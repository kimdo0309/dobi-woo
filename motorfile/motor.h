#include <iostream>
#include <stdlib.h>	// exit 사용
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>	// signal 인터럽트

using namespace std;

#ifndef MOTOR
#define MOTOR

void motor_value();
void motor_init();
void INThandler(int sig);
void motor_straight(int speed);
void motor_back(int speed);
void motor_right(int speed);
void motor_left(int speed);
void motor_straight_left(int speed);
void motor_back_left(int speed);
void motor_back_right(int speed);
void motor_straight_right(int speed);

#endif
