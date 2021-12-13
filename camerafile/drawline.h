#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#ifndef DRAWLINE
#define DRAWLINE

void draw_line(Mat &img_line, vector<Vec4i> lines, int width, int height);

#endif
