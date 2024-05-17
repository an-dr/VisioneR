// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <QImage>
#include <QPixmap>
#include <mutex>
#include <thread>

class MainWindow;    // Forward declaration
class QApplication;  // Forward declaration

class Gui {
 public:
  ~Gui();
  void Start();
  bool isReady();
  bool isClosed();

  // Sets image. Thread safe.
  void SetImageLeft(QPixmap &img);

  void SetImageLeft(QImage &img);

  // Sets image. Thread safe.
  void SetImageRight(QPixmap &img);
  void SetImageRight(QImage &img);

 private:
  static void thread_func(Gui *self);

  QApplication *m_qapp;
  MainWindow *m_window;
  std::thread m_thread;
  std::mutex m_mux;
};
