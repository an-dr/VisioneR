// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/core/core.hpp>
#include "ulog.h"
#include "App/InterfaceSceneReader.hpp"
#include "App/App.hpp"

using namespace cv;

App::App(FaceInterface *face, InputInterface *input, InterfaceSceneReader *scene_reader)
    : m_face(face), m_input(input), m_scene_input(scene_reader), m_objectFinder()
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
    int objects = 0;
    for (auto &object : m_input->GetGoodObjects())
    {
        Quadrilateral obj = m_objectFinder.Find(object);
        if (obj.GetPerimeter() > 0)
        {
            Point2f center = obj.GetCenter();
            auto area = obj.GetArea();
            auto perimeter = obj.GetPerimeter();
            float a2p = area / perimeter;
            objects++;
            log_info("Object! Center: %f-%f. Area/Perimeter: %f",
                          center.x, center.y, a2p);
        }
    }
    return objects;
}

int App::FindBadObjects(bool show_result)
{
    int objects = 0;
    for (auto &object : m_input->GetBadObjects())
    {
        Quadrilateral obj = m_objectFinder.Find(object);
        if (obj.GetPerimeter() > 0)
        {
            Point2f center = obj.GetCenter();
            auto area = obj.GetArea();
            auto perimeter = obj.GetPerimeter();
            float a2p = area / perimeter;
            objects++;
            log_info("Object! Center: %f-%f. Area/Perimeter: %f",
                          center.x, center.y, a2p);
        }
    }
    return objects;
}

void App::PreFindAction() {}

int App::RunOnce(bool show_result, bool less_confused)
{

    auto scene_img = m_scene_input->GetScene();
    m_objectFinder.SetScene(scene_img);

    PreFindAction();

    // Good objects
    int good_objects = FindGoodObjects(show_result);
    if (good_objects){
        log_info("👍 Good objects found: %d", good_objects);
    }
    else {
        log_info("No good objects found");
    }
    
    // Bad objects
    int bad_objects = FindBadObjects(show_result);
    if (bad_objects){
        log_info("👎 Bad objects found: %d", bad_objects);
    }
    else {
        log_info("No bad objects found");
    }

    // Reaction
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
