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

#include "AppVisioner.hpp"
#include "App/FaceDesktop.hpp"
#include "App/InputFiles.hpp"
#include "SceneReaderWebcam.hpp"
#include "ulog.h"

int main(int argc, char **argv)
{
    
    ulog_set_level(LOG_INFO);
    InputFiles input;
    FaceDesktop face;
    SceneReaderWebcam scene_input;
    
    input.LoadFiles("input");

    AppVisioner app(&face, &input, &scene_input);
    app.Intro();
    
    // Until the face is not exiting
    int result = 0;
    while(!face.IsExit())
    {
        result = app.RunOnce(true, true);
    }
    return 0;
}
