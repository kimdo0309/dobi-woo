#include <opencv2/opencv.hpp>
#include <iostream>
#include "drawline.h"
#include "color.h"
#include "point.h"

using namespace cv;
using namespace std;

int H_lowTh, S_lowTh, V_lowTh, H_highTh, S_highTh, V_highTh;
Mat black_mask,black_inRange;

static Mat black_Scalar(Mat colorselect,int, int, int, int, int, int, void*)
{
    Mat hsv,gray,gauss,can;
    cvtColor(colorselect, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(H_lowTh, S_lowTh, V_lowTh), Scalar(H_highTh, S_highTh, V_highTh), black_mask);
    bitwise_and(colorselect, colorselect, black_inRange, black_mask);
    
    cvtColor(black_inRange, gray, COLOR_BGR2GRAY);

    GaussianBlur(gray, gauss, Size(3, 3), 0, 0);
    Canny(gauss, can, 100, 125);
    
    return can;
}

int main()
{
   VideoCapture cap(-1);

   //VideoCapture cap("unknown.png");

   if(!cap.isOpened())
      cout << "첫번째 카메라를 열 수 없습니다." << endl;
   
   //double fps = cap.get(CAP_PROP_FPS);
   //int Width = cap.get(CAP_PROP_FRAME_WIDTH)/2;
   //int Height = cap.get(CAP_PROP_FRAME_HEIGHT)/2;
   int width = cap.get(CAP_PROP_FRAME_WIDTH);
   int height = cap.get(CAP_PROP_FRAME_HEIGHT);
   printf("%d\n", width);
   printf("%d\ns", height);
   
   namedWindow("cam",1);
    
   createTrackbar("H_Low","cam", &H_lowTh, 179);
   createTrackbar("S_Low","cam", &S_lowTh, 255);
   createTrackbar("V_Low","cam", &V_lowTh, 255);
   createTrackbar("H_High","cam", &H_highTh, 179);
   createTrackbar("S_High","cam", &S_highTh, 255);
   createTrackbar("V_High","cam", &V_highTh, 255);
   
   while(1)
   {
      Mat frame, black_img, can, lines, colorselect;
      Mat Result, frame2;
   
      cap >> frame;
      
      resize(frame, frame2, Size(width, height));
      
      can = color(frame2, width, height);
      
      frame2.copyTo(colorselect);
      black_mask=black_Scalar(colorselect,H_lowTh, S_lowTh, V_lowTh, H_highTh, S_highTh, V_highTh, 0);
      
      Result = Point_img(can, width, height);
      
      frame2.copyTo(lines);
      vector<Vec4i> linesP;
      HoughLinesP(Result, linesP, 2, CV_PI/180, 15, 10, 20);
      draw_line(lines, linesP, width, height);
      
      imshow("cam1", lines);
      imshow("cam2", can);
      imshow("cam", black_mask);

      if(waitKey(1) == 27) break;   //esc입력시 종료
   }
   
   destroyAllWindows();

   return 0;
}
