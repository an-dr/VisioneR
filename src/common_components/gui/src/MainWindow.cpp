// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include "MainWindow.hpp"
#include <iostream>
#include <QEvent>
#include <QKeyEvent>

MainWindow::MainWindow() : m_imageLeft(nullptr), m_imageRight(nullptr), m_closed(false)
{
    // Create QLabel widgets for the images
    m_imageLeft = new QLabel(this);
    m_imageRight = new QLabel(this);

    // Set the label positions and sizes
    m_imageLeft->setGeometry(10, 10, LEFT_W, LEFT_H);
    m_imageRight->setGeometry(20 + RIGHT_W, 10, RIGHT_W, RIGHT_H);

    // Set the main window properties
    setCentralWidget(m_imageLeft); // Set imageLabel1 as central widget
    setWindowTitle("VisioneR GUI");
    resize(2 * 20 + LEFT_W + RIGHT_W, RIGHT_H + 20); // Set the window size

    // Load the images (replace with actual file paths)
    SetImageLeft("faces/calm.png");
    SetImageRight("faces/blink.png");
}

void MainWindow::SetImageLeft(std::string path)
{
    QPixmap img(path.c_str());
    SetImageLeft(img);
}

void MainWindow::SetImageRight(std::string path)
{
    QPixmap img(path.c_str());
    SetImageRight(img);
}

void MainWindow::SetImageLeft(QPixmap &img)
{
    // Resize and set
    QPixmap resizedImg = img.scaled(LEFT_W, LEFT_H, Qt::KeepAspectRatio);
    m_imageLeft->setPixmap(resizedImg);
}

void MainWindow::SetImageRight(QPixmap &img)
{
    // Resize and set
    QPixmap resizedImg = img.scaled(RIGHT_W, RIGHT_H, Qt::KeepAspectRatio);
    m_imageRight->setPixmap(resizedImg);
}

bool MainWindow::isClosed()
{
    return m_closed;
}

MainWindow::~MainWindow()
{
    delete m_imageLeft;
    delete m_imageRight;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_closed = true;
    std::cout << "Bye" << std::endl;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close()
    }
}
