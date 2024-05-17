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
#include "Gui.hpp"
#include "InputFiles.hpp"
#include "SceneReaderFileSystem.hpp"
#include "ulog.h"

#include <csignal>  // for handling abort
#include <iostream>
#include <pthread.h>
#include <unistd.h>

// void abort_handler(int) {
//     std::cout << "Aborted" <<std::endl;
//     // std::string_view msg = "Abort handler invoked\n";
//     // // Signal handlers are extremely limited, one of
//     // // the few ways to iteract with the outside
//     // // environment is using write() which requires POSIX.
//     // write(2, msg.data(), msg.length());
//     // // We can prevent abnormal program termination by:
//     // // std::_Exit(EXIT_FAILURE);
// }

int main(int argc, char **argv) {
  // Name the thread
  pthread_setname_np(pthread_self(), "Main");
  // std::signal(SIGABRT, abort_handler);

  Gui gui;
  gui.Start();

  ulog_set_level(LOG_INFO);
  InputFiles input;
  SceneReaderFileSystem scene_input;
  FaceDesktop face(gui);
  face.ShowThinking();
  input.LoadFiles("input");
  scene_input.SetPath("input");

  // int i = 0;
  // while(1){
  //     printf("%d\n", i++);
  // }

  AppVisioner app(&face, &input, &gui, &scene_input);

  // Until the face is not exiting
  int result = 0;
  while (!gui.isClosed()) {
    result = app.RunOnce();
    printf("\n");
    app.Delay(3000);
  }
  printf("Main thread is closed\n");
  return 0;
}
