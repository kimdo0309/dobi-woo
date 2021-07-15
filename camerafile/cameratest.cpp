#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <gsl/gsl_fit.h>
#include "drawline.h"

using namespace cv;
using namespace std;

Mat color(Mat frame2,int width,int height){
    Mat Add, img;
    Mat white_inRange, white_mask, yellow_inRange, yellow_mask;
    Mat can, hsv, gray, gauss;
    
    inRange(frame2, Scalar(200, 255, 255), Scalar(255, 255, 255), white_mask);
    bitwise_and(frame2, frame2, white_inRange, white_mask);
      
    cvtColor(frame2, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(18, 94, 140), Scalar(48, 255, 255), yellow_mask);
    bitwise_and(frame2, frame2, yellow_inRange, yellow_mask);
      
    addWeighted(white_inRange, 1.0, yellow_inRange, 1.0, 0.0, Add);
    cvtColor(Add, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gauss, Size(3, 3), 0, 0);
    Canny(gauss, can, 100, 255);
      
    return can;
}
int main()
{
   VideoCapture cap("challenge.mp4");

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
      Mat frame,black_img,can,lines;
      Mat Result,frame2;
   
      cap >> frame;
      
      resize(frame, frame2, Size(width, height));
      
      can=color(frame2,width,height);

      black_img = Mat::zeros(height, width, CV_8UC1);

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
