// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <opencv2/opencv.hpp>
#include <QImage>
#include "FaceInterface.hpp"
#include "InputInterface.hpp"
#include "InterfaceSceneReader.hpp"

// Forward declaration
class ObjectFinder;
class Visualizer;
class Gui;


class App
{
public:
    App(FaceInterface *face, InputInterface *input, Gui * gui, InterfaceSceneReader *scene_input = nullptr);
    virtual int RunOnce(bool show_result = true, bool less_confused = false);
    virtual void Intro();
    virtual void Delay(int ms) = 0;
    ~App() = default;

protected:
    cv::Mat GetScene();
    QImage ToQImage(cv::Mat &cv_mat);
    void Show(std::string title, cv::Mat cv_img);
    
    ObjectFinder *m_objectFinder;
    Visualizer *m_vis;
    FaceInterface *m_face;
    InputInterface *m_input;
    InterfaceSceneReader *m_scene_input;
    Gui *m_gui;
    cv::Mat m_current_scene;

private:
    
    virtual int FindObjects(std::vector<cv::Mat> objects, bool show_result = true);
    virtual void PreFindAction();
};
