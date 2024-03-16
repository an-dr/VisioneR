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

#include <opencv2/calib3d/calib3d.hpp> // for homography
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // for wrapPerspective
#include <opencv2/opencv_modules.hpp>

#include "ObjectFinder.hpp"
#include "Face.hpp"

using namespace cv;

void proto_recognition()
{
    Mat objectImg = imread("img_obj.jpg");
    Mat sceneImg = imread("img_scene_many.jpg");

    ObjectFinder of;
    of.SetScene(sceneImg);

    Point2f result;
    of.Find(objectImg, result);
    printf("Result: %f %f\n", result.x, result.y);
}

void proto_face()
{
    Face face;
    
    face.ShowCalm();
    face.ShowHappy();
    face.ShowSad();
    face.ShowDunno();
    face.ShowThinking();
    face.ShowThinking();
}

int main(int argc, char **argv)
{
    proto_recognition();
    proto_face();
    return 0;
}
