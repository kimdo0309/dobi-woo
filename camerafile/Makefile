CC = g++

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

.PHONY: all clean
    
camera:cameratest.cpp drawline.o
	$(CC) -o camera cameratest.cpp drawline.cpp $(LIBS) -lgsl -lcblas
	./camera

drawline.o:drawline.cpp drawline.h
	$(CC) -c -o drawline.o drawline.cpp $(LIBS)

clean:
	rm -f camera
