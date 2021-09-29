#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>
#include <bluetooth/rfcomm.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>

using namespace std;

#ifndef BLUETO
#define BLUETO

int _str2uuid(const char* uuid_str, uuid_t* uuid);
sdp_session_t* register_service(uint8_t rfcomm_channel);
char* read_server(int client);
void write_server(int client, char* message);
void* ThreadMain(void* argument);

#endif
