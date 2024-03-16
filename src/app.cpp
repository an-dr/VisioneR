// https://docs.opencv.org/3.4/d7/dff/tutorial_feature_homography.html

#include <opencv2/calib3d/calib3d.hpp> // for homography
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // for wrapPerspective
#include <opencv2/opencv_modules.hpp>

#include "ObjectFinder.hpp"

void proto2()
{
    cv::Mat objectImg = cv::imread("img_obj.jpg");
    cv::Mat sceneImg = cv::imread("img_scene_many.jpg");

    ObjectFinder of;
    of.SetScene(sceneImg);

    cv::Point2f result;
    of.Find(objectImg, result);
    printf("Result: %f %f\n", result.x, result.y);
}

int main(int argc, char **argv)
{
    proto2();
    return 0;
}
