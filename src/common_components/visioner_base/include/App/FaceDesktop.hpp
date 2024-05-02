// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <map>
#include <opencv2/core/core.hpp>
#include <stdint.h>
#include <string>
#include "FaceInterface.hpp"

class FaceDesktop : public FaceInterface
{

public:
    static const int WIN_SIZE_X = 500;
    static const int WIN_SIZE_Y = 256;
    static constexpr char WIN_NAME[] = "VisioneR";
    std::map<std::string, std::string> m_img_paths = {
        {"thinking1", "faces/thinking1.png"},
        {"thinking2", "faces/thinking2.png"},
        {"thinking3", "faces/thinking3.png"},
        {"blink", "faces/blink.png"},
        {"calm", "faces/calm.png"},
        {"happy", "faces/happy.png"},
        {"sad", "faces/sad.png"},
        {"dunno", "faces/dunno.png"},
        {"confused", "faces/confused.png"} };

    FaceDesktop();
    void ShowThinking() override;
    void ShowBlink(int delay = 500) override;
    void ShowCalm(int delay = 500) override;
    void ShowHappy(int delay = 500) override;
    void ShowSad(int delay = 500) override;
    void ShowDunno(int delay = 500) override;
    void ShowConfused(int delay = 500) override;
    bool IsExit();

private:
    static const int WAIT_DELTA = 100;
    void Delay(int delay) override;
    uint64_t GetTimeMs();

    std::map<std::string, cv::Mat> m_images;
    bool m_exit = false;
    int m_show_count = 0;
};
