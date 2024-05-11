// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include "App.hpp"
#include "FaceInterface.hpp"
#include "InputInterface.hpp"
#include "InterfaceSceneReader.hpp"

class AppVisioner : public App
{
public:
    AppVisioner(FaceApp *face, InputInterface *input, InterfaceSceneReader *scene_input);
    void Delay(int ms) override;
    void PreFindAction() override;
    ~AppVisioner() = default;
};
