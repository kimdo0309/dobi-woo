#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat Add, img;
Mat white_inRange, white_mask, yellow_inRange, yellow_mask;
Mat black_inRange, black_mask, color_inRange, color_mask;
Mat can, hsv, gray, gauss, inblack_inRange;
int H_lowTh, S_lowTh, V_lowTh, H_highTh, S_highTh, V_highTh;

static void Color_Scalar(Mat frame2, int, int, int, int, int, int, void*)
{
	color_inRange = Mat::zeros(0, 0, CV_8UC3);
	inRange(hsv, Scalar(H_lowTh, S_lowTh, V_lowTh), Scalar(H_highTh, S_highTh, V_highTh), color_mask);
	bitwise_and(frame2, frame2, color_inRange, color_mask);
	
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    erode(color_inRange, color_inRange, element);
    dilate(color_inRange, color_inRange, element);
}

void Color_createTrackbar()
{
	createTrackbar("H_Low", "cam", &H_lowTh, 179);
    createTrackbar("S_Low", "cam", &S_lowTh, 255);
    createTrackbar("V_Low", "cam", &V_lowTh, 255);
    createTrackbar("H_High", "cam", &H_highTh, 179);
    createTrackbar("S_High", "cam", &S_highTh, 255);
    createTrackbar("V_High", "cam", &V_highTh, 255);
}

Mat color(Mat frame2, int width, int height)
{
    /*
    inRange(frame2, Scalar(200, 255, 255), Scalar(255, 255, 255), white_mask);
    bitwise_and(frame2, frame2, white_inRange, white_mask);
    
    cvtColor(frame2, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(18, 94, 140), Scalar(48, 255, 255), yellow_mask);
    bitwise_and(frame2, frame2, yellow_inRange, yellow_mask);
    */
    cvtColor(frame2, hsv, COLOR_BGR2HSV);
    Color_Scalar(frame2, H_lowTh, S_lowTh, V_lowTh, H_highTh, S_highTh, V_highTh, 0);
    
    cvtColor(color_inRange, gray, COLOR_BGR2GRAY);
    //addWeighted(white_inRange, 1.0, yellow_inRange, 1.0, 0.0, Add);
    //cvtColor(Add, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gauss, Size(3, 3), 0, 0);
    Canny(gauss, can, 100, 125);
    
    imshow("cam", color_inRange);

    return can;
}
