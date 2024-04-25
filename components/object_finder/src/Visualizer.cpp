// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/opencv.hpp>
#include "Visualizer.hpp"

void Visualizer::SetImg(cv::Mat img)
{
    m_img_orig = img;
    m_img_selection = img;
    m_img_dismissed = img;
}

cv::Mat Visualizer::SelectAndDismiss(Quadrilateral selection)
{

    return m_img_dismissed;
}

void Visualizer::DrawQuadrilateral(cv::Mat &img,
                                          Quadrilateral selection, 
                                          bool crossed,
                                          cv::Scalar color,
                                          int thickness)
{
    cv::line(img, selection[1], selection[2], color, thickness);
    cv::line(img, selection[2], selection[3], color, thickness);
    cv::line(img, selection[3], selection[4], color, thickness);
    cv::line(img, selection[4], selection[1], color, thickness);

    if (crossed)
    {
        cv::line(img, selection[1], selection[3], color, thickness);
        cv::line(img, selection[2], selection[4], color, thickness);
    }
}

void Visualizer::ClearQuadrilateral(cv::Mat &img, Quadrilateral selection)
{
    cv::fillPoly(img, selection.GetSides(),Scalar(0, 0, 0));
    
}
