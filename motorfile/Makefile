CC = g++

OPENCV = -lwiringPi
LIBS = $(OPENCV)

.PHONY: all clean
    
main : main.cpp motor.o
	$(CC) -o main main.cpp motor.o $(LIBS) -lgsl -lcblas
	./main

motor.o : motor.cpp motor.h
	$(CC) -c -o motor.o motor.cpp $(LIBS)

clean:
	rm -f camera
