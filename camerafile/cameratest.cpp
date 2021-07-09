#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <gsl/gsl_fit.h>

using namespace cv;
using namespace std;
//dd
void draw_line(Mat &img_line, vector<Vec4i> lines, int width, int height)
{
    if (lines.size() == 0) return;

    bool draw_right = true;
    bool draw_left = true;
    bool draw_center = true;
   //int width = Width;
   //int height = Height;
    //Find slopes of all lines
    //But only care about lines where abs(slope) > slope_threshold
    float slope_threshold = 0.5;
    vector<float> slopes;
    vector<Vec4i> new_lines;

    for (int i = 0; i < lines.size(); i++)
    {
    Vec4i line = lines[i];
    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];


    float slope;
    //Calculate slope
    if (x2 - x1 == 0) //corner case, avoiding division by 0
    slope = 999.0; //practically infinite slope
    else
    slope = (y2 - y1) / (float)(x2 - x1);


    //Filter lines based on slope
    if (abs(slope) > slope_threshold) {
     slopes.push_back(slope); new_lines.push_back(line);
    }
    }



    // Split lines into right_lines and left_lines, representing the right and left lane lines
    // Right / left lane lines must have positive / negative slope, and be on the right / left half of the image
    vector<Vec4i> right_lines;
    vector<Vec4i> left_lines;

    for (int i = 0; i < new_lines.size(); i++)
    {

    Vec4i line = new_lines[i]; 
    float slope = slopes[i];

    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];


    float cx = width * 0.5; //x coordinate of center of image

    if (slope > 0 && x1 > cx && x2 > cx)
    right_lines.push_back(line);
    else if (slope < 0 && x1 < cx && x2 < cx)
    left_lines.push_back(line);
    }


    //Run linear regression to find best fit line for right and left lane lines
    //Right lane lines
    double right_lines_x[1000];
    double right_lines_y[1000];
    float right_m, right_b;


    int right_index = 0;
    for (int i = 0; i < right_lines.size(); i++) {

    Vec4i line = right_lines[i];
    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];

    right_lines_x[right_index] = x1;
    right_lines_y[right_index] = y1;
    right_index++;
    right_lines_x[right_index] = x2;
    right_lines_y[right_index] = y2;
    right_index++;
    }


    if (right_index > 0) {

    double c0, c1, cov00, cov01, cov11, sumsq;
    gsl_fit_linear(right_lines_x, 1, right_lines_y, 1, right_index,&c0, &c1, &cov00, &cov01, &cov11, &sumsq);

    //printf("# best fit: Y = %g + %g X\n", c0, c1);
    right_m = c1;
    right_b = c0;
    }
    else {
    right_m = right_b = 1;

    draw_right = false;
    }



    // Left lane lines
    double left_lines_x[1000];
    double left_lines_y[1000];
    float left_m, left_b;

    int left_index = 0;
    for (int i = 0; i < left_lines.size(); i++) {

    Vec4i line = left_lines[i];
    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];

    left_lines_x[left_index] = x1;
    left_lines_y[left_index] = y1;
    left_index++;
    left_lines_x[left_index] = x2;
    left_lines_y[left_index] = y2;
    left_index++;
    }


    if (left_index > 0) {
    double c0, c1, cov00, cov01, cov11, sumsq;
    gsl_fit_linear(left_lines_x, 1, left_lines_y, 1, left_index,&c0, &c1, &cov00, &cov01, &cov11, &sumsq);

    //printf("# best fit: Y = %g + %g X\n", c0, c1);

    left_m = c1;
    left_b = c0;
    }
    else {
    left_m = left_b = 1;

    draw_left = false;
    }



    //Find 2 end points for right and left lines, used for drawing the line
    //y = m*x + b--> x = (y - b) / m
    int y1 = height;
    int y2 = height * (1 - 0.4);

    float right_x1 = (y1 - right_b) / right_m;
    float right_x2 = (y2 - right_b) / right_m;

    float left_x1 = (y1 - left_b) / left_m;
    float left_x2 = (y2 - left_b) / left_m;


    //Convert calculated end points from float to int
    y1 = int(y1);
    y2 = int(y2);
    right_x1 = int(right_x1);
    right_x2 = int(right_x2);
    left_x1 = int(left_x1);
    left_x2 = int(left_x2);


    //Draw the right and left lines on image
    if (draw_right)
    line(img_line, Point(right_x1, y1), Point(right_x2, y2), Scalar(255, 0, 0), 10);
    if (draw_left)
    line(img_line, Point(left_x1, y1), Point(left_x2, y2), Scalar(255, 0, 0), 10);
    if (draw_center)
    line(img_line, Point((right_x1 + left_x1) / 2, y1), 
    Point((right_x2 + left_x2) / 2, y2), Scalar(255, 0, 0), 10);

}

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
