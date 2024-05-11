// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "FaceApp.hpp"
#include <thread>
#include <unistd.h>
#include <iostream>

using namespace std;

FaceApp::FaceApp(FaceInterface &faceActions) : m_thread(nullptr),
                                               m_stopping(false),
                                               m_actions(&faceActions)
{
    m_events.appendListener(EmotionEventType::Blink, HandlerBlink);
    m_events.appendListener(EmotionEventType::Thinking, HandlerThinking);
    m_events.appendListener(EmotionEventType::Calm, HandlerCalm);
    m_events.appendListener(EmotionEventType::Happy, HandlerHappy);
    m_events.appendListener(EmotionEventType::Sad, HandlerSad);
    m_events.appendListener(EmotionEventType::Confused, HandlerConfused);
    // m_events.appendListener(EmotionEventType::Dunno, m_actions->ShowDunno);
}

void FaceApp::SendEvent(EmotionEventType type, const EmotionEvent &event)
{
    m_events.enqueue(type, this, event);
}

void FaceApp::Start()
{
    m_stopping = false;
    if (m_thread != nullptr)
    {
        delete m_thread;
    }
    m_thread = new thread(thread_func, this);
}

void FaceApp::Stop()
{
    m_stopping = true;
}

void FaceApp::thread_func(FaceApp *self)
{
    while (1)
    {
        if (!(self->m_events.processOne()))
        {
            self->m_actions->ShowCalm(1);
        }
    }
}

void FaceApp::HandlerBlink(FaceApp *self, const EmotionEvent evt)
{
    cout << __FUNCTION__;
    self->m_actions->ShowBlink(100);
}

void FaceApp::HandlerThinking(FaceApp *self, const EmotionEvent evt)
{
    cout << __FUNCTION__;
    self->m_actions->ShowThinking();
}

void FaceApp::HandlerSad(FaceApp *self, const EmotionEvent evt)
{
    cout << __FUNCTION__;
    self->m_actions->ShowSad(3000);
}

void FaceApp::HandlerHappy(FaceApp *self, const EmotionEvent evt)
{
    cout << __FUNCTION__;
    self->m_actions->ShowHappy(3000);
}

void FaceApp::HandlerConfused(FaceApp *self, const EmotionEvent evt)
{
    cout << __FUNCTION__;
    self->m_actions->ShowConfused(3000);
}

void FaceApp::HandlerCalm(FaceApp *self, const EmotionEvent evt)
{
    cout << __FUNCTION__;
    self->m_actions->ShowCalm(1);
}
