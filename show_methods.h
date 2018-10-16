#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class ShowMethods
{
public:
    void show_img(const char* file_name, char color);
    void show_video(const char* file_name, int wait_time, char color);
};
