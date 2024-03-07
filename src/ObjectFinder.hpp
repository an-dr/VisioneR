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
    void Find();

    bool LoadFromFiles(std::string objectImgPath,
                       std::string sceneImgPath);

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
    bool FindHomography();
    bool DrawMatches();

    std::vector<cv::KeyPoint> m_objectKeypoints;
    std::vector<cv::KeyPoint> m_sceneKeypoints;

    cv::Mat m_objectDescriptors;
    cv::Mat m_sceneDescriptors;

    cv::Mat m_objectImg;
    cv::Mat m_sceneImg;
};
