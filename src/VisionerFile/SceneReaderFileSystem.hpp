// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include "InterfaceSceneReader.hpp"

class SceneReaderFileSystem : public InterfaceSceneReader
{
public:
    SceneReaderFileSystem();
    cv::Mat GetScene() override;
    ~SceneReaderFileSystem();

private:
    std::vector<cv::Mat> m_scenes;
    int m_scene_cursor;
};
