// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>

class ObjectFinder
{
public:
    void Find(cv::Mat &objectImg, cv::Point2f &out_result);
    void Find(std::string &objectImg, cv::Point2f &out_result);
    bool SetScene(cv::Mat &sceneImg);
    bool SetScene(std::string &sceneImgPath);

private:
    bool DetectKeypoints(std::string image_name,
                         cv::Mat &img,
                         std::vector<cv::KeyPoint> &keypoints,
                         bool show = false);

    bool ComputeDescriptors(std::string image_name,
                            cv::Mat &img,
                            std::vector<cv::KeyPoint> &keypoints,
                            cv::Mat &descriptors,
                            bool show = false);

    bool MatchDescriptors(cv::Mat &results,
                          cv::Mat &dists,
                          std::vector<std::vector<cv::DMatch>> &matches,
                          bool useBFMatcher = false);

    bool FindGoodMatches(cv::Mat &results,
                         cv::Mat &dists,
                         std::vector<std::vector<cv::DMatch>> &matches,
                         std::vector<cv::Point2f> &src_points,
                         std::vector<cv::Point2f> &dst_points,
                         std::vector<int> &src_point_idxs,
                         std::vector<int> &dst_point_idxs,
                         std::vector<uchar> &outlier_mask,
                         bool useBFMatcher = false);

    bool FindHomography(std::vector<cv::Point2f> &src_points,
                        std::vector<cv::Point2f> &dst_points,
                        std::vector<uchar> &outlier_mask,
                        cv::Mat &H,
                        unsigned int minInliers = 8);

    bool GetResult(cv::Mat &objectImg,
                   cv::Mat &sceneImg,
                   cv::Mat &H,
                   cv::Point2f &out_center);

    static bool CalculateLinesIntersection(cv::Point2f &p1,
                                           cv::Point2f &p2,
                                           cv::Point2f &p3,
                                           cv::Point2f &p4,
                                           cv::Point2f &r);

    std::vector<cv::KeyPoint> m_objectKeypoints;
    std::vector<cv::KeyPoint> m_sceneKeypoints;

    cv::Mat m_objectDescriptors;
    cv::Mat m_sceneDescriptors;

    cv::Mat m_objectImg;
    cv::Mat m_sceneImg;
};
