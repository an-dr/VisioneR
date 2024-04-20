// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/calib3d/calib3d.hpp> // for homography
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // for wrapPerspective
#include <opencv2/opencv_modules.hpp>
#include <stdio.h>

#include "tools.hpp"
#include "Tetrangle.hpp"

#include "ObjectFinder.hpp"

using namespace cv;
using namespace std;

bool ObjectFinder::Find(Mat &objectImg, Point2f &out_result, bool show_result)
{
    m_objectImg = objectImg;
    if (m_objectImg.empty() || m_sceneImg.empty())
    {
        printf("Error: empty images\n");
        return false;
    }

    _DetectKeypoints("Object", m_objectImg, m_objectKeypoints, false);
    _ComputeDescriptors("Object", m_objectImg, m_objectKeypoints, m_objectDescriptors);

    _DetectKeypoints("Scene", m_sceneImg, m_sceneKeypoints);
    _ComputeDescriptors("Scene", m_sceneImg, m_sceneKeypoints, m_sceneDescriptors);

    bool useBFMatcher = true;

    // Match descriptors
    Mat results, dists;
    vector<vector<DMatch>> matches;
    _MatchDescriptors(results, dists, matches, useBFMatcher);

    // Find good matches
    vector<Point2f> src_points, dst_points;
    vector<int> src_point_idxs, dst_point_idxs;
    vector<uchar> outlier_mask;
    _FindGoodMatches(results, dists, matches,
                     src_points, dst_points, src_point_idxs, dst_point_idxs,
                     outlier_mask, useBFMatcher);

    // Find homography
    Mat H;
    bool result = false;
    result = _FindHomography(src_points, dst_points, outlier_mask, H, 20);
    if (!result)
    {
        printf("Error: homography not found\n");
        return false;
    }

    // Get result
    result = _GetResult(m_objectImg, m_sceneImg, H, out_result, show_result);
    if (!result)
    {
        printf("Error: result not found\n");
        return result;
    }
    return result;
}

bool ObjectFinder::SetScene(cv::Mat &sceneImg)
{
    if (sceneImg.empty())
    {
        printf("Error: empty/no image\n");
        return false;
    }
    m_sceneImg = sceneImg;
    return true;
}

