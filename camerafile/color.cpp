#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat black_inRange, black_mask;
Mat can, hsv, gray, gauss;
int Kernel_size=3, Max_lowTh=200, ratioo=3;
int lowTh = 60;

Mat color(Mat frame2)
{
    //cvtColor(frame2, hsv, COLOR_BGR2HSV);
    //black_inRange = Mat::zeros(0, 0, CV_8UC3);
    //inRange(hsv, Scalar(0, 0, 0), Scalar(180, 255, 255), black_mask);
    //bitwise_and(frame2, frame2, black_inRange, black_mask);

    //cvtColor(black_inRange, gray, COLOR_BGR2GRAY);
    cvtColor(frame2, gray, COLOR_BGR2GRAY);

    GaussianBlur(gray, gauss, Size(3, 3), 0, 0);
    Canny(gauss, can, lowTh, (lowTh*ratioo));	// 값 95
    //medianBlur(can,can,3);
    
    imshow("can", can);

    return can;
}
