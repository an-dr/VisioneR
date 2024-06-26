// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "InputFiles.hpp"
#include <string>
#include <opencv2/opencv.hpp>
#include "FileScanner.hpp"

InputFiles::InputFiles() {}

std::vector<cv::Mat> &InputFiles::GetGoodObjects() { return m_objects_good; }

std::vector<cv::Mat> &InputFiles::GetBadObjects() { return m_objects_bad; }

void InputFiles::LoadFiles(const std::string &path) {
    m_path = path;
    m_file_scanner = new FileScanner(m_path);

    m_objects_good.clear();
    m_objects_good_names = m_file_scanner->GetFiles("object_good_");
    for (auto &obj : m_objects_good_names) {
        m_objects_good.push_back(cv::imread(obj));
    }

    m_objects_bad.clear();
    m_objects_bad_names = m_file_scanner->GetFiles("object_bad_");
    for (auto &obj : m_objects_bad_names) {
        m_objects_bad.push_back(cv::imread(obj));
    }
}

InputFiles::~InputFiles() { delete m_file_scanner; }
