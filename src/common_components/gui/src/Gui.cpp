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

#include "Gui.hpp"

void Gui::Start()
{
    m_thread = std::thread(thread_func, this);
}

Gui::~Gui()
{
    delete m_window;
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
    QApplication GUI(argc, argv);
    self->m_window = new MainWindow;
    self->m_window->show();
    GUI.exec();
}
