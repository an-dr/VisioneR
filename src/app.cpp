// https://docs.opencv.org/3.4/d7/dff/tutorial_feature_homography.html

#include <unistd.h>
#include <opencv2/calib3d/calib3d.hpp> // for homography
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // for wrapPerspective
#include <opencv2/opencv_modules.hpp>

#include "ObjectFinder.hpp"

using namespace cv;

void proto2()
{
    Mat objectImg = imread("img_obj.jpg");
    Mat sceneImg = imread("img_scene_many.jpg");

    ObjectFinder of;
    of.SetScene(sceneImg);

    Point2f result;
    of.Find(objectImg, result);
    printf("Result: %f %f\n", result.x, result.y);
}

void wait(int delay, bool &exit)
{
    if (waitKey(delay) == 27) // ESC
    {
        exit = true;
    }
}

void proto_faces()
{

    Mat blink = imread("assets/blink.png");
    Mat calm = imread("assets/calm.png");
    Mat happy = imread("assets/happy.png");
    Mat sad = imread("assets/sad.png");
    Mat confused = imread("assets/confused.png");
    const char *windowName = "VisioneR";

    namedWindow(windowName, WINDOW_GUI_EXPANDED);

    bool exit = false;
    
    imshow(windowName, calm);
    resizeWindow(windowName, 500, 128);
    
    wait(1000, exit);
    imshow(windowName, happy);
    wait(1000, exit);
    imshow(windowName, sad);
    wait(1000, exit);
    imshow(windowName, confused);
    wait(1000, exit);
    imshow(windowName, blink);
    while (!exit)
    {
        imshow(windowName, calm);
        wait(2000, exit);

        imshow(windowName, blink);
        wait(300, exit);
    }
}

int main(int argc, char **argv)
{
    proto_faces();
    return 0;
}