bool ObjectFinder::_DetectKeypoints(string image_name,
                                    Mat &img,
                                    vector<KeyPoint> &keypoints,
                                    bool show)
{
    Ptr<FeatureDetector> detector;
#if CV_MAJOR_VERSION == 2
    // detector = Ptr(new DenseFeatureDetector());
    // detector = Ptr(new FastFeatureDetector());
    // detector = Ptr(new GFTTDetector());
    // detector = Ptr(new MSER());
    // detector = Ptr(new ORB());
    detector = Ptr<FeatureDetector>(new SIFT());
    // detector = Ptr(new StarFeatureDetector());
    // detector = Ptr(new SURF(600.0));
    // detector = Ptr(new BRISK());
#elif CV_MAJOR_VERSION < 4 || (CV_MAJOR_VERSION == 4 && CV_MINOR_VERSION < 3)
    detector = xfeatures2d::SIFT::create();
#else // >= 4.3.0
    detector = SIFT::create();
#endif
    detector->detect(img, keypoints);
    printf("[%s] %d keypoints detected\n", image_name.c_str(),
           (int)keypoints.size());

    if (show)
    {
        // Draw keypoints
        Mat img_keypoints = img.clone();
        drawKeypoints(img_keypoints, keypoints, img_keypoints,
                      Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        // show
        imshow("Keypoints", img_keypoints);
        waitKey(1500);
    }
    return true;
}

bool ObjectFinder::_ComputeDescriptors(string image_name,
                                       Mat &img,
                                       vector<KeyPoint> &keypoints,
                                       Mat &descriptors)
{
    if (keypoints.size() == 0)
    {
        printf("[%s] Error: no keypoints\n", image_name.c_str());
        return false;
    }

    Ptr<DescriptorExtractor> extractor;
#if CV_MAJOR_VERSION == 2
    // The extractor can be any of (see OpenCV features2d.hpp):
    // extractor = Ptr(new BriefDescriptorExtractor());
    // extractor = Ptr(new ORB());
    extractor = Ptr<DescriptorExtractor>(new SIFT());
    // extractor = Ptr(new SURF(600.0));
    // extractor = Ptr(new BRISK());
    // extractor = Ptr(new FREAK());
#elif CV_MAJOR_VERSION < 4 || (CV_MAJOR_VERSION == 4 && CV_MINOR_VERSION < 3)
    extractor = xfeatures2d::SIFT::create();
#else // >= 4.3.0
    extractor = SIFT::create();
#endif
    extractor->compute(img, keypoints, descriptors);
    printf("[%s] %d descriptors extracted\n",
           image_name.c_str(),
           descriptors.rows);
    return true;
}

bool ObjectFinder::_MatchDescriptors(Mat &results, Mat &dists,
                                     vector<vector<DMatch>> &matches, bool useBFMatcher)
{
    int k = 2; // find the 2 nearest neighbors
    if (m_objectDescriptors.type() == CV_8U)
    {
        // Binary descriptors detected (from ORB, Brief, BRISK, FREAK)
        printf("Binary descriptors detected...\n");
        if (useBFMatcher)
        {
            // use NORM_HAMMING2 for ORB descriptor with WTA_K == 3 or 4 (see ORB constructor)
            BFMatcher matcher(NORM_HAMMING);
            matcher.knnMatch(m_objectDescriptors, m_sceneDescriptors, matches, k);
        }
        else
        {
            // Create Flann LSH index
            flann::Index flannIndex(m_sceneDescriptors,
                                    flann::LshIndexParams(12, 20, 2),
                                    cvflann::FLANN_DIST_HAMMING);
            printf("Creating FLANN LSH index is done\n");

            // search (nearest neighbor)
            flannIndex.knnSearch(m_objectDescriptors, results, dists, k, flann::SearchParams());
        }
    }
    else
    {
        // assume it is CV_32F
        printf("Float descriptors detected...\n");
        if (useBFMatcher)
        {
            BFMatcher matcher(NORM_L2);
            matcher.knnMatch(m_objectDescriptors, m_sceneDescriptors, matches, k);
        }
        else
        {
            // Create Flann KDTree index
            flann::Index flannIndex(m_sceneDescriptors,
                                    flann::KDTreeIndexParams(),
                                    cvflann::FLANN_DIST_EUCLIDEAN);
            // printf("Time creating FLANN KDTree index = %lld ms\n", 0LL);

            // search (nearest neighbor)
            flannIndex.knnSearch(m_objectDescriptors, results, dists, k,
                                 flann::SearchParams());
        }
    }
    // printf("Time nearest neighbor search = %lld ms\n", 0LL);

    // Conversion to CV_32F if needed
    if (dists.type() == CV_32S)
    {
        Mat temp;
        dists.convertTo(temp, CV_32F);
        dists = temp;
    }
    return true;
}

bool ObjectFinder::_FindGoodMatches(Mat &results,
                                    Mat &dists,
                                    vector<vector<DMatch>> &matches,
                                    vector<Point2f> &src_points,
                                    vector<Point2f> &dst_points,
                                    vector<int> &src_point_idxs,
                                    vector<int> &dst_point_idxs,
                                    vector<uchar> &outlier_mask,
                                    bool useBFMatcher)
{
    // Find correspondences by NNDR (Nearest Neighbor Distance Ratio)
    float nndrRatio = 0.8f;
    // Check if this descriptor matches with those of the objects
    if (!useBFMatcher)
    {
        for (int i = 0; i < m_objectDescriptors.rows; ++i)
        {
            // Apply NNDR
            // printf("q=%d dist1=%f dist2=%f\n", i, dists.at<float>(i,0), dists.at<float>(i,1));
            if (results.at<int>(i, 0) >= 0 &&
                results.at<int>(i, 1) >= 0 &&
                dists.at<float>(i, 0) <= nndrRatio * dists.at<float>(i, 1))
            {
                src_points.push_back(m_objectKeypoints.at(i).pt);
                src_point_idxs.push_back(i);

                dst_points.push_back(m_sceneKeypoints.at(results.at<int>(i, 0)).pt);
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
                src_points.push_back(m_objectKeypoints.at(matches.at(i).at(0).queryIdx).pt);
                src_point_idxs.push_back(matches.at(i).at(0).queryIdx);

                dst_points.push_back(m_sceneKeypoints.at(matches.at(i).at(0).trainIdx).pt);
                dst_point_idxs.push_back(matches.at(i).at(0).trainIdx);
            }
        }
    }
    printf("%d good matches found\n", (int)src_points.size());
    return true;
}

bool ObjectFinder::_FindHomography(vector<Point2f> &src_points,
                                   vector<Point2f> &dst_points,
                                   vector<uchar> &outlier_mask,
                                   Mat &H,
                                   unsigned int minInliers)
{
    bool result = false;

    if (src_points.size() >= minInliers)
    {
        H = findHomography(src_points,
                           dst_points,
                           RANSAC,
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
        result = true;
    }
    else
    {
        printf("Not enough matches (%d) for homography...\n", (int)src_points.size());
    }
    return result;
}

bool ObjectFinder::_GetResult(cv::Mat &objectImg,
                              cv::Mat &sceneImg,
                              cv::Mat &H,
                              cv::Point2f &out_center,
                              bool show)
{
    //-- Get the corners from the image_1 ( the object to be "detected" )
    Tetrangle obj_corners(Point2f(0, 0),
                          Point2f((float)objectImg.cols, 0),
                          Point2f((float)objectImg.cols, (float)objectImg.rows),
                          Point2f(0, (float)objectImg.rows));
    Tetrangle scene_corners;

    // Catch exception if transformation is not possible
    try
    {
        perspectiveTransform(obj_corners.arr, scene_corners.arr, H);
    }
    catch (...)
    {
        return false;
    }

    // Verify Tetrangle Size
    if (scene_corners.GetArea() >= 200)
    {
        out_center = scene_corners.GetCenter();
        printf("Center: (%.2f, %.2f)\n", out_center.x, out_center.y);

        if (show)
        {
            Mat sceneImgCopy = sceneImg.clone();
            DrawTetrangle(sceneImgCopy,
                          scene_corners[0], scene_corners[1],
                          scene_corners[2], scene_corners[3],
                          true);
            imshow("Scene", sceneImgCopy);
            waitKey(1);
        }

        return true;
    }
    return false;
}
