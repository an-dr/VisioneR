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
#include "FaceDesktop.hpp"
#include "InputFiles.hpp"
#include "SceneReaderFileSystem.hpp"
#include "ulog.h"
#include "eventpp/eventqueue.h"

enum class MyEventType
{
    ev1,
    ev2,
    ev3,
};

struct MyEvent
{
    MyEventType type;
    int data;
};

struct MyEventPolicies
{
    static MyEventType getEvent(const MyEvent &e)
    {
        return e.type;
    }
};

void func3(const std::string s, bool b)
{
    std::cout << std::boolalpha << "Got event 3, s is " << s << " b is " << b << std::endl;
}

void func5(const std::string s, bool b)
{
    std::cout << std::boolalpha << "Got event 5, s is " << s << " b is " << b << std::endl;
}

void event_test()
{
    eventpp::EventQueue<int, void(const std::string &, const bool)> queue;

    queue.appendListener(3, func3);
    queue.appendListener(5, func5);

    // The listeners are not triggered during enqueue.
    queue.enqueue(3, "Hello", true);
    queue.enqueue(5, "World", false);

    // Process the event queue, dispatch all queued events.
    queue.process();
}

int main(int argc, char **argv)
{
    event_test();
    return 0;
    ulog_set_level(LOG_INFO);
    InputFiles input;
    FaceDesktop face;
    SceneReaderFileSystem scene_input;
    face.ShowThinking();
    input.LoadFiles("input");
    scene_input.SetPath("input");

    AppVisioner app(&face, &input, &scene_input);
    app.Start(3000);

    while (!face.IsExit())
        ;
    return 0;
}
