// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include "ObjectFinder.hpp"
#include "FaceInterface.hpp"
#include "InputInterface.hpp"
#include "InterfaceSceneReader.hpp"
#include "Visualizer.hpp"

class App
{
public:
    App(FaceInterface *face, InputInterface *input, InterfaceSceneReader *scene_input = nullptr);
    virtual int RunOnce(bool show_result = true, bool less_confused = false);
    virtual void Intro();
    virtual void Delay(int ms) = 0;
    ~App() = default;

protected:
    ObjectFinder m_objectFinder;
    FaceInterface *m_face;
    InputInterface *m_input;
    InterfaceSceneReader *m_scene_input;
    cv::Mat m_current_scene;
    Visualizer m_vis;

private:
    virtual int FindObjects(std::vector<cv::Mat> objects, bool show_result = true);
    virtual void PreFindAction();
};
