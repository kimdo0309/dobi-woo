#include <opencv2/opencv.hpp>
#include <iostream>
#include "drawline.h"
#include "color.h"
#include "point.h"
#include "motor.h"

using namespace cv;
using namespace std;

int main()
{
   VideoCapture cap(-1);
   //VideoCapture cap("unknown.png");
   
   if(!cap.isOpened())
      cout << "첫번째 카메라를 열 수 없습니다." << endl;
      
   if(wiringPiSetup() == -1) return 1;
   signal(SIGINT, INThandler);	// ctrl + z 종료
      
   //double fps = cap.get(CAP_PROP_FPS);
   int width = cap.get(CAP_PROP_FRAME_WIDTH);
   int height = cap.get(CAP_PROP_FRAME_HEIGHT);
   
   motor_value();
   //namedWindow("cam", 1);
   //Color_createTrackbar();

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
      HoughLinesP(Result, linesP, 2, CV_PI/180, 15, 100, 100);
      float slope = draw_line(lines, linesP, width, height);
      //printf("%f\n", slope);
      //delay(100);
      
      if(slope < 1 && slope > -1)
      {
		  motor_straight(200);
		  }
		  else
		  {
			  motor_init();
		  }
      
      imshow("cam1", lines);
      imshow("cam2", can);

      if(waitKey(1) == 27) break;   //esc입력시 종료
   }
   
   destroyAllWindows();

   return 0;
}
