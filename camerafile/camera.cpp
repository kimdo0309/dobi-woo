#include <opencv2/opencv.hpp>
#include <iostream>
#include "drawline.h"
#include "color.h"
#include "point.h"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(-1);
	//VideoCapture cap("unknown.png");
	
	if(!cap.isOpened())
	cout << "첫번째 카메라를 열 수 없습니다." << endl;
	
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);

	while(1)
	{
		Mat frame, black_img, can, lines, colorselect;
		Mat Result, frame2;
		
		cap >> frame;
		flip(frame, frame, -1); // 카메라 상하 반전
		resize(frame, frame2, Size(width, height));
		
		can = color(frame2, width, height);
		
		frame2.copyTo(colorselect);
		
		Result = Point_img(can, width, height);
		
		frame2.copyTo(lines);
		vector<Vec4i> linesP;
		HoughLinesP(Result, linesP, 2, CV_PI/180, 15, 50, 100);
		
		draw_line(lines, linesP, width, height);

		imshow("cam1", lines);
		//imshow("cam2", Result);
		if(waitKey(1) == 27) //esc입력시 종료
		{
			break;   
		}
	}
	destroyAllWindows();
	return 0;
}
