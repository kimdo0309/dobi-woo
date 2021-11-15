#include <iostream>
#include <stdlib.h>	// exit 사용
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>	// signal 인터럽트

// 왼쪽 앞 바퀴
#define MOTOR1A 24	// 35
#define MOTOR2A 23	// 33
#define ENA 25 //37
// 오른쪽 앞 바퀴
#define MOTOR1B 22	//31
#define MOTOR2B 21	//29
#define ENB 3 // 15
// 오른쪽 뒷 바퀴
#define MOTOR1C 28	// 38
#define MOTOR2C 27	// 36
#define ENC 29 // 40
// 왼쪽 뒷 바퀴
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
void motor_straight_left(int speed)
{
	motor_left(speed*2);
	delay(600);
	motor_straight(speed);
	delay(400);
}
void motor_back_left(int speed)
{
	motor_left(speed*2);
	delay(600);
	motor_back(speed);
	delay(400);
}
void motor_back_right(int speed)
{
	motor_right(speed);
	delay(700);
	motor_back(speed);
	delay(300);
}
#define DELAY_MS1  760
#define DELAY_MS2  100
unsigned long long lastMs = 0;
void motor_straight_right(int speed)
{
	motor_right(speed*5/3);
	/*while(1)
	{
		if(millis() - lastMs >= DELAY_MS1)
		{
			lastMs = millis();
			break;
		}
		printf("OK!!!!!!!!!!!!!!!!!!!!");
	}
	motor_straight(speed);
	while(1)
	{
		if(millis() - lastMs >= DELAY_MS2)
		{
			lastMs = millis();
			break;
		}
	}*/
	
}

void motor_joyskick(float mess)
{
	int speed = 100;
	
		/*
		if(mess < 112.5 && mess >= 67.5)
		{
			motor_straight(speed);
		}
		else if(mess < 157.5 && mess >= 112.5)
		{
			motor_straight_left(speed);
		}
		else if((mess >=157.5 && mess <= 180) || (mess < -157.5 && mess >= -180))
		{
			motor_left(speed);
		}
		else if(mess < -112.5 && mess >= -157.5)
		{
			motor_back_left(speed);
		}
		else if(mess < -67.5 && mess >= -112.5)
		{
			motor_back(speed);
		}
		else if(mess < -22.5 && mess >= 67.5)
		{
			motor_back_right(speed);
		}
		else if(mess <22.5 && mess >= -22.5)
		{
			motor_right(speed);
		}
		else if(mess < 67.5 && mess >= 22.5)
		{
			motor_straight_right(speed);
		}
		else if(mess == 3000)
		{
			motor_init();
		}
		else if(mess == 1000)
		{
			break;
		}
		*/
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

#define DELAY_MS1  760
#define DELAY_MS2  100

//unsigned long long lastMs = 0;

void motor_auto(float left, float right, float slope)
{
	int speed = 100;
	if((left<=-1.2))
	{
		motor_right(speed*5/3);
		delay(10);
		motor_straight(speed);
		delay(10);

	}
	else if((slope>=-0.5)&&(slope<=0.5))
	{
		motor_straight(50);
	}
	else if(right >= 1.2)
	{
		motor_left(speed*5/3);
		delay(10);
		motor_straight(speed);
		delay(10);
	}
	else
	{
		motor_init();
	}
}
