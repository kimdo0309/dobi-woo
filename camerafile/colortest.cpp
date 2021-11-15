#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat Add, img;
Mat white_inRange, white_mask, yellow_inRange, yellow_mask, black_inRange, black_mask;
Mat hsv, gray, gauss, inblack_inRange;
Mat frame, black_img, can, lines;
Mat Result, frame2;

int H_lowTh, S_lowTh, V_lowTh, H_highTh, S_highTh, V_highTh;

static void black_Scalar(int, void*)
{
	inRange(hsv, Scalar(H_lowTh, S_lowTh, V_lowTh), Scalar(H_highTh, S_highTh, V_highTh), black_mask);
}

int main()
{
   VideoCapture cap("unknown.png");

   if(!cap.isOpened())
      cout << "첫번째 카메라를 열 수 없습니다." << endl;

   int width = cap.get(CAP_PROP_FRAME_WIDTH);
   int height = cap.get(CAP_PROP_FRAME_HEIGHT);
   
   cap >> frame;
   resize(frame, frame2, Size(width, height));
   namedWindow("cam",1);
   
   createTrackbar("H_Low","cam", &H_lowTh, 179, black_Scalar);
   createTrackbar("S_Low","cam", &S_lowTh, 255, black_Scalar);
   createTrackbar("V_Low","cam", &V_lowTh, 255, black_Scalar);
   createTrackbar("H_High","cam", &H_highTh, 179, black_Scalar);
   createTrackbar("S_High","cam", &S_highTh, 255, black_Scalar);
   createTrackbar("V_High","cam", &V_highTh, 255, black_Scalar);
  
   while(1)
   {
	   cvtColor(frame2, hsv, COLOR_BGR2HSV);
	   black_inRange = Mat::zeros(0, 0, CV_8UC3);
	   //black_Scalar(H_lowTh, S_lowTh, V_lowTh, H_highTh, S_highTh, V_highTh, 0);
	   black_Scalar(0 ,0);
	   
	   bitwise_and(frame2, frame2, black_inRange, black_mask);
	   cvtColor(black_inRange, gray, COLOR_BGR2GRAY);
	   GaussianBlur(gray, gauss, Size(3, 3), 0, 0);;
	   Canny(gauss, can, 100, 255);
	   
	   //imshow("cam", black_inRange); 
	   //imshow("cam1", frame2);
	   //imshow("cam2", can);
	   
	   if(waitKey(1) == 27) break;   //esc입력시 종료
   }
   
   destroyAllWindows();
   return 0;
}

