CC = g++
SRCS = test.cpp
PROG = test

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

.PHONY: all clean

$(PROG):$(SRCS)
	$(CC) -o $(PROG) $(SRCS) $(LIBS) -lgsl -lcblas

all: $(PROG)

clean:
	rm -f $(OBJS) $(PROG)
