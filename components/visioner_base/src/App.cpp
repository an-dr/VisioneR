// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/core/core.hpp>
#include "App/App.hpp"

using namespace cv;

App::App(FaceInterface *face, InputInterface *input)
    : m_face(face), m_input(input), m_objectFinder()
{
}

void App::Intro()
{
    m_face->ShowCalm(1000);
    m_face->ShowBlink(200);
    m_face->ShowCalm(1000);
    m_face->ShowBlink(200);
    m_face->ShowCalm(1000);
}

int App::FindGoodObjects(bool show_result)
{
    int good_objects = 0;
    for (auto &object : m_input->GetGoodObjects())
    {
        Point2f result;
        if (m_objectFinder.Find(object, result, show_result))
        {
            good_objects++;
            printf("Good object found: %f %f\n", result.x, result.y);
        }
        else
        {
            printf("Good object not found\n");
        }
        printf("Good objects found: %d\n", good_objects);
    }
    return good_objects;
}

int App::FindBadObjects(bool show_result)
{
    int bad_objects = 0;
    for (auto &object : m_input->GetBadObjects())
    {
        Point2f result;
        if (m_objectFinder.Find(object, result, show_result))
        {
            bad_objects++;
            printf("Bad object found: %f %f\n", result.x, result.y);
        }
        else
        {
            printf("Bad object not found\n");
        }
        printf("Bad objects found: %d\n", bad_objects);
    }
    return bad_objects;
}

void App::PreFindAction() {}

int App::RunOnce(bool show_result, bool less_confused)
{

    auto scene_img = m_input->GetScene();
    m_objectFinder.SetScene(scene_img);

    PreFindAction();

    int good_objects = FindGoodObjects(show_result);
    int bad_objects = FindBadObjects(show_result);

    if (good_objects == 0 && bad_objects == 0)
    {
        if (less_confused)
        {
            m_face->ShowCalm(1);
        }
        else
        {
            m_face->ShowDunno(1);
        }
        return -1;
    }

    if (good_objects > bad_objects)
    {
        m_face->ShowHappy(1);
        return 1;
    }
    else if (good_objects < bad_objects)
    {
        m_face->ShowSad(1);
        return 2;
    }
    else
    {
        m_face->ShowConfused(1);
        return 0;
    }
}