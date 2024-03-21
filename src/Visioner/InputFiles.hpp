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
#include "App/InputInterface.hpp"

class InputFiles : public InputInterface
{
public:
    InputFiles();
    cv::Mat GetScene() override;
    std::vector<cv::Mat>& GetObjects() override;
    void LoadFiles(const std::string &path);
    ~InputFiles();

private:
    FileScanner *m_file_scanner;
    std::string m_path;
    std::vector<cv::Mat> m_objects;
    std::vector<cv::Mat> m_scenes;
    // scene vector current cursor
    int m_scene_cursor;
    
    
};
