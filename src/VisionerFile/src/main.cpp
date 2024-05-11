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
#include "FaceApp.hpp"
#include "FaceDesktop.hpp"
#include "InputFiles.hpp"
#include "SceneReaderFileSystem.hpp"
#include "ulog.h"
#include "eventpp/eventqueue.h"


int main(int argc, char **argv)
{
    // event_test();
    // return 0;
    ulog_set_level(LOG_INFO);
    InputFiles input;
    FaceDesktop face_actions;
    FaceApp app_face(face_actions);
    app_face.Start();

    // app_face.SendEvent(EmotionEventType::Thinking, EmotionEvent());
    // app_face.SendEvent(EmotionEventType::Blink, EmotionEvent());
    // app_face.SendEvent(EmotionEventType::Thinking, EmotionEvent());
    // app_face.SendEvent(EmotionEventType::Thinking, EmotionEvent());


    SceneReaderFileSystem scene_input;
    face_actions.ShowThinking();
    input.LoadFiles("input");
    scene_input.SetPath("input");

    AppVisioner app(&app_face, &input, &scene_input);
    app.Start(1000);

    while (!face_actions.IsExit())
        ;
    return 0;
}
