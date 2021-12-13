#include <iostream>
#include <stdlib.h>	// exit 사용
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>	// signal 인터럽트

// 오른쪽 뒷 바퀴
#define MOTOR1A 24	// 35
#define MOTOR2A 23	// 33
#define ENA 25 //37
// 왼쪽 뒷 바퀴
#define MOTOR1B 22	//31
#define MOTOR2B 21	//29
#define ENB 3 // 15
// 왼쪽 앞 바퀴
#define MOTOR1C 28	// 38
#define MOTOR2C 27	// 36
#define ENC 29 // 40
// 오른쪽 앞 바퀴
#define MOTOR1D 26	// 32
#define MOTOR2D 6	// 22
#define END 5 // 18

using namespace std;

void motor_value()
{
	pinMode(MOTOR1A, OUTPUT);
	pinMode(MOTOR2A, OUTPUT);
	pinMode(MOTOR1B, OUTPUT);
	pinMode(MOTOR2B, OUTPUT);
	pinMode(MOTOR1C, OUTPUT);
	pinMode(MOTOR2C, OUTPUT);
	pinMode(MOTOR1D, OUTPUT);
	pinMode(MOTOR2D, OUTPUT);
	
	softPwmCreate(ENA, 0, 200);
	softPwmCreate(ENB, 0, 200);
	softPwmCreate(ENC, 0, 200);
	softPwmCreate(END, 0, 200);	
}

void motor_init()
{
	digitalWrite(MOTOR1A, LOW);
	digitalWrite(MOTOR2A, LOW);
	digitalWrite(MOTOR1B, LOW);
	digitalWrite(MOTOR2B, LOW);
	digitalWrite(MOTOR1C, LOW);
	digitalWrite(MOTOR2C, LOW);
	digitalWrite(MOTOR1D, LOW);
	digitalWrite(MOTOR2D, LOW);
}

void INThandler(int sig)
{
	motor_init();
	exit(0);
}

void motor_straight(int speed)
{
	digitalWrite(MOTOR1A, 1);
	digitalWrite(MOTOR2A, 0);
	softPwmWrite(ENA, speed);
	digitalWrite(MOTOR1B, 1);
	digitalWrite(MOTOR2B, 0);
	softPwmWrite(ENB, speed);
	digitalWrite(MOTOR1C, 1);
	digitalWrite(MOTOR2C, 0);
	softPwmWrite(ENC, speed);
	digitalWrite(MOTOR1D, 1);
	digitalWrite(MOTOR2D, 0);
	softPwmWrite(END, speed);
}

void motor_back(int speed)
{
	digitalWrite(MOTOR1A, 0);
	digitalWrite(MOTOR2A, 1);
	softPwmWrite(ENA, speed);
	digitalWrite(MOTOR1B, 0);
	digitalWrite(MOTOR2B, 1);
	softPwmWrite(ENB, speed);
	digitalWrite(MOTOR1C, 0);
	digitalWrite(MOTOR2C, 1);
	softPwmWrite(ENC, speed);
	digitalWrite(MOTOR1D, 0);
	digitalWrite(MOTOR2D, 1);
	softPwmWrite(END, speed);
}

void motor_right(int speed)
{
	digitalWrite(MOTOR1A, 0);
	digitalWrite(MOTOR2A, 0);
	softPwmWrite(ENA, speed);
	digitalWrite(MOTOR1B, 1);
	digitalWrite(MOTOR2B, 0);
	softPwmWrite(ENB, speed);
	digitalWrite(MOTOR1C, 1);
	digitalWrite(MOTOR2C, 0);
	softPwmWrite(ENC, speed);
	digitalWrite(MOTOR1D, 0);
	digitalWrite(MOTOR2D, 0);
	softPwmWrite(END, speed);
}

void motor_left(int speed)
{
	digitalWrite(MOTOR1A, 1);
	digitalWrite(MOTOR2A, 0);
	softPwmWrite(ENA, speed);
	digitalWrite(MOTOR1B, 0);
	digitalWrite(MOTOR2B, 0);
	softPwmWrite(ENB, speed);
	digitalWrite(MOTOR1C, 0);
	digitalWrite(MOTOR2C, 0);
	softPwmWrite(ENC, speed);
	digitalWrite(MOTOR1D, 1);
	digitalWrite(MOTOR2D, 0);
	softPwmWrite(END, speed);
}

