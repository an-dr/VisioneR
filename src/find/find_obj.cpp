#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp> // for homography

#include "find_obj.hpp"

void FindObj::Find(cv::Mat objectImg, cv::Mat sceneImg)
{
    std::vector<cv::KeyPoint> objectKeypoints;
    std::vector<cv::KeyPoint> sceneKeypoints;
    cv::Mat objectDescriptors;
    cv::Mat sceneDescriptors;

    // The detector can be any of (see OpenCV features2d.hpp):
    // cv::FeatureDetector * detector = new cv::DenseFeatureDetector();
    // cv::FeatureDetector * detector = new cv::FastFeatureDetector();
    // cv::FeatureDetector * detector = new cv::GFTTDetector();
    // cv::FeatureDetector * detector = new cv::MSER();
    // cv::FeatureDetector * detector = new cv::ORB();
    cv::FeatureDetector *detector = new cv::SIFT();
    // cv::FeatureDetector * detector = new cv::StarFeatureDetector();
    // cv::FeatureDetector * detector = new cv::SURF(600.0);
    // cv::FeatureDetector * detector = new cv::BRISK();
    detector->detect(objectImg, objectKeypoints);
    detector->detect(sceneImg, sceneKeypoints);
    delete detector;

    ////////////////////////////
    // EXTRACT DESCRIPTORS
    ////////////////////////////
    // The extractor can be any of (see OpenCV features2d.hpp):
    // cv::DescriptorExtractor * extractor = new cv::BriefDescriptorExtractor();
    // cv::DescriptorExtractor * extractor = new cv::ORB();
    cv::DescriptorExtractor *extractor = new cv::SIFT();
    // cv::DescriptorExtractor * extractor = new cv::SURF(600.0);
    // cv::DescriptorExtractor * extractor = new cv::BRISK();
    // cv::DescriptorExtractor * extractor = new cv::FREAK();
    extractor->compute(objectImg, objectKeypoints, objectDescriptors);
    extractor->compute(sceneImg, sceneKeypoints, sceneDescriptors);
    delete extractor;

    ////////////////////////////
    // NEAREST NEIGHBOR MATCHING USING FLANN LIBRARY (included in OpenCV)
    ////////////////////////////
    cv::Mat results;
    cv::Mat dists;
    int k = 2; // find the 2 nearest neighbors
    if (objectDescriptors.type() == CV_8U)
    {
        // Binary descriptors detected (from ORB or Brief)

        // Create Flann LSH index
        cv::flann::Index flannIndex(sceneDescriptors, cv::flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);

        // search (nearest neighbor)
        flannIndex.knnSearch(objectDescriptors, results, dists, k, cv::flann::SearchParams());
    }
    else
    {
        // assume it is CV_32F
        // Create Flann KDTree index
        cv::flann::Index flannIndex(sceneDescriptors, cv::flann::KDTreeIndexParams(), cvflann::FLANN_DIST_EUCLIDEAN);

        // search (nearest neighbor)
        flannIndex.knnSearch(objectDescriptors, results, dists, k, cv::flann::SearchParams());
    }

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
    // Find correspondences by NNDR (Nearest Neighbor Distance Ratio)
    float nndrRatio = 0.8;
    std::vector<cv::Point2f> mpts_1, mpts_2; // Used for homography
    std::vector<int> indexes_1, indexes_2;   // Used for homography
    std::vector<uchar> outlier_mask;         // Used for homography
    for (unsigned int i = 0; i < objectData.rows; ++i)
    {
        // Check if this descriptor matches with those of the objects
        // Apply NNDR
        if (results.at<int>(i, 0) >= 0 && results.at<int>(i, 1) >= 0 && dists.at<float>(i, 0) <= nndrRatio * dists.at<float>(i, 1))
        {
            mpts_1.push_back(objectKeypoints.at(i).pt);
            indexes_1.push_back(i);

            mpts_2.push_back(sceneKeypoints.at(results.at<int>(i, 0)).pt);
            indexes_2.push_back(results.at<int>(i, 0));
        }
    }

    // FIND HOMOGRAPHY
    int nbMatches = 8;
    if (mpts_1.size() >= nbMatches)
    {
        cv::Mat H = findHomography(mpts_1,
                                   mpts_2,
                                   cv::RANSAC,
                                   1.0,
                                   outlier_mask);
        // Do what you want with the homography (like showing a rectangle)
        // The "outlier_mask" contains a mask representing the inliers and outliers.
        // ...
    }
}
