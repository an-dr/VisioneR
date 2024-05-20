// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <QMainWindow>
#include <string>

// Forward declarations
class QLabel;
class QPixmap;

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    MainWindow();
    void SetImageLeft(std::string path);
    void SetImageLeft(const QPixmap &img);
    void SetImageRight(std::string path);
    void SetImageRight(const QPixmap &img);
    bool isClosed();
    ~MainWindow();

 protected:
    static const int LEFT_W = 640;
    static const int LEFT_H = 480;
    static const int RIGHT_W = 640;
    static const int RIGHT_H = 480;

    void closeEvent(QCloseEvent *event);

 private:
    QLabel *m_imageLeft;
    QLabel *m_imageRight;
    bool m_closed;
    void keyPressEvent(QKeyEvent *event) override;
};
