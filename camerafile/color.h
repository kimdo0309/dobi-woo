#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#ifndef COLOR
#define COLOR

static void black_Scalar(int, void*);
void Color_createTrackbar();
Mat color(Mat frame2,int width,int height);

#endif
