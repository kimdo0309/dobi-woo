CC = g++
SRCS = test.cpp
PROG = test

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

.PHONY: all clean
    
camera:cameratest.cpp
	$(CC) -o camera cameratest.cpp $(LIBS) -lgsl -lcblas
	./camera

all: $(PROG)

clean:
	rm -f $(OBJS) $(PROG)
