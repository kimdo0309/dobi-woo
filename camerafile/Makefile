CC = g++

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

.PHONY: all clean
    
camera : cameratest.cpp drawline.o color.o point.o
	$(CC) -o camera cameratest.cpp drawline.o color.o point.o $(LIBS) -lgsl -lcblas
	sudo git add .
	sudo git commit -m "git add"
	sudo git push
	wooyong-kim
	dndyd9169!
	./camera

drawline.o : drawline.cpp drawline.h
	$(CC) -c -o drawline.o drawline.cpp $(LIBS)
	
color.o : color.cpp color.h
	$(CC) -c -o color.o color.cpp $(LIBS)
	
point.o : point.cpp point.h
	$(CC) -c -o point.o point.cpp $(LIBS)

clean:
	rm -f camera
