#include <sys/ioctl.h>
#include <iostream>
#include <fcntl.h>
#include <linux/videodev2.h>

#include "v4l2_con.h"

using namespace std;

void V4L2_con::v4l2_set_exposure(const char* file_name, int exposure)
{
    int Handle = open(file_name, O_RDWR);
    struct v4l2_control exp_set;
    exp_set.id = V4L2_CID_EXPOSURE_AUTO;
    exp_set.value = 1;
    ioctl(Handle, VIDIOC_S_CTRL, &exp_set);
    cout << "auto_exposure : " << exp_set.value << endl;    // 设置自动曝光作为参考

    exp_set.id = V4L2_CID_EXPOSURE_ABSOLUTE;
    exp_set.value = exposure;
    ioctl(Handle, VIDIOC_S_CTRL, &exp_set);
}
void V4L2_con::v4l2_set_saturation(const char* file_name, int saturation)
{
    int Handle = open(file_name, O_RDWR);
    struct v4l2_control sat_ctrl;
    sat_ctrl.id = V4L2_CID_SATURATION;
    sat_ctrl.value = saturation;
    ioctl(Handle, VIDIOC_S_CTRL, &sat_ctrl);
}
void V4L2_con::v4l2_get_saturation(const char* file_name)
{
    int Handle = open(file_name, O_RDWR);
    struct v4l2_control sat_get;
    sat_get.id = V4L2_CID_SATURATION;
    cout << "saturation : " << sat_get.value << endl;
}
void V4L2_con::v4l2_set_brightness(const char* file_name, int saturation)
{
    int Handle = open(file_name, O_RDWR);
    struct v4l2_control bri_ctrl;
    bri_ctrl.id = V4L2_CID_BRIGHTNESS;
    bri_ctrl.value = saturation;
    ioctl(Handle, VIDIOC_S_CTRL, &bri_ctrl);
}
void V4L2_con::v4l2_get_brightness(const char* file_name)
{
    int Handle = open(file_name, O_RDWR);
    struct v4l2_control bri_get;
    bri_get.id = V4L2_CID_BRIGHTNESS;
    cout << "brightness : " << bri_get.value << endl;
}
