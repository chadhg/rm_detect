#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <linux/videodev2.h>
#include <sys/ioctl.h>

#include "detect_methods.h"
#include "v4l2_con.h"

using namespace cv;
using namespace std;

int fd;

int xioctl(int fd, int request, void *arg){
    int r;
    do r = ioctl (fd, request, arg);
    while (-1 == r && EINTR == errno);
    return r;
}

bool setExposureTime(bool auto_exp, int t){
    if (auto_exp){
        struct v4l2_control control_s;
        control_s.id = V4L2_CID_EXPOSURE_AUTO;
        control_s.value = V4L2_EXPOSURE_AUTO;
        if( xioctl(fd, VIDIOC_S_CTRL, &control_s) < 0){
            cout << "Set Auto Exposure error\n" << endl;
            return false;
        }
    }
    else {
        struct v4l2_control control_s;
        control_s.id = V4L2_CID_EXPOSURE_AUTO;
        control_s.value = V4L2_EXPOSURE_MANUAL;
        if( xioctl(fd, VIDIOC_S_CTRL, &control_s) < 0){
            cout << "Close MANUAL Exposure error\n" << endl;
            return false;
        }

        control_s.id = V4L2_CID_EXPOSURE_ABSOLUTE;
        control_s.value = t;
        if( xioctl(fd, VIDIOC_S_CTRL, &control_s) < 0){
            cout << "Set Exposure Time error\n" << endl;
            return false;
        }
    }
    return true;
}

int main1()
{


    V4L2_con mycam;
    mycam.v4l2_set_exposure("/dev/ch_video1", 30);
    mycam.v4l2_set_saturation("/dev/ch_video1",60);
    mycam.v4l2_set_brightness("/dev/ch_video1", 40);

    VideoCapture capture("/dev/ch_video1");

    capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);
    methods cam;

    while (true)
    {
        Mat frame;
        capture >> frame;
        cam.set_img(frame);

//        dst = cam.draw(dst);

        imshow("src", frame);

        if(char(waitKey(30)) == 'q')  break;
    }

    capture.release();
}
