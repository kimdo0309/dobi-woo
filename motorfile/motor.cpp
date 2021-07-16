#include <stdio.h>
#include <wiringPi.h>

#define MOTOR1 28	// GPIO20
#define MOTOR2 29	// GPIO21

int main(void)
{
	if(wiringPiSetup() == -1) return 1;
	
	pinMode(MOTOR1, OUTPUT);
	pinMode(MOTOR2, OUTPUT);
	
	for(;;)
	{
		digitalWrite(MOTOR1, 1);
		digitalWrite(MOTOR2, 0);
	}
	
	return 0;
}
