#include <stdio.h>

#include <windows.h>

#define BUFFER_SIZE 1024

#pragma comment (lib,"ws2_32.lib")

void main(void)

{

	WSADATA   wsaData;
	printf("")


	SOCKET   ClientSocket;

	SOCKADDR_IN  ToServer;   SOCKADDR_IN  FromServer;



	int   FromServer_Size;

	int   Recv_Size;   int   Send_Size;



	char   Buffer[BUFFER_SIZE] = { "Message~" };

	USHORT   ServerPort = 9991;



	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR)

	{

		printf("WinSock 초기화부분에서 문제 발생.n");

		WSACleanup();

		exit(0);

	}



	memset(&ToServer, 0, sizeof(ToServer));

	memset(&FromServer, 0, sizeof(FromServer));



	ToServer.sin_family = AF_INET;

	ToServer.sin_addr.s_addr = inet_addr("127.0.0.1");

	ToServer.sin_port = htons(ServerPort); // 포트번호



	ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);//



	if (ClientSocket == INVALID_SOCKET)

	{

		printf("소켓을 생성할수 없습니다.");

		closesocket(ClientSocket);

		WSACleanup();

		exit(0);

	}

	//##########################################################################

	  //------------------- 패킷송신 (26바이트의 알파벳대문자들~)

	Send_Size = sendto(ClientSocket, Buffer, 26, 0,

		(struct sockaddr*) &ToServer, sizeof(ToServer));



	//------------------- 패킷송신시 에러처리

	if (Send_Size != 26) { printf("sendto() error! \n"); exit(0); }

	//##########################################################################



	FromServer_Size = sizeof(FromServer);



	memset(Buffer, 0, BUFFER_SIZE);



	//------------------- 패킷수신

	Recv_Size = recvfrom(ClientSocket, Buffer, BUFFER_SIZE, 0,

		(struct sockaddr*) &FromServer, &FromServer_Size);

	//------------------- 패킷수신시 에러처리

	if (Recv_Size < 0) { printf("recvfrom() error! \n"); exit(0); }

	//###########################################################################



	  //------------------- 수신한 패킷에서 IP / Data 출력

	printf("Recv from < %s > \n", inet_ntoa(FromServer.sin_addr));

	printf("Data < %s > \n", Buffer);



	//------------------- 소켓닫기

	closesocket(ClientSocket); //소켓을 닫습니다.

	WSACleanup();

}

