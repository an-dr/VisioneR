// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "SceneReaderWebcam.hpp"
#include <opencv2/opencv.hpp>

SceneReaderWebcam::SceneReaderWebcam() : cap(0) {}

cv::Mat SceneReaderWebcam::GetScene() {
    if (!cap.isOpened())  // check if we succeeded
        return cv::Mat();
    cap >> m_scene;
    return m_scene;
}
