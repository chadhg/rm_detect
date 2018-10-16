#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>

#include "detect_methods.h"

using namespace cv;
using namespace std;

void methods::set_img(Mat img)
{
    imgOriginal=img.clone();
    colsNumbers=imgOriginal.cols;
    rowsNumbers=imgOriginal.rows;
    pre_center.x = 0;
    pre_center.y = 0;
}

void methods::save(Mat img, char const* file_name, int time)
{
//    VideoWriter writer(file_name, VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, Size(1280, 720), true);
//    int count = time;
//    if(count <= 0)
//    {
//        while (true)
//        {
//            writer << img;
//            if(char(waitKey(30)) == 'q')    break;
//        }
//    }
//    else
//    {
//        while (count--)
//        {
//            writer << img;
//            waitKey(30);
//        }
//    }
//    writer.release();
}

Mat methods::HSV_B()
{
    Mat img1,img2;

    imgOriginal.copyTo(img1);
    cvtColor(img1, img1, CV_BGR2HSV);

    vector<Mat> channels;
    Mat element = getStructuringElement(MORPH_RECT, Size(5,5));
    split(img1, channels);
    threshold(channels[2], channels[2], 50, 255, THRESH_BINARY);   // 亮度 50  100
    medianBlur(channels[2], channels[2], 3);
    morphologyEx(channels[2], channels[2], MORPH_DILATE, element);
    img1.copyTo(img2, channels[2]);

    Mat img_last;
    Mat lower1 = (Mat_<uchar>(1, 3) << 95, 70, 64);
    Mat upper1 = (Mat_<uchar>(1, 3) << 124, 255, 255);
    inRange(img2, lower1, upper1, img_last);

    morphologyEx(img_last, img_last, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));
    erode(img_last, img_last, getStructuringElement(MORPH_RECT, Size(5, 5)));

    return img_last;
}

Mat methods::HSV_R()
{
    Mat img1,img2;

    imgOriginal.copyTo(img1);
    cvtColor(img1, img1, CV_BGR2HSV);
    vector<Mat> channels;
    Mat element = getStructuringElement(MORPH_RECT, Size(5,5));
    split(img1, channels);
    threshold(channels[2], channels[2], 50, 255, THRESH_BINARY);   // 亮度 50  100
    medianBlur(channels[2], channels[2], 3);
    morphologyEx(channels[2], channels[2], MORPH_DILATE, element);
    img1.copyTo(img2, channels[2]);
    Mat img_last1 = Mat::zeros(img2.rows, img2.cols, CV_8UC1);
    Mat img_last2 = Mat::zeros(img2.rows, img2.cols, CV_8UC1);
    Mat img_last3 = Mat::zeros(img2.rows, img2.cols, CV_8UC1);

    Mat lower0 = (Mat_<uchar>(1, 3) << 0, 70, 60);
    Mat upper0 = (Mat_<uchar>(1, 3) << 4, 255, 255);
    inRange(img2, lower0, upper0, img_last1);

    Mat lower1 = (Mat_<uchar>(1, 3) << 160, 70,60);
    Mat upper1 = (Mat_<uchar>(1, 3) << 180, 255, 255);
    inRange(img2, lower1, upper1, img_last2);

    img_last3 = img_last1 + img_last2;
    morphologyEx(img_last3, img_last3, MORPH_DILATE, element);
    dilate(img_last3, img_last3, element);

    return img_last3;
}

Mat methods::new_test()
{
    Mat img1, img_hsv, img2, img_out;
    imgOriginal.copyTo(img1);
    vector<Mat> channels_hsv;
    Mat dst;
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    cvtColor(img1, img_hsv, COLOR_BGR2HSV);
    split(img_hsv, channels_hsv);
    threshold(channels_hsv[2], channels_hsv[2], 100, 255, THRESH_BINARY);
    morphologyEx(channels_hsv[2], channels_hsv[2], MORPH_DILATE, element);
    img_hsv.copyTo(img2, channels_hsv[2]);
    Mat lower1 = (Mat_<uchar>(1, 3) << 160, 70,60);
    Mat upper1 = (Mat_<uchar>(1, 3) << 180, 255, 255);
    inRange(img2, lower1, upper1, img_out);
    morphologyEx(img_out, img_out, MORPH_DILATE, element);
    return img_out;
}

Mat methods::RGB_R()
{
    Mat img1, img2, img3;
    Mat img_last;

    imgOriginal.copyTo(img1);
    Mat lower0 = (Mat_<uchar>(1, 3) << 40, 30, 180);
    Mat upper0 = (Mat_<uchar>(1, 3) << 80, 70, 230);
    inRange(img1, lower0, upper0, img2);

    Mat lower1 = (Mat_<uchar>(1, 3) << 15, 20, 80);
    Mat upper1 = (Mat_<uchar>(1, 3) << 60, 60, 110);
    inRange(img1, lower1, upper1, img3);

    img_last = img2 +img3;

    return img_last;
}

