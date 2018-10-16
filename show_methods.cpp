#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <QDebug>
#include <QTime>

#include "detect_methods.h"
#include "show_methods.h"
#include "v4l2_con.h"

using namespace cv;
using namespace std;

void ShowMethods::show_img(const char* file_name, char color)
{
    Mat src = imread(file_name);
    methods cam;
    cam.set_img(src);
    Mat dst;
    if(color == 'B')
        dst = cam.HSV_B();
    if(color == 'R')
        dst = cam.HSV_R();
    Mat dst_c = cam.draw(dst);
    imshow("dst", dst);
    imshow("dst_c",dst_c);
    waitKey(0);
}

void ShowMethods::show_video(const char* file_name, int wait_time, char color)
{
    V4L2_con mycam;
    mycam.v4l2_set_exposure(file_name, 20);
    mycam.v4l2_set_saturation(file_name,60);
    mycam.v4l2_set_brightness(file_name, 40);


    VideoCapture capture(file_name);

    capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);

    methods cam;
    Mat src;
    while(1)
    {
        QTime time;
        time.start();
        capture >> src;
        cam.set_img(src);
        Mat dst;
        if(color == 'B')
            dst = cam.HSV_B();
        if(color == 'R')
            dst = cam.HSV_R();
        Mat dst_c = cam.draw(dst);
        imshow("dst", dst);
        imshow("dst_c", dst_c);
//        qDebug()<<"time:"<<time.elapsed()<<"ms";
        if(char(waitKey(wait_time)) == 'q')    break;
    }
}
