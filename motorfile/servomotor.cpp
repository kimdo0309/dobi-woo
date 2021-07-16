#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVO 27	// GPIO16

int main()
{
	printf("hi\n");
	int pos = 5;
	int dir = 1;
	printf("%d\n", dir);
	
	if(wiringPiSetup() == -1) return 1;  //init wiringPi
	
	pinMode(SERVO, OUTPUT);  //set the 0 pin as OUTPUT
	digitalWrite(SERVO, LOW);  //0 pin output LOW voltage
	softPwmCreate(SERVO, 0, 200) ;  //pwm initialize HIGH time 0, LOW time 200ms
	
	while(1)
	{
		pos += dir;
		if (pos < 5 || pos > 25)
		{
			dir *= -1;
		}
		printf("%d\n", pos);
		
		softPwmWrite(SERVO, pos);
		sleep(1);
	}
	
	return 0 ;
}