Mat methods::YUV_B()
{
    Mat img1, img2;
    imgOriginal.copyTo(img1);

    cvtColor(img1, img1, CV_BGR2YUV);
    vector<Mat> planes;
    split(img1, planes);

//    imshow("last_img", last_img);

//    cvtColor(img1, img1, CV_BGR2GRAY);
//    threshold(img1, img1, 70, 255, THRESH_BINARY);
//    imshow("img1", img1);
    Mat U = planes[1];
    threshold(U, U, 136, 255, THRESH_BINARY);

//    Mat lower = (Mat_<uchar>(1, 3) << )

//    imshow("last_img", last_img);
    return U;
}

Mat methods::YUV_R()
{
    Mat img1, img2, img3, Y, U, V;
    Mat img_last;

    imgOriginal.copyTo(img1);
    vector<Mat> planes;
    split(img1, planes);

    Mat fIn, fI, O;

    for(int i = 0; i < 3; i++)
    {
        planes[i].convertTo(planes[i], CV_64F, 1.0/255, 0);
        pow(planes[i], 0.5, planes[i]);         // 伽马变换
        planes[i].convertTo(planes[i], CV_8U, 255, 0);
    }
    Mat last_img;
    merge(planes, last_img);
    cvtColor(last_img, last_img, CV_BGR2YUV);
//    imshow("last", last_img);
    Mat lower = (Mat_<uchar>(1, 3) << 0, 0, 160);
    Mat upper = (Mat_<uchar>(1, 3) << 255, 255, 210);
    inRange(last_img, lower, upper, last_img);

    morphologyEx(last_img, last_img, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));
    dilate(last_img, last_img, getStructuringElement(MORPH_RECT, Size(3, 3)));

    return last_img;
}

//bool sortFun(const Vec3f &p1, const Vec3f &p2)
//{
//    return p1[2] < p2[2];
//}

