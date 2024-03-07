// https://docs.opencv.org/3.4/d7/dff/tutorial_feature_homography.html

#include <opencv2/calib3d/calib3d.hpp> // for homography
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // for wrapPerspective
#include <opencv2/opencv_modules.hpp>
#include <stdio.h>

#include "ObjectFinder.hpp"

using namespace cv;

void GetImages(cv::Mat &img_scene, cv::Mat &img_obj)
{
    img_scene = imread("img_scene.jpg");
    // img_scene = imread("img_scene_many.jpg");
    // img_scene = imread("img_scene_obj.jpg");
    img_obj = imread("img_obj.jpg");
}

void GetKeyPoints(cv::Mat &img, std::vector<cv::KeyPoint> &keypoints, bool show = false)
{
    cv::Ptr<cv::FeatureDetector> detector;
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
    detector->detect(img, keypoints);
    printf("%d keypoints detected\n", (int)keypoints.size());

    if (show)
    {
        // Draw keypoints
        Mat img_keypoints = img.clone();
        drawKeypoints(img_keypoints, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        // show
        imshow("Keypoints", img_keypoints);
        waitKey(500);
    }
}

void GetDescriptors(cv::Mat &img, std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors)
{
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
    extractor->compute(img, keypoints, descriptors);
    printf("%d descriptors extracted\n", descriptors.rows);
}

void FindMatches(cv::Mat &objectDescriptors,
                 cv::Mat &sceneDescriptors,
                 cv::Mat &results,
                 cv::Mat &dists,
                 std::vector<std::vector<cv::DMatch>> &matches,
                 bool useBFMatcher = false)
{

    int k = 2; // find the 2 nearest neighbors
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
            printf("Creating FLANN LSH index is done\n");

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
            // printf("Time creating FLANN KDTree index = %lld ms\n", 0LL);

            // search (nearest neighbor)
            flannIndex.knnSearch(objectDescriptors, results, dists, k, cv::flann::SearchParams());
        }
    }
    // printf("Time nearest neighbor search = %lld ms\n", 0LL);

    // Conversion to CV_32F if needed
    if (dists.type() == CV_32S)
    {
        cv::Mat temp;
        dists.convertTo(temp, CV_32F);
        dists = temp;
    }

    // Draw matches
}

void DrawMatches(cv::Mat &objectImg, std::vector<cv::KeyPoint> &objectKeypoints,
                 cv::Mat &sceneImg, std::vector<cv::KeyPoint> &sceneKeypoints,
                 std::vector<std::vector<cv::DMatch>> &matches)
{
    Mat img_matches;
    // cv::drawMatches(objectImg, objectKeypoints, sceneImg, sceneKeypoints, matches, img_matches);
    cv::drawMatches(objectImg, objectKeypoints, sceneImg, sceneKeypoints, matches, img_matches);
    imshow("Matches", img_matches);
    waitKey(500);
}

