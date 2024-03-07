#include <opencv2/calib3d/calib3d.hpp> // for homography
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // for wrapPerspective
#include <opencv2/opencv_modules.hpp>
#include <stdio.h>

#include "ObjectFinder.hpp"

using namespace cv;
using namespace std;

void ObjectFinder::Find()
{
    if (m_objectImg.empty() || m_sceneImg.empty())
    {
        printf("Error: empty images\n");
        return;
    }

    DetectKeypoints("Object", m_objectImg, m_objectKeypoints);
    ComputeDescriptors("Object", m_objectImg, m_objectKeypoints, m_objectDescriptors);

    DetectKeypoints("Scene", m_sceneImg, m_sceneKeypoints);
    ComputeDescriptors("Scene", m_sceneImg, m_sceneKeypoints, m_sceneDescriptors);
}

bool ObjectFinder::LoadFromFiles(string objectImgPath,
                                 string sceneImgPath)
{
    m_objectImg = imread(objectImgPath);
    m_sceneImg = imread(sceneImgPath);
    return true;
}

bool ObjectFinder::DetectKeypoints(std::string image_name,
                                   Mat &img,
                                   vector<KeyPoint> &keypoints,
                                   bool show)
{
    Ptr<FeatureDetector> detector;
#if CV_MAJOR_VERSION == 2
    // detector = Ptr(new DenseFeatureDetector());
    // detector = Ptr(new FastFeatureDetector());
    // detector = Ptr(new GFTTDetector());
    // detector = Ptr(new MSER());
    // detector = Ptr(new ORB());
    detector = Ptr<FeatureDetector>(new SIFT());
    // detector = Ptr(new StarFeatureDetector());
    // detector = Ptr(new SURF(600.0));
    // detector = Ptr(new BRISK());
#elif CV_MAJOR_VERSION < 4 || (CV_MAJOR_VERSION == 4 && CV_MINOR_VERSION < 3)
    detector = xfeatures2d::SIFT::create();
#else // >= 4.3.0
    detector = SIFT::create();
#endif
    detector->detect(img, keypoints);
    printf("[%s] %d keypoints detected\n", image_name.c_str(),
           (int)keypoints.size());

    if (show)
    {
        // Draw keypoints
        Mat img_keypoints = img.clone();
        drawKeypoints(img_keypoints, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        // show
        imshow("Keypoints", img_keypoints);
        waitKey(500);
    }
    return true;
}

bool ObjectFinder::ComputeDescriptors(std::string image_name, cv::Mat &img, std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors, bool show)
{
    if (keypoints.size() == 0)
    {
        printf("[%s] Error: no keypoints\n", image_name.c_str());
        return false;
    }

    cv::Ptr<cv::DescriptorExtractor> extractor;
#if CV_MAJOR_VERSION == 2
    // The extractor can be any of (see OpenCV features2d.hpp):
    // extractor = cv::Ptr(new cv::BriefDescriptorExtractor());
    // extractor = cv::Ptr(new cv::ORB());
    extractor = cv::Ptr<cv::DescriptorExtractor>(new cv::SIFT());
    // extractor = cv::Ptr(new cv::SURF(600.0));
    // extractor = cv::Ptr(new cv::BRISK());
    // extractor = cv::Ptr(new cv::FREAK());
#elif CV_MAJOR_VERSION < 4 || (CV_MAJOR_VERSION == 4 && CV_MINOR_VERSION < 3)
    extractor = cv::xfeatures2d::SIFT::create();
#else // >= 4.3.0
    extractor = cv::SIFT::create();
#endif
    extractor->compute(img, keypoints, descriptors);
    printf("[%s] %d descriptors extracted\n",
           image_name.c_str(),
           descriptors.rows);
    return true;
}
