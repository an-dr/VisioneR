// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include "FileScanner.hpp"
#include "App/InterfaceSceneReader.hpp"

class SceneReaderFileSystem : public InterfaceSceneReader
{
public:
    SceneReaderFileSystem();
    ~SceneReaderFileSystem();
    void SetPath(const std::string &path);
    cv::Mat GetScene() override;
private:
    
    FileScanner *m_file_scanner;
    std::string m_path;
    std::vector<cv::Mat> m_scenes;
    int m_scene_cursor;
    
};
