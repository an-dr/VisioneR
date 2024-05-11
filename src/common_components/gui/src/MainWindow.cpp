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


MainWindow::MainWindow()
{
        // Create QLabel widgets for the images
        QLabel* imageLabel1 = new QLabel(this);
        QLabel* imageLabel2 = new QLabel(this);

        // Load the images (replace with actual file paths)
        QPixmap pixmap1("faces/calm.png");
        QPixmap pixmap2("input/scene_da.jpg");
        
        int width = 640;
        int height = 480;
        QPixmap resizedPixmap1 = pixmap1.scaled(width, height, Qt::KeepAspectRatio);
        QPixmap resizedPixmap2 = pixmap2.scaled(width, height, Qt::KeepAspectRatio);


        // Set the images on the labels
        imageLabel1->setPixmap(resizedPixmap1);
        imageLabel2->setPixmap(resizedPixmap2);
        

        // Set the label positions and sizes
        imageLabel1->setGeometry(10, 10, width, height);
        imageLabel2->setGeometry(660, 10, width, height);

        // Set the main window properties
        setCentralWidget(imageLabel1); // Set imageLabel1 as central widget
        setWindowTitle("VisioneR GUI");
        resize(1320, 500); // Set the window size
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    std::cout << "Bye" << std::endl;
}
