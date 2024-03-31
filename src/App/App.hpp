// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include "ObjectFinder.hpp"
#include "FaceInterface.hpp"
#include "InputInterface.hpp"

class App
{
public:
    App(FaceInterface *face, InputInterface *input);
    virtual int RunOnce();
    virtual void Intro();
    virtual void Delay(int ms) = 0;
    ~App() = default;

protected:
private:
    virtual int FindGoodObjects();
    virtual int FindBadObjects();

    ObjectFinder m_objectFinder;
    FaceInterface *m_face;
    InputInterface *m_input;
};
