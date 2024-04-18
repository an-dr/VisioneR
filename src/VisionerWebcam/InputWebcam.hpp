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
#include <opencv2/opencv.hpp>
#include "FileScanner.hpp"
#include "App/InputInterface.hpp"

class InputWebcam : public InputInterface
{
public:
    InputWebcam();
    cv::Mat GetScene() override;
    std::vector<cv::Mat>& GetGoodObjects() override;
    std::vector<cv::Mat>& GetBadObjects() override;
    void LoadFiles(const std::string &path);
    ~InputWebcam();

private:
    FileScanner *m_file_scanner;
    std::string m_path;
    std::vector<cv::Mat> m_objects_good;
    std::vector<cv::Mat> m_objects_bad;
    cv::Mat m_scene;
    cv::VideoCapture cap;
};
