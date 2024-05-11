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
#include "SceneReaderFileSystem.hpp"
#include "ulog.h"
#include "Gui.hpp"
#include <unistd.h>


int main(int argc, char **argv)
{
    Gui gui;
    gui.Start();

    ulog_set_level(LOG_INFO);
    InputFiles input;
    SceneReaderFileSystem scene_input;
    sleep(2); // BUG: find what is not inited
    FaceDesktop face(gui);
    sleep(2); // BUG: find what is not inited
    face.ShowThinking();
    input.LoadFiles("input");
    scene_input.SetPath("input");
    
    // int i = 0;
    // while(1){
    //     printf("%d\n", i++);
    // }

    AppVisioner app(&face, &input, &gui, &scene_input);
    
    // Until the face is not exiting
    int result = 0;
    while(!face.IsExit())
    {
        result = app.RunOnce();
        printf("\n");
        app.Delay(3000);
    }
    return 0;
}
