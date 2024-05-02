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
#include "FileScanner.hpp"
#include "InputInterface.hpp"

class InputFiles : public InputInterface
{
public:
    InputFiles();
    std::vector<cv::Mat>& GetGoodObjects() override;
    std::vector<cv::Mat>& GetBadObjects() override;
    void LoadFiles(const std::string &path);
    ~InputFiles();

private:
    FileScanner *m_file_scanner;
    std::string m_path;
    std::vector<cv::Mat> m_objects_good;
    std::vector<cv::Mat> m_objects_bad;
    std::vector<std::string> m_objects_good_names;
    std::vector<std::string> m_objects_bad_names;
    
};
