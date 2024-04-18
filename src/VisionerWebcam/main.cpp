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
#include "InputWebcam.hpp"

int main(int argc, char **argv)
{
    InputWebcam input;
    Face face;
    face.ShowThinking();
    input.LoadFiles("input");

    AppVisioner app(&face, &input);
    app.Intro();
    
    // Until the face is not exiting
    int result = 0;
    while(!face.IsExit())
    {
        result = app.RunOnce(true);
    }
    return 0;
}