Mat methods::draw(Mat img_last3)
{
    GaussianBlur(img_last3, img_last3, Size(3,3), 0.5);
    Mat binaryImg;
    Canny(img_last3, binaryImg, 50, 200);

//    for(int i=0;i<img_last3.rows;i++)
//    {
//        for(int j=0;j<img_last3.cols;j++)
//            cout<<img_last3.at<int>(i,j)<<' ';
//        cout<<endl;
//    }
//    cout<<endl;

//    imshow("显示边缘", binaryImg);

    // 边缘轮廓
    vector<vector<Point>> contours;
    vector<Point> hierarchy;
    vector<Vec3f> lantern_message;
    findContours(binaryImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    int num = contours.size();   // 轮廓数量
    double rate_sta = 1.4;                        // 可调参数：筛选竖直长方形灯条

    // 第一个for找灯条
    vector<RotatedRect> rectPoint(num);
    for(int i = 0; i < num; i++)
    {
        RotatedRect rect=minAreaRect(contours[i]);
        Point2f P[4];
        rect.points(P);

        // 筛选长竖直长方形灯条
        double delta_x = 0, delta_y = 0, delta;
        for(int i = 0; i < 4; i++)
        {
            delta = fabs(P[i].x - P[(i+1)%4].x);
            if(delta_x < delta) delta_x = delta;
            delta = fabs(P[i].y - P[(i+1)%4].y);
            if(delta_y < delta) delta_y = delta;
        }
        double rate = delta_y / delta_x;
        if(rate < rate_sta)
        {
            continue;
        }
        // 排除中间不是空白的(即可能是反光)
//        int sum=0;
//        for(int i = rect.center.x-2; i < rect.center.x+2; i++)
//        {
//            for(int j = rect.center.y-2; j < rect.center.y+2; j++)
//            {
//                sum+=img_last3.at<uchar>(j,i);
//            }
//        }
//        if(sum  >= 1275)
//        {
//            continue;
//        }

        rectPoint[i] = rect;

        // 如果不是竖直长方形灯条，不画出框和不计入lantern_message，即不进行装甲板计算
        for(int j=0;j<=3;j++)
        {
            line(img_last3,P[j],P[(j+1)%4],Scalar(255),2);
        }

        float height = rect.size.height;
        float width = rect.size.width;
        height = height > width ? height : width;
        float area = contourArea(contours[i]);
        Vec3f message(i, height, area);
        lantern_message.push_back(message);
    }

    // 第二个for找装甲板
    vector<Vec3f> armour;
    for(int i=0;i<(int)lantern_message.size();i++)
    {
        for(int j=i+1;j<(int)lantern_message.size();j++)
        {
            double original_index_i=lantern_message[i][0];
            double original_index_j=lantern_message[j][0];

            double area1=lantern_message[i][2];
            double area2=lantern_message[j][2];

            double height_1=lantern_message[i][1];
            double height_2=lantern_message[j][1];

            double angle_1 = rectPoint[original_index_i].angle;
            double angle_2 = rectPoint[original_index_j].angle;

            double area_rate=area1/area2;
            double lantern_cha=fabs(rectPoint[original_index_i].center.y-rectPoint[original_index_j].center.y);
            double cha=40;  //20                // 可调参数：调节灯条高度差
            double rate1=2.8;                   // 可调参数：调节灯条面积比
            double rate2=0.2;

//            if(area1>500||area2>500)
//            {
//                rate1=3;
//                rate2=0.3;
//                cha=25;
//            }

            // 控制两个灯条面积
            if(area1<30||area2<30)              // 可调参数：调节灯条面积
            {
                continue;
            }

            if(fabs(angle_1-angle_2) > 10)      // 可调参数：调节灯条角度差
            {
                continue;
            }

            Point2f P1[4], P2[4];
            double cha_max=0;
            rectPoint[original_index_i].points(P1);
            rectPoint[original_index_j].points(P2);
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    double cha_p = fabs(P1[i].x - P2[j].x);
                    if(cha_p < cha_max) cha_max = cha_p;
                }
            }
            if(cha_max - fabs(rectPoint[original_index_i].center.x - rectPoint[original_index_j].center.x) > 10)
            {
                continue;
            }

            // 筛选灯条高度差
            if(lantern_cha<cha)//&&(area_rate>rate2&&area_rate<rate1))
            {
                double diameter=sqrt(pow(rectPoint[original_index_i].center.x-rectPoint[original_index_j].center.x,2)+
                                     pow(rectPoint[original_index_i].center.y-rectPoint[original_index_j].center.y,2));
                // cout<<"d: "<<diameter<<endl;    // 装甲板直径

                double average_height=(height_1+height_2)*0.5;
                // cout<<"h: "<<average_height<<endl;
//                if((diameter/average_height>3.5&&diameter/average_height<5.5+0.5)||(diameter/average_height>0.28&&diameter/average_height<3.3))
                // 筛选装甲板直径
                if((diameter/average_height>2.5&&diameter/average_height<6)||(diameter/average_height>0.3&&diameter/average_height<2.5))
                {
                    // 限制直径范围(减少隔灯条的误识别)
                    if(diameter<20)//||(area1>80||area2>80))       // 可调参数：调节装甲板直径范围
                    {
                        continue;
                    }
                    Point armour_center=(rectPoint[original_index_i].center+rectPoint[original_index_j].center)*0.5;
//                    circle(imgOriginal,armour_center,diameter/2,Scalar(255),1);//紫色
//                    cout << "angle: " << fabs(angle_1-angle_2) << endl;
                    // 阴影的装甲板是白色的，根据像素点的颜色筛选掉
                    int sum=0;
                    for(int i = armour_center.x-4; i < armour_center.x+4; i++)
                    {
                        for(int j = armour_center.y-4; j < armour_center.y+4; j++)
                        {
                            sum+=img_last3.at<uchar>(j,i);
                        }
                    }
                    if(sum  > 2550)
                    {
                        continue;
                    }
                    Vec3f armour_message(armour_center.x,armour_center.y,diameter);
                    armour.push_back(armour_message);
                }
            }
        }
    }
    int size = armour.size();
    // 根据y坐标筛选一部分
    if(size > 0)
    {
        Vec3f circle_img = armour[0];
        vector<Vec3f> candidate_armour;
        double cha = 20;
        for(int i=0; i < size; i++)
        {
//            if(circle_img[2] > armour[i][2])    circle_img = armour[i];
            if(fabs(armour[i][1]-pre_center.y) < cha)
            {
//                cha = fabs(armour[i][1] - pre_center.y);
                candidate_armour.push_back(armour[i]);

            }
        }
        int size_can = candidate_armour.size();
        if(size_can > 0)
        {
            circle_img = candidate_armour[0];
            for(int i = 0; i < size_can; i++)
            {
                if(circle_img[2] > candidate_armour[i][2])  circle_img = candidate_armour[i];
            }
        }


        Point2d armour_cen(circle_img[0], circle_img[1]);
        pre_center = armour_cen;
        circle(imgOriginal, armour_cen, circle_img[2]/2, Scalar(0, 0, 255), 2);
    }
    return imgOriginal;
}

void methods::armor_draw()
{

}


//    sort(armour.begin(), armour.end(), sortFun);
//    circle(imgOriginal, Point(armour[0][0],armour[0][1]), armour[0][2]/2, Scalar(255), 1);


//    vector<char> x_coor;
//    vector<char> y_coor;
//    for(int i = 0; ; i++)
//    {
//        char num_x_remainder_char = '0';
//        char num_y_remainder_char = '0';

//        if(X != 0)
//        {
//            num_x_remainder_char = X % 10 + '0';
//            X /= 10;
//            x_coor.push_back(num_x_remainder_char);
//        }

//        if(Y != 0)
//        {
//            num_y_remainder_char = Y % 10 + '0';
//            Y /= 10;
//            y_coor.push_back(num_y_remainder_char);
//        }

//        if(X == 0 && Y == 0)    break;
//    }

//    char coordinate[9] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'};
//    int counter = 0;
//    coordinate[counter++] = 'X';
//    int size_x = x_coor.size();
//    for(int count = 0; count < size_x; count++)
//    {
//        coordinate[counter++] = x_coor[size_x - count - 1];
//    }
//    coordinate[counter++] = 'Y';
//    int size_y = y_coor.size();
//    for(int count = 0; count < size_y; count++)
//    {
//        coordinate[counter++] = y_coor[size_y - count - 1];
//    }
