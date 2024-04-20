#include "Tetrangle.hpp"
#include "tools.hpp"

Tetrangle::Tetrangle(Point2f p1, Point2f p2, Point2f p3, Point2f p4)
    : arr({p1,p2,p3,p4})
{
}

Point2f Tetrangle::GetCenter()
{
    return (arr[1] + arr[2] + arr[3] + arr[4]) / 4;
}

float Tetrangle::GetArea()
{
    float a = CalculateDistance(arr[1], arr[2]);
    float b = CalculateDistance(arr[2], arr[3]);
    float c = CalculateDistance(arr[3], arr[4]);
    float d = CalculateDistance(arr[4], arr[1]);
    float p = (a + b + c + d) / 2;
    return sqrt((p - a) * (p - b) * (p - c) * (p - d));
}

Point2f &Tetrangle::operator[](int i)
{
    return arr[i];
}

const Point2f &Tetrangle::operator[](int i) const
{
    return arr[i];
}
