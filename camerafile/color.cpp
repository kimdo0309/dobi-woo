 #include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
 
Mat color(Mat frame2, int width, int height)
{
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
