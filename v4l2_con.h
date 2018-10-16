#pragma once
#include <sys/ioctl.h>

class V4L2_con
{
public:
    void v4l2_set_exposure(const char* file_name, int exposure);
    void v4l2_set_saturation(const char* file_name, int stauration);
    void v4l2_get_saturation(const char* file_name);
    void v4l2_set_brightness(const char* file_name, int brightness);
    void v4l2_get_brightness(const char* file_name);
};
