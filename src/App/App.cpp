// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/core/core.hpp>
#include "App.hpp"

using namespace cv;

App::App(FaceInterface *face, InputInterface *input)
    : m_face(face), m_input(input), m_objectFinder()
{
}

void App::Intro()
{
    m_face->ShowThinking();
    m_face->ShowCalm(3000);
    m_face->ShowBlink(500);
    m_face->ShowCalm(1000);
    m_face->ShowBlink(500);
    m_face->ShowCalm(1000);
}

void App::Outro()
{
    m_face->ShowCalm(1000);
    m_face->ShowBlink(500);
    m_face->ShowCalm(1000);
    m_face->ShowHappy(10000);
}

int App::RunOnce()
{

    auto scene_img = m_input->GetScene();
    m_objectFinder.SetScene(scene_img);
    m_face->ShowCalm(1000);

    for (auto &object : m_input->GetObjects())
    {
        Point2f result;
        m_face->ShowThinking();
        m_objectFinder.Find(object, result);
        printf("Result: %f %f\n", result.x, result.y);
        m_face->ShowCalm(1000);
    }
    return 0;
}
