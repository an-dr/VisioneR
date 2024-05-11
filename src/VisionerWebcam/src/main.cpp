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
#include "FaceDesktop.hpp"
#include "InputFiles.hpp"
#include "SceneReaderWebcam.hpp"
#include "ulog.h"
#include "Gui.hpp"

int main(int argc, char **argv)
{
    Gui gui;
    gui.Start();
    
    ulog_set_level(LOG_INFO);
    InputFiles input;
    FaceDesktop face(gui);
    SceneReaderWebcam scene_input;
    
    input.LoadFiles("input");

    AppVisioner app(&face, &input, &gui, &scene_input);
    // app.Intro();
    
    // Until the face is not exiting
    int result = 0;
    while(!face.IsExit())
    {
        result = app.RunOnce(true, true);
    }
    return 0;
}
