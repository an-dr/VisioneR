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
#include <mutex>
#include <QPixmap>

class MainWindow; // Forward declaration

class Gui
{
public:
    ~Gui();
    void Start();
    
    // Sets image. Thread safe.
    void SetImageLeft(QPixmap &img);
    
    // Sets image. Thread safe.
    void SetImageRight(QPixmap &img);

private:
    static void thread_func(Gui *self);

    MainWindow *m_window;
    std::thread m_thread;
    std::mutex m_mux;
};
