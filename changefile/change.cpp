#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


int main(int ac, char** av)
{
	Mat img = imread("road.jpeg");

	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);

	Mat img_canny;
	Canny(img_gray, img_canny, 150, 255);

	vector<Vec4i> linesP;
	HoughLinesP(img_canny, linesP, 1, (CV_PI / 180), 50, 50, 10);

	Mat img_houghP;
	img.copyTo(img_houghP);
	
	Mat img_lane;
	threshold(img_canny, img_lane, 150, 255, THRESH_MASK);

	for (size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i];
		line(i, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, 8);
		line(img_lane, Point(l[0], l[1]), Point(l[2], l[3]), Scalar::all(255), 1, 8);
	}

	imshow("img", img);
	imshow("img_canny", img_houghP);
	imshow("img_lane", img_lane);

	waitKey(0);
	return 0;
}
