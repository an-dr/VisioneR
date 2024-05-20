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
#include <opencv2/highgui.hpp>
#include <unistd.h>
#include "FaceInterface.hpp"
#include "Gui.hpp"
#include "InputInterface.hpp"

AppVisioner::AppVisioner(FaceInterface *face, InputInterface *input, Gui *gui,
                         InterfaceSceneReader *scene_input)
    : App(face, input, gui, scene_input) {}

void AppVisioner::Delay(int ms) { usleep(ms * 1000); }

void AppVisioner::PreFindAction() { Show("Scene", GetScene()); }
