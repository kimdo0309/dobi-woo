CC = g++
SRCS = test.cpp
PROG = test

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

.PHONY: all clean

$(PROG):$(SRCS) camera
	$(CC) -o $(PROG) $(SRCS) $(LIBS) -lgsl -lcblas
    
camera:cameratest.cpp
	$(CC) -o camera cameratest.cpp $(LIBS) -lgsl -lcblas

all: $(PROG)

clean:
	rm -f $(OBJS) $(PROG)
