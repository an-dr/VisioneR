#include "InputFiles.hpp"
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
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>


InputFiles::InputFiles()
{
    
}

cv::Mat InputFiles::GetScene()
{
    if(m_scenes.size() == 0) {
        return cv::Mat();
    }
    m_scene_cursor = (m_scene_cursor + 1) % m_scenes.size();
    return m_scenes[m_scene_cursor];
}

std::vector<cv::Mat>& InputFiles::GetObjects()
{
    return m_objects;
}

void InputFiles::LoadFiles(const std::string &path)
{
    m_path = path;
    m_file_scanner = new FileScanner(m_path);
    
    m_objects.clear();
    auto objs = m_file_scanner->GetFiles("object_");
    for (auto &obj: objs) {
        m_objects.push_back(cv::imread(obj));
    }
    
    m_scenes.clear();
    auto scenes = m_file_scanner->GetFiles("scene_");
    for (auto &scene: scenes) {
        m_scenes.push_back(cv::imread(scene));
    }
    
}

InputFiles::~InputFiles() {
    delete m_file_scanner;
}
