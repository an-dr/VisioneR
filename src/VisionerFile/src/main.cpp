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

int main(int argc, char **argv)
{
    ulog_set_level(LOG_INFO);
    InputFiles input;
    FaceDesktop face;
    SceneReaderFileSystem scene_input;
    face.ShowThinking();
    input.LoadFiles("input");
    scene_input.SetPath("input");

    AppVisioner app(&face, &input, &scene_input);
    app.Start(3000);
    
    while(!face.IsExit());
    return 0;
}
