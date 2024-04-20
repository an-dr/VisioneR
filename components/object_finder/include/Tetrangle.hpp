// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <opencv2/opencv.hpp>
#include <array>

using namespace cv;
using namespace std;

class Tetrangle
{
public:
    Tetrangle() = default; 
    Tetrangle(Point2f p1, Point2f p2, Point2f p3, Point2f p4);
    Point2f GetCenter();
    float GetArea();
    array<Point2f, 4> arr;
    
    // overload operator []
    Point2f &operator[](int i);
    const Point2f &operator[](int i) const;
    
    
};