void motor_S_right(int speed)
{
	digitalWrite(MOTOR1A, 0);
	digitalWrite(MOTOR2A, 0);
	softPwmWrite(ENA, speed);
	digitalWrite(MOTOR1B, 1);
	digitalWrite(MOTOR2B, 0);
	softPwmWrite(ENB, speed*1.3);
	digitalWrite(MOTOR1C, 1);
	digitalWrite(MOTOR2C, 0);
	softPwmWrite(ENC, speed*1.6);
	digitalWrite(MOTOR1D, 0);
	digitalWrite(MOTOR2D, 0);
	softPwmWrite(END, speed);
}

void motor_S_left(int speed)
{
	digitalWrite(MOTOR1A, 1);
	digitalWrite(MOTOR2A, 0);
	softPwmWrite(ENA, speed);
	digitalWrite(MOTOR1B, 0);
	digitalWrite(MOTOR2B, 0);
	softPwmWrite(ENB, speed);
	digitalWrite(MOTOR1C, 0);
	digitalWrite(MOTOR2C, 0);
	softPwmWrite(ENC, speed);
	digitalWrite(MOTOR1D, 1);
	digitalWrite(MOTOR2D, 0);
	softPwmWrite(END, speed*1.3);
}


void motor_joyskick(float mess)
{
	int speed = 100;
	
	if(mess < 135 && mess >= 45)
	{
		motor_straight(speed);
	}
	else if((mess >=135 && mess <= 180) || (mess < -135 && mess >= -180))
	{
		motor_left(speed);
	}
	else if(mess < -45 && mess >= -135)
	{
		motor_back(speed);
	}
	else if(mess < 45 && mess >= -45)
	{
		motor_right(speed);
	}
	else if(mess == 3000)
	{
		motor_init();
	}
}

#define DELAY  760

void motor_auto(float left, float right, float slope)
{
	int speed = 43; //35
	
	if((left < -0.9) && (left > - 1.2))
	{
		motor_S_right(85);
		printf("@@@@@@@@@@@@@@@@@@@@@@@@\n");
		delay(10);
	}
	else if((slope >= -0.17) && (slope <= 0.17))
	{
		motor_straight(speed*1.1);
		printf("straight\n");
		delay(10);
	}
	else if(((left <= -1.6) && (left >= -2.0))||((left <= -0.2) && (left >= -0.6)) && (right == 1))
	{
		motor_S_right(85);
		printf("rrrrrrrrrrrrrrrrr\n");
		delay(10);
	}
	else if(((left < -2.0) && (left >= -3)) || ((left < -0.6) && (left > - 1.2)))
	{
		motor_straight(speed);
		delay(10);
		printf("ssssssssss_rrrrrrrrrrrrr\n");
		motor_S_right(speed*1.3);
		delay(10);
	}
	else if((((right < 1.2) && (right > 0.4))||((right <= 1.2) && (right > 1))||((right <= 4) && (right >= 1.5))) && (left == 1) && (right !=1))
	{
		motor_S_left(speed*2);
		printf("llllllll\n");
		delay(10);
	}
	else if((right > 1.2) && (right < 1.5))
	{
		motor_straight(speed);
		delay(10);
		printf("ssssssss_llllllllllll\n");
		motor_left(speed*1.3);
		delay(10);
	}
	/*
	else if((left > -1.2) && (left < -0.6) && (right == 1))
	{
		delay(10);
		motor_S_right(speed*1.45);
		printf("33333333333333333\n");
		delay(10);
	}
	 */
	else if((right >= 0.55) && (right <=0.7) && (slope >= 0.72) && (slope <= 0.87) && (left ==1) && (right != 1))
	{
		motor_S_left(speed*2);
		printf("33333333333333333\n");
		delay(10);
	}
	
	else if((right == 1) && (left == 1) && (slope == 1))
	{
		motor_back(45);
		printf("back\n");
	}
	else
	{
		//motor_init();
	}
}
