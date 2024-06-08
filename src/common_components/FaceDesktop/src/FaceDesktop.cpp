// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************
#include <chrono>
#include <stdexcept>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <stdint.h>
#include <unistd.h>

#include "FaceDesktop.hpp"

using namespace cv;
using namespace std::chrono;

FaceDesktop::FaceDesktop(Gui &gui)
    : m_images({}), m_gui(&gui), m_exit(false), m_show_count(0) {
    // Load all images by the paths from m_img_paths
    for (auto &img : m_img_paths) {
        m_images[img.first] = QImage(img.second.c_str());
        if (m_images[img.first].isNull()) {
            printf("Error: can't load image %s\n", img.second.c_str());
            throw std::runtime_error("Can't load image");
        }
    }
}

void FaceDesktop::ShowThinking() {
    int w_time = 350;
    m_gui->SetImageLeft(m_images["thinking1"]);
    Delay(w_time);
    m_gui->SetImageLeft(m_images["thinking2"]);
    Delay(w_time);
    m_gui->SetImageLeft(m_images["thinking3"]);
    Delay(w_time);
}

void FaceDesktop::ShowBlink(int delay) {
    m_gui->SetImageLeft(m_images["blink"]);
    Delay(delay);
}

void FaceDesktop::ShowCalm(int delay) {
    m_gui->SetImageLeft(m_images["calm"]);
    Delay(delay);
}

void FaceDesktop::ShowHappy(int delay) {
    m_gui->SetImageLeft(m_images["happy"]);
    Delay(delay);
}

void FaceDesktop::ShowSad(int delay) {
    m_gui->SetImageLeft(m_images["sad"]);
    Delay(delay);
}

void FaceDesktop::ShowDunno(int delay) {
    m_gui->SetImageLeft(m_images["dunno"]);
    Delay(delay);
}

void FaceDesktop::ShowConfused(int delay) {
    m_gui->SetImageLeft(m_images["confused"]);
    Delay(delay);
}

bool FaceDesktop::IsExit() { return m_exit; }

QPixmap FaceDesktop::ToQPixmap(const cv::Mat mat) {
    auto img = QImage((unsigned char *)mat.data, mat.cols, mat.rows,
                      QImage::Format_RGB888);
    return QPixmap::fromImage(img);
}

void FaceDesktop::Delay(int delay) {
    usleep(1000 * delay);
}

uint64_t FaceDesktop::GetTimeMs() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
}
