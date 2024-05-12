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

#include "MainWindow.hpp"
#include <QApplication>
#include <thread>
#include <pthread.h>
#include <iostream>

#include "Gui.hpp"

void Gui::Start()
{
    m_thread = std::thread(thread_func, this);
    while (!isReady());
}

Gui::~Gui()
{
    m_thread.join();
}

bool Gui::isReady()
{
    if (m_qapp == nullptr)
    {
        return false;
    }
    return !(m_qapp->startingUp());
}

bool Gui::isClosed()
{
    if (m_window == nullptr)
    {
        return true;
    }
    return m_window->isClosed();
}

void Gui::SetImageLeft(QPixmap &img)
{
    if (m_window != nullptr)
    {
        m_mux.lock();
        m_window->SetImageLeft(img);
        m_mux.unlock();
    }
}

void Gui::SetImageLeft(QImage &img)
{
    int w = img.width();
    QPixmap pixmap;
    pixmap.convertFromImage(img);
    w = pixmap.width();
    SetImageLeft(pixmap);
}

void Gui::SetImageRight(QImage &img)
{
    QPixmap pixmap;
    pixmap.convertFromImage(img);
    SetImageRight(pixmap);
}

void Gui::SetImageRight(QPixmap &img)
{
    if (m_window != nullptr)
    {
        m_mux.lock();
        m_window->SetImageRight(img);
        m_mux.unlock();
    }
}

void Gui::thread_func(Gui *self)
{
    int argc = 0;
    char **argv = {};
    // Name the thread
    pthread_setname_np(pthread_self(), "Gui"); 
    
    self->m_qapp = new QApplication(argc, argv);
    self->m_window = new MainWindow;
    self->m_window->show();
    self->m_qapp->exec();
    std::cout<< "Gui Closed" <<std::endl;
}
