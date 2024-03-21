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

#include <opencv2/highgui.hpp>
#include "App/FaceInterface.hpp"
#include "App/InputInterface.hpp"
#include "AppVisioner.hpp"


AppVisioner::AppVisioner(FaceInterface *face, InputInterface *input)
    : App(face, input)
{
}

void AppVisioner::Delay(int ms)
{
    cv::waitKey(ms);
}