// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include "App/App.hpp"
#include "App/FaceInterface.hpp"
#include "App/InputInterface.hpp"
#include "App/InterfaceSceneReader.hpp"

class AppVisioner : public App
{
public:
    AppVisioner(FaceInterface *face, InputInterface *input, InterfaceSceneReader *scene_input);
    void Delay(int ms) override;
    void PreFindAction() override;
    ~AppVisioner() = default;
};
