// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/opencv.hpp>
#include <stdio.h>

#include "Tetrangle.hpp"
#include "tools.hpp"

float CalculateDistance(cv::Point2f &p_a, cv::Point2f &p_b)
{
    return sqrt(pow(p_a.x - p_b.x, 2) + pow(p_a.y - p_b.y, 2));
}

bool VerifyTetrangleSize(cv::Point2f &p1, cv::Point2f &p2,
                         cv::Point2f &p3, cv::Point2f &p4,
                         float minSize)
{
    float d1 = CalculateDistance(p1, p2);
    float d2 = CalculateDistance(p2, p3);
    float d3 = CalculateDistance(p3, p4);
    float d4 = CalculateDistance(p4, p1);

    float min = d1;
    if (d2 < min)
        min = d2;
    if (d3 < min)
        min = d3;
    if (d4 < min)
        min = d4;

    if (min < minSize)
    {
        printf("Error: object is too small\n");
        return false;
    }
    printf("Min object dimension: %.2f\n", min);
    return true;
}

bool CalculateLinesIntersection(cv::Point2f &line1_p1, cv::Point2f &line1_p2,
                                cv::Point2f &line2_p1, cv::Point2f &line2_p2,
                                cv::Point2f &result_point)
{
    float x11 = line1_p1.x, y11 = line1_p1.y, x12 = line1_p2.x, y12 = line1_p2.y;
    float x21 = line2_p1.x, y21 = line2_p1.y, x22 = line2_p2.x, y22 = line2_p2.y;

    // Solving using y = ax + b for two lines
    float a1 = (y12 - y11) / (x12 - x11);
    float b1 = y11 - a1 * x11;
    float a2 = (y22 - y21) / (x22 - x21);
    float b2 = y21 - a2 * x21;

    if (a1 == a2)
    {
        printf("Error: parallel lines\n");
        return false;
    }

    result_point.x = (b2 - b1) / (a1 - a2);
    result_point.y = a1 * result_point.x + b1;
    return true;
}

void DrawTetrangle(cv::Mat &img,
                   cv::Point2f &p1,
                   cv::Point2f &p2,
                   cv::Point2f &p3,
                   cv::Point2f &p4,
                   bool crossed,
                   cv::Scalar color,
                   int thickness)
{
    cv::line(img, p1, p2, color, thickness);
    cv::line(img, p2, p3, color, thickness);
    cv::line(img, p3, p4, color, thickness);
    cv::line(img, p4, p1, color, thickness);

    if (crossed)
    {
        cv::line(img, p1, p3, color, thickness);
        cv::line(img, p2, p4, color, thickness);
    }
}

void DrawTetrangle(cv::Mat &img,
                   Tetrangle &tetrangle,
                   bool crossed,
                   cv::Scalar color,
                   int thickness)
{
    DrawTetrangle(img,
                  tetrangle[1], tetrangle[2], tetrangle[3], tetrangle[4],
                  false, color, thickness);
}
