#include <stdio.h>
#include <stdlib.h>	// exit 사용
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>	// signal 인터럽트

#define MOTOR1A 24	// 35
#define MOTOR2A 23	// 33
#define ENA 25 //37

#define MOTOR1B 22	//31
#define MOTOR2B 21	//29
#define ENB 30 // 27

void init()
{
	digitalWrite(MOTOR1A, LOW);
	digitalWrite(MOTOR2A, LOW);
	digitalWrite(MOTOR1B, LOW);
	digitalWrite(MOTOR2B, LOW);
}

void INThandler(int sig)
{
	init();
	exit(0);
}

int main(void)
{
	if(wiringPiSetup() == -1) return 1;
	signal(SIGINT, INThandler);	// ctrl + z 종료
	
	pinMode(MOTOR1A, OUTPUT);
	pinMode(MOTOR2A, OUTPUT);
	pinMode(MOTOR1B, OUTPUT);
	pinMode(MOTOR2B, OUTPUT);
	
	softPwmCreate(ENA, 0, 200);
	softPwmCreate(ENB, 0, 200);
	
	while(1)
	{
		digitalWrite(MOTOR1A, 1);
		digitalWrite(MOTOR2A, 0);
		softPwmWrite(ENA, 100);
		digitalWrite(MOTOR1B, 1);
		digitalWrite(MOTOR2B, 0);
		softPwmWrite(ENB, 100);
		delay(1000);
		digitalWrite(MOTOR1A, 0);
		digitalWrite(MOTOR2A, 1);
		softPwmWrite(ENA, 50);
		digitalWrite(MOTOR1B, 0);
		digitalWrite(MOTOR2B, 1);
		softPwmWrite(ENB, 200);
		delay(1000);
	}
	
	
	return 0;
}
