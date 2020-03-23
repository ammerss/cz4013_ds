#include <stdio.h>

#include <windows.h>

#define BUFFER_SIZE 1024

//################################################################################

#pragma comment (lib,"ws2_32.lib")

WSADATA   wsaData;

SOCKET   ServerSocket;  SOCKADDR_IN  ServerInfo;

SOCKADDR_IN  FromClient;   int   FromClient_Size;



int   Recv_Size;   int   Send_Size;

int   Count;

char   Buffer[BUFFER_SIZE];

short   ServerPort = 9991;