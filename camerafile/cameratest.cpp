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
   
   //double fps = cap.get(CAP_PROP_FPS);
   int width = cap.get(CAP_PROP_FRAME_WIDTH);
   int height = cap.get(CAP_PROP_FRAME_HEIGHT);
  
   namedWindow("cam", 1);
   Color_createTrackbar();

   while(1)
   {
      Mat frame, black_img, can, lines, colorselect;
      Mat Result, frame2;
   
      cap >> frame;
      
      resize(frame, frame2, Size(width, height));
      
      can = color(frame2, width, height);
      
      //frame2.copyTo(colorselect);
      //black_mask=black_Scalar(colorselect,H_lowTh, S_lowTh, V_lowTh, H_highTh, S_highTh, V_highTh, 0);
      
      Result = Point_img(can, width, height);
      
      frame2.copyTo(lines);
      vector<Vec4i> linesP;
      HoughLinesP(Result, linesP, 2, CV_PI/180, 15, 10, 20);
      draw_line(lines, linesP, width, height);
      
      imshow("cam1", lines);
      imshow("cam2", can);
      //imshow("cam", black_mask);

      if(waitKey(1) == 27) break;   //esc입력시 종료
   }
   
   destroyAllWindows();

   return 0;
}
