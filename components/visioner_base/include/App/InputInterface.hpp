// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <opencv2/core/core.hpp>
#include <vector>
#include <map>

class InputInterface
{
public:
    InputInterface() = default;
    virtual cv::Mat GetScene() = 0;
    virtual std::vector<cv::Mat> &GetGoodObjects() = 0;
    virtual std::vector<cv::Mat> &GetBadObjects() = 0;
    // virtual std::vector<std::pair<cv::Mat, std::string>> &GetGoodObjects() = 0;
    // virtual std::vector<std::pair<cv::Mat, std::string>> &GetBadObjects() = 0;
};
