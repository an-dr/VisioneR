#include <stdio.h>
// time std

// Qt stuff
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QPen>
#include <QColor>

// OpenCV stuff
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp> // for homography

#include <opencv2/opencv_modules.hpp>

using namespace cv;

void GetImages(cv::Mat &img_scene, cv::Mat &img_obj)
{
    img_scene = imread("img_scene.jpg", cv::IMREAD_GRAYSCALE);
    img_obj = imread("img_obj.jpg", cv::IMREAD_GRAYSCALE);
}

int main(int argc, char **argv)
{

    // create a gui window:
    //  namedWindow("VisioneR",1);

    // initialize a 120X350 matrix of black pixels:
    //  Mat output = Mat::zeros( 120, 350, CV_8UC3 );
    Mat sceneImg, objectImg;
    GetImages(sceneImg, objectImg);

    QElapsedTimer time;

    // GUI stuff
    QApplication app(argc, argv);

    time.start();

    if (!objectImg.empty() && !sceneImg.empty())
    {
        printf("Loading images: %lld ms\n", time.restart());
        std::vector<cv::KeyPoint> objectKeypoints;
        std::vector<cv::KeyPoint> sceneKeypoints;
        cv::Mat objectDescriptors;
        cv::Mat sceneDescriptors;

        ////////////////////////////
        // EXTRACT KEYPOINTS
        ////////////////////////////
        cv::Ptr<cv::FeatureDetector> detector;
        // The detector can be any of (see OpenCV features2d.hpp):
#if CV_MAJOR_VERSION == 2
        // detector = cv::Ptr(new cv::DenseFeatureDetector());
        // detector = cv::Ptr(new cv::FastFeatureDetector());
        // detector = cv::Ptr(new cv::GFTTDetector());
        // detector = cv::Ptr(new cv::MSER());
        // detector = cv::Ptr(new cv::ORB());
        detector = cv::Ptr<cv::FeatureDetector>(new cv::SIFT());
        // detector = cv::Ptr(new cv::StarFeatureDetector());
        // detector = cv::Ptr(new cv::SURF(600.0));
        // detector = cv::Ptr(new cv::BRISK());
#elif CV_MAJOR_VERSION < 4 || (CV_MAJOR_VERSION == 4 && CV_MINOR_VERSION < 3)
        detector = cv::xfeatures2d::SIFT::create();
#else // >= 4.3.0
        detector = cv::SIFT::create();
#endif
        detector->detect(objectImg, objectKeypoints);
        printf("Object: %d keypoints detected in %lld ms\n", (int)objectKeypoints.size(), time.restart());
        detector->detect(sceneImg, sceneKeypoints);
        printf("Scene: %d keypoints detected in %lld ms\n", (int)sceneKeypoints.size(), time.restart());

        ////////////////////////////
        // EXTRACT DESCRIPTORS
        ////////////////////////////
        cv::Ptr<cv::DescriptorExtractor> extractor;
#if CV_MAJOR_VERSION == 2
        // The extractor can be any of (see OpenCV features2d.hpp):
        // extractor = cv::Ptr(new cv::BriefDescriptorExtractor());
        // extractor = cv::Ptr(new cv::ORB());
        extractor = cv::Ptr<cv::DescriptorExtractor>(new cv::SIFT());
        // extractor = cv::Ptr(new cv::SURF(600.0));
        // extractor = cv::Ptr(new cv::BRISK());
        // extractor = cv::Ptr(new cv::FREAK());
#elif CV_MAJOR_VERSION < 4 || (CV_MAJOR_VERSION == 4 && CV_MINOR_VERSION < 3)
        extractor = cv::xfeatures2d::SIFT::create();
#else // >= 4.3.0
        extractor = cv::SIFT::create();
#endif
        extractor->compute(objectImg, objectKeypoints, objectDescriptors);
        printf("Object: %d descriptors extracted in %lld ms\n", objectDescriptors.rows, time.restart());
        extractor->compute(sceneImg, sceneKeypoints, sceneDescriptors);
        printf("Scene: %d descriptors extracted in %lld ms\n", sceneDescriptors.rows, time.restart());

        ////////////////////////////
        // NEAREST NEIGHBOR MATCHING USING FLANN LIBRARY (included in OpenCV)
        ////////////////////////////
        cv::Mat results;
        cv::Mat dists;
        std::vector<std::vector<cv::DMatch>> matches;
        int k = 2;                 // find the 2 nearest neighbors
        bool useBFMatcher = false; // SET TO TRUE TO USE BRUTE FORCE MATCHER
        if (objectDescriptors.type() == CV_8U)
        {
            // Binary descriptors detected (from ORB, Brief, BRISK, FREAK)
            printf("Binary descriptors detected...\n");
            if (useBFMatcher)
            {
                cv::BFMatcher matcher(cv::NORM_HAMMING); // use cv::NORM_HAMMING2 for ORB descriptor with WTA_K == 3 or 4 (see ORB constructor)
                matcher.knnMatch(objectDescriptors, sceneDescriptors, matches, k);
            }
            else
            {
                // Create Flann LSH index
                cv::flann::Index flannIndex(sceneDescriptors, cv::flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);
                printf("Time creating FLANN LSH index = %lld ms\n", time.restart());

                // search (nearest neighbor)
                flannIndex.knnSearch(objectDescriptors, results, dists, k, cv::flann::SearchParams());
            }
        }
        else
        {
            // assume it is CV_32F
            printf("Float descriptors detected...\n");
            if (useBFMatcher)
            {
                cv::BFMatcher matcher(cv::NORM_L2);
                matcher.knnMatch(objectDescriptors, sceneDescriptors, matches, k);
            }
            else
            {
                // Create Flann KDTree index
                cv::flann::Index flannIndex(sceneDescriptors, cv::flann::KDTreeIndexParams(), cvflann::FLANN_DIST_EUCLIDEAN);
                printf("Time creating FLANN KDTree index = %lld ms\n", time.restart());

                // search (nearest neighbor)
                flannIndex.knnSearch(objectDescriptors, results, dists, k, cv::flann::SearchParams());
            }
        }
        printf("Time nearest neighbor search = %lld ms\n", time.restart());

        // Conversion to CV_32F if needed
        if (dists.type() == CV_32S)
        {
            cv::Mat temp;
            dists.convertTo(temp, CV_32F);
            dists = temp;
        }

        ////////////////////////////
        // PROCESS NEAREST NEIGHBOR RESULTS
        ////////////////////////////
        // Set gui data
        // ObjWidget objWidget(0, objectKeypoints, QMultiMap<int,int>(), cvtCvMat2QImage(objectImg));
        // ObjWidget sceneWidget(0, sceneKeypoints, QMultiMap<int,int>(), cvtCvMat2QImage(sceneImg));

        // Find correspondences by NNDR (Nearest Neighbor Distance Ratio)
        float nndrRatio = 0.8f;
        std::vector<cv::Point2f> mpts_1, mpts_2; // Used for homography
        std::vector<int> indexes_1, indexes_2; // Used for homography
        std::vector<uchar> outlier_mask;  // Used for homography
        // Check if this descriptor matches with those of the objects
        if(!useBFMatcher)
        {
        	for(int i=0; i<objectDescriptors.rows; ++i)
        	{
        		// Apply NNDR
        		//printf("q=%d dist1=%f dist2=%f\n", i, dists.at<float>(i,0), dists.at<float>(i,1));
        		if(results.at<int>(i,0) >= 0 && results.at<int>(i,1) >= 0 &&
        		   dists.at<float>(i,0) <= nndrRatio * dists.at<float>(i,1))
        		{
        			mpts_1.push_back(objectKeypoints.at(i).pt);
        			indexes_1.push_back(i);

        			mpts_2.push_back(sceneKeypoints.at(results.at<int>(i,0)).pt);
        			indexes_2.push_back(results.at<int>(i,0));
        		}
        	}
        }
        else
        {
        	for(unsigned int i=0; i<matches.size(); ++i)
        	{
        		// Apply NNDR
        		//printf("q=%d dist1=%f dist2=%f\n", matches.at(i).at(0).queryIdx, matches.at(i).at(0).distance, matches.at(i).at(1).distance);
        		if(matches.at(i).size() == 2 &&
        		   matches.at(i).at(0).distance <= nndrRatio * matches.at(i).at(1).distance)
        		{
        			mpts_1.push_back(objectKeypoints.at(matches.at(i).at(0).queryIdx).pt);
        			indexes_1.push_back(matches.at(i).at(0).queryIdx);

        			mpts_2.push_back(sceneKeypoints.at(matches.at(i).at(0).trainIdx).pt);
        			indexes_2.push_back(matches.at(i).at(0).trainIdx);
        		}
        	}
        }

        // FIND HOMOGRAPHY
        unsigned int minInliers = 8;
        if(mpts_1.size() >= minInliers)
        {
        	time.start();
        	cv::Mat H = findHomography(mpts_1,
        			mpts_2,
        			cv::RANSAC,
        			1.0,
        			outlier_mask);
        	printf("Time finding homography = %lld ms\n", time.restart());
        	int inliers=0, outliers=0;
        	for(unsigned int k=0; k<mpts_1.size();++k)
        	{
        		if(outlier_mask.at(k))
        		{
        			++inliers;
        		}
        		else
        		{
        			++outliers;
        		}
        	}
        	QTransform hTransform(
        	H.at<double>(0,0), H.at<double>(1,0), H.at<double>(2,0),
        	H.at<double>(0,1), H.at<double>(1,1), H.at<double>(2,1),
        	H.at<double>(0,2), H.at<double>(1,2), H.at<double>(2,2));

        	// GUI : Change color and add homography rectangle
        	QColor color(Qt::green);
        	int alpha = 130;
        	color.setAlpha(alpha);
        	for(unsigned int k=0; k<mpts_1.size();++k)
        	{
        		// if(outlier_mask.at(k))
        		// {
        		// 	objWidget.setKptColor(indexes_1.at(k), color);
        		// 	sceneWidget.setKptColor(indexes_2.at(k), color);
        		// }
        		// else
        		// {
        		// 	objWidget.setKptColor(indexes_1.at(k), QColor(255,0,0,alpha));
        		// 	sceneWidget.setKptColor(indexes_2.at(k), QColor(255,0,0,alpha));
        		// }
        	}
        	QPen rectPen(color);
        	rectPen.setWidth(4);
        	// QGraphicsRectItem * rectItem = new QGraphicsRectItem(objWidget.pixmap().rect());
        	// rectItem->setPen(rectPen);
        	// rectItem->setTransform(hTransform);
        	// sceneWidget.addRect(rectItem);
        	printf("Inliers=%d Outliers=%d\n", inliers, outliers);
        }
        else
        {
        	printf("Not enough matches (%d) for homography...\n", (int)mpts_1.size());
        }

        // // Wait for gui
        // objWidget.setGraphicsViewMode(false);
        // objWidget.setWindowTitle("Object");
        // if(objWidget.pixmap().width() <= 800)
        // {
        // 	objWidget.setMinimumSize(objWidget.pixmap().width(), objWidget.pixmap().height());
        // }
        // else
        // {
        // 	objWidget.setMinimumSize(800, 600);
        // 	objWidget.setAutoScale(false);
        // }

        // sceneWidget.setGraphicsViewMode(false);
        // sceneWidget.setWindowTitle("Scene");
        // if(sceneWidget.pixmap().width() <= 800)
        // {
        // 	sceneWidget.setMinimumSize(sceneWidget.pixmap().width(), sceneWidget.pixmap().height());
        // }
        // else
        // {
        // 	sceneWidget.setMinimumSize(800, 600);
        // 	sceneWidget.setAutoScale(false);
        // }

        // sceneWidget.show();
        // objWidget.show();

        int r = app.exec();
        printf("Closing...\n");

        return r;
    }
    else
    {
        printf("Images are not valid!\n");
        // showUsage();
    }

    return 1;
}
