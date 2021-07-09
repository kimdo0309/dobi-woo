CC = g++

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

.PHONY: all clean
    
camera:cameratest.cpp
	$(CC) -o camera cameratest.cpp $(LIBS) -lgsl -lcblas
	./camera

clean:
	rm -f camera
