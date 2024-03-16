// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdexcept>
#include "Face.hpp"

using namespace cv;

Face::Face()
{
    // Load all images by the paths from m_img_paths
    for (auto &img : m_img_paths)
    {
        m_images[img.first] = imread(img.second);
        if (m_images[img.first].empty())
        {
            printf("Error: can't load image %s\n", img.second.c_str());
            throw std::runtime_error("Can't load image");
        }
    }

    // Create window
    namedWindow(WIN_NAME, WINDOW_GUI_EXPANDED);
    ShowCalm(1);
    resizeWindow(WIN_NAME, WIN_SIZE_X, WIN_SIZE_Y);
}

void Face::ShowThinking()
{
    int w_time = 350;
    imshow(WIN_NAME, m_images["thinking1"]);
    Wait(w_time);
    imshow(WIN_NAME, m_images["thinking2"]);
    Wait(w_time);
    imshow(WIN_NAME, m_images["thinking3"]);
    Wait(w_time);
}

void Face::ShowBlink(int delay)
{
    imshow(WIN_NAME, m_images["blink"]);
    Wait(delay);
}

void Face::ShowCalm(int delay)
{
    imshow(WIN_NAME, m_images["calm"]);
    Wait(delay);
}

void Face::ShowHappy(int delay)
{
    imshow(WIN_NAME, m_images["happy"]);
    Wait(delay);
}

void Face::ShowSad(int delay)
{
    imshow(WIN_NAME, m_images["sad"]);
    Wait(delay);
}

void Face::ShowDunno(int delay)
{
    imshow(WIN_NAME, m_images["dunno"]);
    Wait(delay);
}

void Face::Wait(int delay)
{
    if (waitKey(delay) == 27) // ESC
    {
        m_exit = true;
    }
}
