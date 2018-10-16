#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "detect_methods.h"
#include "v4l2_con.h"

using namespace cv;
using namespace std;

int main1()
{


    V4L2_con mycam;
    mycam.v4l2_set_exposure("/dev/ch_video1", 40);
    mycam.v4l2_set_saturation("/dev/ch_video1",60);
    mycam.v4l2_set_brightness("/dev/ch_video1", 40);


    VideoCapture capture("/dev/ch_video1");
//    VideoWriter writer("video28.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10.0, Size(1280, 720), true);

    capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);

//    Mat frame;
//    while (true)
//    {
//        capture >> frame;
//        imshow("test", frame);
//        if(char(waitKey(30)) == 'q')    break;
//    }


    methods cam;

    while (true)
    {
        Mat frame;
        capture >> frame;
//        writer << frame;
        cam.set_img(frame);

//        Mat dst = cam.HSV_R();
//        dst = cam.draw(dst);

        imshow("src", frame);
//        imshow("hsv_b", dst);

        if(char(waitKey(30)) == 'q')  break;
    }

//    writer.release();
    capture.release();
}
