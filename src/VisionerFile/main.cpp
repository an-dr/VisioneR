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
#include "Face.hpp"
#include "InputFiles.hpp"
#include "ulog.h"

int main(int argc, char **argv)
{
    ulog_set_level(LOG_INFO);
    InputFiles input;
    Face face;
    face.ShowThinking();
    input.LoadFiles("input");

    AppVisioner app(&face, &input);
    
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
