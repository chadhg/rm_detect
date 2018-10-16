#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "detect_methods.h"
#include "show_methods.h"

using namespace cv;
using namespace std;

int main()
{
    ShowMethods show;
//    show.show_img("4.png", 'R');
    show.show_video("video21.avi", 50, 'R');
}
