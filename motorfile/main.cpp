#include <iostream>
#include <stdlib.h>	// exit 사용
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>	// signal 인터럽트
#include "motor.h"

using namespace std;

int main(void)
{
	if(wiringPiSetup() == -1) return 1;
	signal(SIGINT, INThandler);	// ctrl + z 종료

	motor_value();
	
	while(1)
	{
		motor_right(150);
	}
	
	return 0;
}
