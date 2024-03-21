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
#include "App/FaceInterface.hpp"

class Face : public FaceInterface
{

public:
    static const int WIN_SIZE_X = 500;
    static const int WIN_SIZE_Y = 256;
    static constexpr char WIN_NAME[] = "VisioneR";
    std::map<std::string, std::string> m_img_paths = {
        {"thinking1", "assets/thinking1.png"},
        {"thinking2", "assets/thinking2.png"},
        {"thinking3", "assets/thinking3.png"},
        {"blink", "assets/blink.png"},
        {"calm", "assets/calm.png"},
        {"happy", "assets/happy.png"},
        {"sad", "assets/sad.png"},
        {"dunno", "assets/dunno.png"}};

    Face();
    void ShowThinking() override;
    void ShowBlink(int delay = 500) override;
    void ShowCalm(int delay = 500) override;
    void ShowHappy(int delay = 500) override;
    void ShowSad(int delay = 500) override;
    void ShowDunno(int delay = 500) override;
    bool IsExit();

private:
    static const int WAIT_DELTA = 100;
    void Delay(int delay) override;
    uint64_t GetTimeMs();

    std::map<std::string, cv::Mat> m_images;
    bool m_exit = false;
    int m_show_count = 0;
};
