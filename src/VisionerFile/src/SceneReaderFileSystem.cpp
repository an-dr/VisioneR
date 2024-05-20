// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/opencv.hpp>

#include "SceneReaderFileSystem.hpp"

SceneReaderFileSystem::SceneReaderFileSystem()
    : m_file_scanner(nullptr), m_path(""), m_scenes({}), m_scene_cursor(0) {}

SceneReaderFileSystem::~SceneReaderFileSystem() {
    if (m_file_scanner != nullptr) {
        delete m_file_scanner;
    }
}

void SceneReaderFileSystem::SetPath(const std::string &path) {
    // Set up
    m_path = path;
    if (m_file_scanner != nullptr) {
        delete m_file_scanner;
    }
    m_file_scanner = new FileScanner(m_path);

    // Load pictures
    m_scenes.clear();
    auto scenes = m_file_scanner->GetFiles("scene_");
    for (auto &scene : scenes) {
        m_scenes.push_back(cv::imread(scene));
    }
}

cv::Mat SceneReaderFileSystem::GetScene() {
    if (m_scenes.size() == 0) {
        return cv::Mat();
    }
    m_scene_cursor = (m_scene_cursor + 1) % m_scenes.size();
    return m_scenes[m_scene_cursor];
}
