// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

class FaceInterface {
 public:
    virtual void ShowThinking() = 0;
    virtual void ShowBlink(int delay = 500) = 0;
    virtual void ShowCalm(int delay = 500) = 0;
    virtual void ShowHappy(int delay = 500) = 0;
    virtual void ShowSad(int delay = 500) = 0;
    virtual void ShowDunno(int delay = 500) = 0;
    virtual void ShowConfused(int delay = 500) = 0;
    virtual void Delay(int ms) = 0;
    virtual ~FaceInterface() = default;
};
