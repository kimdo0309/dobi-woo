#include <unistd.h> //usleep
#include <stdio.h>
#include <wiringPi.h>
 
#define trigPin 4   
#define echoPin 1   

int main(void)
{
    int distance=0;
    int pulse = 0;
    
    long startTime;
    long travelTime;
    
    if(wiringPiSetup () == -1)
    {
        printf("Unable GPIO Setup"); 
        return 1;
    }
        
    pinMode (trigPin, OUTPUT);
    pinMode (echoPin, INPUT);
    
    for(;;)
    {
        digitalWrite (trigPin, LOW);
        usleep(2);
        digitalWrite (trigPin, HIGH);
        usleep(20);
        digitalWrite (trigPin, LOW);
        
        while(digitalRead(echoPin) == LOW);
        
        startTime = micros();
        
        while(digitalRead(echoPin) == HIGH);
        travelTime = micros() - startTime;
        
        int distance = travelTime / 58;
        
        printf( "Distance: %dcm\n", distance);
        delay(200);
    }
}
