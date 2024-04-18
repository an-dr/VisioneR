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
    virtual int RunOnce(bool show_result = true, bool less_confused = false);
    virtual void Intro();
    virtual void Delay(int ms) = 0;
    ~App() = default;

protected:
    ObjectFinder m_objectFinder;
    FaceInterface *m_face;
    InputInterface *m_input;
    
private:
    virtual int FindGoodObjects(bool show_result = true);
    virtual int FindBadObjects(bool show_result = true);
    virtual void PreFindAction();

};
