CC = g++

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

.PHONY: all clean
    
main : main.cpp drawline.o color.o point.o motor.o bluetooth.o
	$(CC) -o main main.cpp drawline.o color.o point.o motor.o bluetooth.o $(LIBS) -lgsl -lcblas -lwiringPi -lbluetooth -lpthread
	./main

drawline.o : drawline.cpp drawline.h motor.h
	$(CC) -c -o drawline.o drawline.cpp $(LIBS)
	
color.o : color.cpp color.h
	$(CC) -c -o color.o color.cpp $(LIBS)
	
point.o : point.cpp point.h
	$(CC) -c -o point.o point.cpp $(LIBS)
	
motor.o : motor.cpp motor.h
	$(CC) -c -o motor.o motor.cpp -lwiringPi
	
bluetooth.o : bluetooth.cpp bluetooth.h motor.h
	$(CC) -c -o bluetooth.o bluetooth.cpp 

clean:
	rm -f main
