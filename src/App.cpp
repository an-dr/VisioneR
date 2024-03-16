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

#include <stdint.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#include "ObjectFinder.hpp"
#include "Face.hpp"

using namespace cv;

int App()
{
    //Init
    Face face;
    face.ShowThinking();
    face.ShowCalm(3000);
    face.ShowHappy(500);
    face.ShowSad(500);
    face.ShowDunno(500);
    face.ShowThinking();
    face.ShowThinking();
    face.ShowThinking();
    
    // Image recognition
    Mat objectImg = imread("img_obj.jpg");
    Mat sceneImg = imread("img_scene.jpg");

    ObjectFinder of;
    of.SetScene(sceneImg);
    
    Point2f result;
    of.Find(objectImg, result);
    
    // Reporting result
    printf("Result: %f %f\n", result.x, result.y);
    face.ShowHappy(10000);
    
    return 0;
}
