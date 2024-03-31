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
    m_face->ShowCalm(1000);
    m_face->ShowBlink(200);
    m_face->ShowCalm(1000);
    m_face->ShowBlink(200);
    m_face->ShowCalm(1000);
}

int App::FindGoodObjects()
{
    int good_objects = 0;
    for (auto &object : m_input->GetGoodObjects())
    {
        Point2f result;
        if (m_objectFinder.Find(object, result))
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

int App::FindBadObjects()
{
    int bad_objects = 0;
    for (auto &object : m_input->GetBadObjects())
    {
        Point2f result;
        if (m_objectFinder.Find(object, result))
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

void App::PreFindAction() { }

int App::RunOnce()
{

    auto scene_img = m_input->GetScene();
    m_objectFinder.SetScene(scene_img);
    
    PreFindAction();

    int good_objects = FindGoodObjects();
    int bad_objects = FindBadObjects();

    if (good_objects == 0 && bad_objects == 0)
    {
        m_face->ShowDunno(3000);
        return -1;
    }

    if (good_objects > bad_objects)
    {
        m_face->ShowHappy(3000);
        return 1;
    }
    else if (good_objects < bad_objects)
    {
        m_face->ShowSad(3000);
        return 2;
    }
    else
    {
        m_face->ShowConfused(3000);
        return 0;
    }
}
