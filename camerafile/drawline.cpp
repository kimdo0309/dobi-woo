#include <opencv2/opencv.hpp>
#include <iostream>
#include <gsl/gsl_fit.h>
#include "motor.h"

using namespace cv;
using namespace std;

void draw_line(Mat &img_line, vector<Vec4i> lines, int width, int height)
{
    //if (lines.size() == 0) return 0;

    bool draw_right = true;
    bool draw_left = true;
    bool draw_center = true;

    //Find slopes of all lines
    //But only care about lines where abs(slope) > slope_threshold  
    float slope_threshold = 0.35;
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
    slope = 499.0; //practically infinite slope
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
    float y1 = height;
    float y2 = height * 0.45;

    float right_x1 = (y1 - right_b) / right_m;
    float right_x2 = (y2 - right_b) / right_m;

    float left_x1 = (y1 - left_b) / left_m;
    float left_x2 = (y2 - left_b) / left_m;

    //Convert calculated end points from float to int
    float right = (right_x1 - right_x2) / (y1 - y2);
    float left = (left_x1 - left_x2) / (y1 - y2);
	float slope = ((right_x1+left_x1)/2 - (right_x2+left_x2)/2) / (y1 - y2);
    
    printf("--------------------------------------------\n\n\n\n\n");
    printf("right: %f\n",right);
    printf("left: %f\n",left);
    printf("slope: %f\n",slope);
    printf("--------------------------------------------\n\n\n\n\n");
    
	
    //Draw the right and left lines on image
    if (draw_right)
    line(img_line, Point(right_x1, y1), Point(right_x2, y2), Scalar(255, 0, 0), 10);
    if (draw_left)
    line(img_line, Point(left_x1, y1), Point(left_x2, y2), Scalar(255, 0, 0), 10);
    if (draw_center)
    line(img_line, Point((right_x1 + left_x1) / 2, y1), 
    Point((right_x2 + left_x2) / 2, y2), Scalar(255, 0, 0), 10);
	
    motor_auto(left, right, slope);
 }
