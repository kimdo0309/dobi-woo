CC = g++

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

.PHONY: all clean
    
camera:cameratest.cpp drawline.o color.o
	$(CC) -o camera cameratest.cpp drawline.o color.o $(LIBS) -lgsl -lcblas
	./camera

drawline.o:drawline.cpp drawline.h
	$(CC) -c -o drawline.o drawline.cpp $(LIBS)
	
color.o:color.cpp color.h
	$(CC) -c -o color.o color.cpp $(LIBS)

clean:
	rm -f camera
