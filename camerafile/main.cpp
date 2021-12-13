#include <opencv2/opencv.hpp>
#include <iostream>
#include "drawline.h"
#include "color.h"
#include "point.h"
#include "motor.h"
#include "bluetooth.h"

using namespace cv;
using namespace std;

bdaddr_t bdaddr_anyy = { 0, 0, 0, 0, 0, 0 };

int main()
{
	VideoCapture cap(-1);
	//VideoCapture cap("1.png");
	
	if(!cap.isOpened())
	cout << "첫번째 카메라를 열 수 없습니다." << endl;
	if(wiringPiSetup() == -1) return 1;
	
	//double fps = cap.get(CAP_PROP_FPS);
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	
	pthread_t thread_id;
	signal(SIGPIPE, SIG_IGN);
	int port = 3, result, sock, client, bytes_read, bytes_sent;
	struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
	char buffer[1024] = { 0 };
	socklen_t opt = sizeof(rem_addr);
	// local bluetooth adapter
	loc_addr.rc_family = AF_BLUETOOTH;
	loc_addr.rc_bdaddr = bdaddr_anyy;
	loc_addr.rc_channel = (uint8_t)port;
	// register service
	sdp_session_t* session = register_service(port);
	// allocate socket
	sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	printf("socket() returned %d\n", sock);
	// bind socket to port 3 of the first available
	result = bind(sock, (struct sockaddr*)&loc_addr, sizeof(loc_addr));
	printf("bind() on channel %d returned %d\n", port, result);
	// put socket into listening mode
	result = listen(sock, 1);
	printf("listen() returned %d\n", result);
	//sdpRegisterL2cap(port);
	
	// accept one connection
	printf("calling accept()\n");
	client = accept(sock, (struct sockaddr*)&rem_addr, &opt);
	printf("accept() returned %d\n", client);
	ba2str(&rem_addr.rc_bdaddr, buffer);
	fprintf(stderr, "accepted connection from %s\n", buffer);
	memset(buffer, 0, sizeof(buffer));
	pthread_create(&thread_id, NULL, ThreadMain, (void*)client);
	
	extern float mess;
	
	float num = 2000;
	
	while(1)
	{
		Mat frame, black_img, can, lines, colorselect;
		Mat Result, frame2;
		
		cap >> frame;
		flip(frame, frame, -1); // 카메라 상하 반전
		resize(frame, frame2, Size(width, height));

		can = color(frame2);
		
		frame2.copyTo(colorselect);
		
		Result = Point_img(can, width, height);
		
		frame2.copyTo(lines);
		vector<Vec4i> linesP;
		HoughLinesP(Result, linesP, 2, CV_PI/180, 15, 50, 100);
		//draw_line(lines, linesP, width, height);
		
		if(mess == 1000) num = mess;
		else if(mess == 2000) num = mess;
		
		if(num == 1000)
		{
			draw_line(lines, linesP, width, height);
		}
		else if(num == 2000)
		{
			motor_init();
			motor_joyskick(mess);
		}
		
		//printf("main mess : %f\n", mess);
		imshow("cam2", lines);
		if(waitKey(1) == 27) //esc입력시 종료
		{
			break;   
		}
	}
	destroyAllWindows();
	return 0;
}
