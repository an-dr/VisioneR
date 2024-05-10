// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/core/core.hpp>
#include "FaceInterface.hpp"
#include "InputInterface.hpp"
#include "InterfaceSceneReader.hpp"
#include "ObjectFinder.hpp"
#include "Visualizer.hpp"
#include "ulog.h"

#include "App.hpp"

using namespace cv;

App::App(FaceInterface *face, InputInterface *input, InterfaceSceneReader *scene_reader)
    : m_face(face), m_input(input), m_scene_input(scene_reader), m_objectFinder(new ObjectFinder),
      m_vis(new Visualizer)
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

cv::Mat App::GetScene()
{
    return m_objectFinder->GetScene();
}

int App::FindObjects(std::vector<cv::Mat> objects, bool show_result)
{
    int found_objects = 0;
    for (auto &object : objects)
    {
        int obj_num = 0;
        Quadrilateral obj = m_objectFinder->Find(object);
        if (obj.GetPerimeter() > 0)
        {
            found_objects++;
            // Remove the object from the scene and update the scene
            m_current_scene = m_vis->SelectAndDismiss(obj);
            
            // Logging
            Point2f center = obj.GetCenter();
            auto area = obj.GetArea();
            auto perimeter = obj.GetPerimeter();
            float a2p = area / perimeter;
            log_info("Object %d! Center: %f-%f. Area:%f. Area/Perimeter: %f",
                          obj_num, center.x, center.y, area, a2p);
            
        }
        obj_num++;
    }
    return found_objects;
}

void App::PreFindAction() {}

int App::RunOnce(bool show_result, bool less_confused)
{

    // Set the new scene
    m_current_scene = m_scene_input->GetScene();
    m_objectFinder->SetScene(m_current_scene);
    m_vis->SetImg(m_current_scene);

    PreFindAction();

    // Find good objects
    int good_objects = FindObjects(m_input->GetGoodObjects(), show_result);
    if (good_objects){
        log_info("👍 Good objects found: %d", good_objects);
    }
    else {
        log_info("No good objects found");
    }
    
    // Find bad objects
    int bad_objects = FindObjects(m_input->GetBadObjects(), show_result);
    if (bad_objects){
        log_info("👎 Bad objects found: %d", bad_objects);
    }
    else {
        log_info("No bad objects found");
    }
    
    // Show
    if (show_result){
        imshow("Scene", m_vis->GetSceneWithSelection());
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
