// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <thread>
#include "eventpp/eventqueue.h"

#include "FaceInterface.hpp"

enum class EmotionEventType
{
    Thinking,
    Blink,
    Calm,
    Happy,
    Sad,
    Dunno,
    Confused
};

class EmotionEvent
{
    // tbd
};

class FaceApp
{
public:
    FaceApp(FaceInterface &faceActions);
    void SendEvent(EmotionEventType type, const EmotionEvent &event);
    void Start();
    void Stop();
    static void thread_func(FaceApp *self);

private:
    eventpp::EventQueue<EmotionEventType, void(FaceApp *, const EmotionEvent)> m_events;
    static void HandlerBlink(FaceApp *self, const EmotionEvent evt);
    static void HandlerThinking(FaceApp *self, const EmotionEvent evt);
    static void HandlerSad(FaceApp *self, const EmotionEvent evt);
    static void HandlerHappy(FaceApp *self, const EmotionEvent evt);
    static void HandlerConfused(FaceApp *self, const EmotionEvent evt);
    static void HandlerCalm(FaceApp *self, const EmotionEvent evt);
    std::thread *m_thread;
    bool m_stopping;
    FaceInterface *m_actions;
};
