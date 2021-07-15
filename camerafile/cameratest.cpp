#include <opencv2/opencv.hpp>
#include <iostream>
#include "drawline.h"
#include "color.h"
#include "point.h"

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
      Mat frame, black_img, can, lines;
      Mat Result, frame2;
   
      cap >> frame;
      
      resize(frame, frame2, Size(width, height));
      
      can = color(frame2, width, height);
      
      Result = Point_img(can, width, height);
      
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
