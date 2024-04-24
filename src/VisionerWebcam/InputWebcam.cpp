#include "InputWebcam.hpp"
// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <string>
#include "FileScanner.hpp"
// #include <opencv2/core/core.hpp>
// #include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>


InputWebcam::InputWebcam(): m_file_scanner(nullptr)
{
}


std::vector<cv::Mat>& InputWebcam::GetGoodObjects()
{
    return m_objects_good;
}

std::vector<cv::Mat> &InputWebcam::GetBadObjects()
{
    return m_objects_bad;
}

void InputWebcam::LoadFiles(const std::string &path)
{
    m_path = path;
    m_file_scanner = new FileScanner(m_path);
    
    m_objects_good.clear();
    auto objs = m_file_scanner->GetFiles("object_good_");
    for (auto &obj: objs) {
        m_objects_good.push_back(cv::imread(obj));
    }
    
    m_objects_bad.clear();
    auto objs_bad = m_file_scanner->GetFiles("object_bad_");
    for (auto &obj: objs_bad) {
        m_objects_bad.push_back(cv::imread(obj));
    }
}

InputWebcam::~InputWebcam() {
    delete m_file_scanner;
}
