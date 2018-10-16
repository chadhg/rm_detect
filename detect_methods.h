#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class methods
{
public:
    void set_img(Mat img);
    void save(Mat img, char const* file_name, int time);
    Mat HSV_R();
    Mat HSV_B();
    Mat RGB_R();
    Mat YUV_B();
    Mat YUV_R();
    Mat draw(Mat img);
    Mat new_test();
    void armor_draw();

private:
    Mat imgOriginal;
    int colsNumbers;
    int rowsNumbers;
    Point2d pre_center;
};