void ProcessNearestNeighborResults(std::vector<cv::KeyPoint> &objectKeypoints,
                                   std::vector<cv::KeyPoint> &sceneKeypoints,
                                   cv::Mat &objectDescriptors,
                                   cv::Mat &results,
                                   cv::Mat &dists,
                                   std::vector<std::vector<cv::DMatch>> &matches,
                                   std::vector<cv::Point2f> &src_points,
                                   std::vector<cv::Point2f> &dst_points,
                                   std::vector<int> &src_point_idxs,
                                   std::vector<int> &dst_point_idxs,
                                   std::vector<uchar> &outlier_mask,
                                   bool useBFMatcher = false)
{
    // Find correspondences by NNDR (Nearest Neighbor Distance Ratio)
    float nndrRatio = 0.6f;
    // Check if this descriptor matches with those of the objects
    if (!useBFMatcher)
    {
        for (int i = 0; i < objectDescriptors.rows; ++i)
        {
            // Apply NNDR
            // printf("q=%d dist1=%f dist2=%f\n", i, dists.at<float>(i,0), dists.at<float>(i,1));
            if (results.at<int>(i, 0) >= 0 &&
                results.at<int>(i, 1) >= 0 &&
                dists.at<float>(i, 0) <= nndrRatio * dists.at<float>(i, 1))
            {
                src_points.push_back(objectKeypoints.at(i).pt);
                src_point_idxs.push_back(i);

                dst_points.push_back(sceneKeypoints.at(results.at<int>(i, 0)).pt);
                dst_point_idxs.push_back(results.at<int>(i, 0));
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            // Apply NNDR
            // printf("q=%d dist1=%f dist2=%f\n", matches.at(i).at(0).queryIdx, matches.at(i).at(0).distance, matches.at(i).at(1).distance);
            if (matches.at(i).size() == 2 &&
                matches.at(i).at(0).distance <= nndrRatio * matches.at(i).at(1).distance)
            {
                src_points.push_back(objectKeypoints.at(matches.at(i).at(0).queryIdx).pt);
                src_point_idxs.push_back(matches.at(i).at(0).queryIdx);

                dst_points.push_back(sceneKeypoints.at(matches.at(i).at(0).trainIdx).pt);
                dst_point_idxs.push_back(matches.at(i).at(0).trainIdx);
            }
        }
    }
}

void FindHomography(std::vector<cv::Point2f> &src_points,
                    std::vector<cv::Point2f> &dst_points,
                    std::vector<uchar> &outlier_mask,
                    cv::Mat &H,
                    unsigned int minInliers = 8)
{
    if (src_points.size() >= minInliers)
    {
        H = findHomography(src_points,
                           dst_points,
                           cv::RANSAC,
                           1.0,
                           outlier_mask);

        int inliers = 0, outliers = 0;
        for (unsigned int k = 0; k < src_points.size(); ++k)
        {
            if (outlier_mask.at(k))
            {
                ++inliers;
            }
            else
            {
                ++outliers;
            }
        }
        printf("Inliers=%d Outliers=%d\n", inliers, outliers);
    }
    else
    {
        printf("Not enough matches (%d) for homography...\n", (int)src_points.size());
    }
}

void GetResult(Mat &objectImg, Mat &sceneImg, cv::Mat &H)
{
    //-- Get the corners from the image_1 ( the object to be "detected" )
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = Point2f(0, 0);
    obj_corners[1] = Point2f((float)objectImg.cols, 0);
    obj_corners[2] = Point2f((float)objectImg.cols, (float)objectImg.rows);
    obj_corners[3] = Point2f(0, (float)objectImg.rows);
    std::vector<Point2f> scene_corners(4);
    perspectiveTransform(obj_corners, scene_corners, H);

    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
    line(sceneImg, scene_corners[0], scene_corners[1], Scalar(0, 255, 0), 4);
    line(sceneImg, scene_corners[1], scene_corners[2], Scalar(0, 255, 0), 4);
    line(sceneImg, scene_corners[2], scene_corners[3], Scalar(0, 255, 0), 4);
    line(sceneImg, scene_corners[3], scene_corners[0], Scalar(0, 255, 0), 4);
    line(sceneImg, scene_corners[0], scene_corners[2], Scalar(0, 255, 0), 4);
    line(sceneImg, scene_corners[3], scene_corners[1], Scalar(0, 255, 0), 4);

    imshow("Result", sceneImg);
    waitKey(0);
}

void proto1()
{
    printf("Loading images\n");
    Mat sceneImg, objectImg;
    GetImages(sceneImg, objectImg);

    // EXTRACT KEYPOINTS
    std::vector<cv::KeyPoint> objectKeypoints;
    std::vector<cv::KeyPoint> sceneKeypoints;
    GetKeyPoints(objectImg, objectKeypoints, false);
    GetKeyPoints(sceneImg, sceneKeypoints, false);

    // EXTRACT DESCRIPTORS
    cv::Mat objectDescriptors;
    cv::Mat sceneDescriptors;
    GetDescriptors(objectImg, objectKeypoints, objectDescriptors);
    GetDescriptors(sceneImg, sceneKeypoints, sceneDescriptors);

    // NEAREST NEIGHBOR MATCHING USING FLANN LIBRARY (included in OpenCV)
    cv::Mat results;
    cv::Mat dists;
    std::vector<std::vector<cv::DMatch>> matches;
    bool useBFMatcher = false; // SET TO TRUE TO USE BRUTE FORCE MATCHER
    FindMatches(objectDescriptors, sceneDescriptors, results, dists, matches, useBFMatcher);
    // DrawMatches(objectImg, objectKeypoints, sceneImg, sceneKeypoints, matches);

    // PROCESS NEAREST NEIGHBOR RESULTS
    std::vector<cv::Point2f> src_points, dst_points; // Used for homography
    std::vector<int> src_point_idxs, dst_point_idxs; // Used for homography
    std::vector<uchar> outlier_mask;                 // Used for homography
    ProcessNearestNeighborResults(objectKeypoints,
                                  sceneKeypoints,
                                  objectDescriptors,
                                  results, dists,
                                  matches,
                                  src_points, dst_points,
                                  src_point_idxs, dst_point_idxs,
                                  outlier_mask, useBFMatcher);

    // FIND HOMOGRAPHY
    cv::Mat H;
    FindHomography(src_points, dst_points, outlier_mask, H);

    // Get the result
    GetResult(objectImg, sceneImg, H);
    printf("Closing...\n");
}

void proto2()
{
    ObjectFinder of;
    of.LoadFromFiles("img_obj.jpg", "img_scene.jpg");
    of.Find();

}

int main(int argc, char **argv)
{
    // proto1();
    proto2();
    return 0;
}
