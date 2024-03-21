// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#include "Input/InputInterface.hpp"
#include "ObjectFinder.hpp"
#include "Face.hpp"

using namespace cv;

static Face face;
static ObjectFinder of;
static Mat objectImg;
static Mat sceneImg;

void Init()
{
    // Init
    face.ShowThinking();
    face.ShowCalm(3000);
    face.ShowBlink(500);
    face.ShowCalm(1000);
    face.ShowBlink(500);
    face.ShowCalm(1000);
    // Image recognition
    // objectImg = imread("img_obj.jpg");
    // sceneImg = imread("img_scene.jpg");
    //
    // of.SetScene(sceneImg);
}

void Find()
{
    Point2f result;
    of.Find(objectImg, result);

    // Reporting result
    printf("Result: %f %f\n", result.x, result.y);
    face.ShowHappy(10000);
}

int App(InputInterface *input)
{

    Init();

    while (!face.IsExit())
    {
        auto scene_img = input->GetScene();
        of.SetScene(scene_img);
        face.ShowCalm(1000);

        for (auto &object : input->GetObjects())
        {
            Point2f result;
            face.ShowThinking();
            of.Find(object, result);
            printf("Result: %f %f\n", result.x, result.y);
            face.ShowCalm(1000);
            destroyWindow("Keypoints");
        }
        face.ShowCalm(1000);
        face.ShowBlink(500);
        face.ShowCalm(1000);
        face.ShowHappy(10000);
    }
    return 0;
}
