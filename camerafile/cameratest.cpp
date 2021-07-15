#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <gsl/gsl_fit.h>
#include "drawline.h"

using namespace cv;
using namespace std;

int main()
{
   VideoCapture cap("1.mp4");

   if(!cap.isOpened())
      cout << "첫번째 카메라를 열 수 없습니다." << endl;
   
   //double fps = cap.get(CAP_PROP_FPS);
   //int Width = cap.get(CAP_PROP_FRAME_WIDTH)/2;
   //int Height = cap.get(CAP_PROP_FRAME_HEIGHT)/2;
   int width = cap.get(CAP_PROP_FRAME_WIDTH);
   int height = cap.get(CAP_PROP_FRAME_HEIGHT);
   printf("%d\n", width);
   printf("%d\ns", height);
   
   while(1)
   {
      Mat frame, frame2 , can, lines, hsv, gray, gauss;
      Mat Add, img;
      Mat black_img, Result;
      Mat white_inRange, white_mask, yellow_inRange, yellow_mask;
   
      cap >> frame;
      
      resize(frame, frame2, Size(width, height));
      inRange(frame2, Scalar(200, 255, 255), Scalar(255, 255, 255), white_mask);
      bitwise_and(frame2, frame2, white_inRange, white_mask);
      
      cvtColor(frame2, hsv, COLOR_BGR2HSV);
      inRange(hsv, Scalar(18, 94, 140), Scalar(48, 255, 255), yellow_mask);
      bitwise_and(frame2, frame2, yellow_inRange, yellow_mask);
      
      addWeighted(white_inRange, 1.0, yellow_inRange, 1.0, 0.0, Add);
      //Add.copyTo(img);
      //bitwise_or(white_inRange, yellow_inRange, Add);
      cvtColor(Add, gray, COLOR_BGR2GRAY);
      GaussianBlur(gray, gauss, Size(3, 3), 0, 0);
      Canny(gauss, can, 100, 255);
      
      black_img = Mat::zeros(height, width, CV_8UC1);
      /*
      Point p[1][4];
      p[0][0] = Point(0,Height);
      p[0][1] = Point(Width*2/5,Height/5);
      p[0][2] = Point(Width*3/5,Height/5);
      p[0][3] = Point(Width,Height);
      */
      Point points[4];
      points[0] = Point(width * (1 - 0.85) / 2, height);
      points[1] = Point((width * (1 - 0.07)) / 2, height - height *0.4);
      points[2] = Point(width - (width * (1 - 0.07)) / 2, height - height * 0.4);
      points[3] = Point(width - (width * (1 - 0.85)) / 2, height);

      const Point*ppt[1] = { points };
      int npt[] = { 4 };
      
      fillPoly(black_img, ppt, npt, 1, Scalar(255, 255, 255), LINE_8);
      bitwise_and(can, black_img, Result);
      
      frame2.copyTo(lines);
      vector<Vec4i> linesP;
      HoughLinesP(Result, linesP, 2, CV_PI/180, 15, 10, 20);
      draw_line(lines, linesP, width, height);
      
      imshow("cam1", lines);
      imshow("cam2", can);

      if(waitKey(1) == 27) break;   //esc입력시 종료
   }
   
   destroyAllWindows();

   return 0;
}
