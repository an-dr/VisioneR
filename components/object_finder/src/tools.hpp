// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <opencv2/opencv.hpp>

bool CalculateLinesIntersection(cv::Point2f &p1,
                                cv::Point2f &p2,
                                cv::Point2f &p3,
                                cv::Point2f &p4,
                                cv::Point2f &r);

float CalculateDistance(cv::Point2f &p1, cv::Point2f &p2);

bool VerifyTetrangleSize(cv::Point2f &p1,
                        cv::Point2f &p2,
                        cv::Point2f &p3,
                        cv::Point2f &p4,
                        float minSize);

void DrawQuadrilateral(cv::Mat &img,
                  cv::Point2f &p1,
                  cv::Point2f &p2,
                  cv::Point2f &p3,
                  cv::Point2f &p4,
                  bool crossed = false,
                  cv::Scalar color = cv::Scalar(0, 255, 0),
                  int thickness = 2);
