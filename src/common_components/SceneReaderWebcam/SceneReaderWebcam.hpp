 // *************************************************************************
 //
 // Copyright (c) 2024 Andrei Gramakov. All rights reserved.
 //
 // site:    https://agramakov.me
 // e-mail:  mail@agramakov.me
 //
 // *************************************************************************
 
 #pragma once
 
#include <opencv2/opencv.hpp>
#include "InterfaceSceneReader.hpp"


class SceneReaderWebcam : public InterfaceSceneReader
{
public:
    SceneReaderWebcam();
    cv::Mat GetScene() override;
private:
    cv::Mat m_scene;
    cv::VideoCapture cap;
};
