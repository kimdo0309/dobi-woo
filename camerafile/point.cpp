#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat Point_img(Mat can, int width, int height)
{
	Mat black_img, Result;
	
	black_img = Mat::zeros(height, width, CV_8UC1);
	Point points[4];
	/*
	points[0] = Point(0, height);
	points[1] = Point((width * (1 - 0.5)) / 2, height - height * 0.55);
	points[2] = Point(width - (width * (1 - 0.5)) / 2, height - height * 0.55);
	points[3] = Point(width, height);
	*/
	points[0] = Point(0, height);
	points[1] = Point(0, height - height * 0.7);
	points[2] = Point(width, height - height * 0.7);
	points[3] = Point(width, height);
	
	const Point*ppt[1] = { points };
	int npt[] = { 4 };
		  
	fillPoly(black_img, ppt, npt, 1, Scalar(255, 255, 255), LINE_8);
	bitwise_and(can, black_img, Result);
	//imshow("cam3", black_img);
	
	return Result;
}
