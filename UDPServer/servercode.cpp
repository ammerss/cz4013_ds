#include <stdio.h>

#include <windows.h>

#define BUFFER_SIZE 1024

//################################################################################

#pragma comment (lib,"ws2_32.lib")



void main(void)

{
	printf("ss");

	WSADATA   wsaData;

	SOCKET   ServerSocket;  SOCKADDR_IN  ServerInfo;

	SOCKADDR_IN  FromClient;   int   FromClient_Size;



	int   Recv_Size;   int   Send_Size;

	int   Count;



	char   Buffer[BUFFER_SIZE];

	short   ServerPort = 9991;



	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR)

	{

		printf("WinSock �ʱ�ȭ�κп��� ���� �߻�.n");

		WSACleanup();

	}



	memset(&ServerInfo, 0, sizeof(ServerInfo));

	memset(&FromClient, 0, sizeof(FromClient));

	memset(Buffer, 0, BUFFER_SIZE);



	ServerInfo.sin_family = AF_INET;

	ServerInfo.sin_addr.s_addr = inet_addr("10.27.229.133");

	ServerInfo.sin_port = htons(ServerPort); // ��Ʈ��ȣ

   //################################### create #########################################

	ServerSocket = socket(AF_INET, SOCK_DGRAM, 0); // udp�� ���� ����


	printf("��Ĺ����\n");
	if (ServerSocket == INVALID_SOCKET)

	{

		printf("������ �����Ҽ� �����ϴ�.");

		closesocket(ServerSocket);

		WSACleanup();

		exit(0);

	}

	//##################################################################################



   //################################### bind #########################################

	if (bind(ServerSocket, (struct sockaddr*)&ServerInfo, //���ε� ���Ͽ� �������� �ο�

		sizeof(ServerInfo)) == SOCKET_ERROR)

	{

		printf("���ε带 �� �� �����ϴ�.");

		closesocket(ServerSocket);

		WSACleanup();

		exit(0);

	}

	//##################################################################################



   //#################################### receive #########################################

	printf("���ε强��\n");

	for (Count = 1; Count <= 5; Count++)

	{

		FromClient_Size = sizeof(FromClient);



		Recv_Size = recvfrom(ServerSocket, Buffer, BUFFER_SIZE, 0,

			(struct sockaddr*) &FromClient, &FromClient_Size);

		if (Recv_Size < 0) { printf("recefrom() error! \n"); exit(0); }



		printf("��Ŷ���ŵ�! ��Ŷ�� ���� Ŭ���̾�Ʈ�� < %s >\n"

			, inet_ntoa(FromClient.sin_addr));



		printf("��Ŷ�� �����ʹ� < %s > \n", Buffer);



		//###################################################################################



		Send_Size = sendto(ServerSocket, Buffer, Recv_Size, 0,

			(struct sockaddr*) &FromClient, sizeof(FromClient));





		if (Send_Size != Recv_Size) { printf("sendto() error! \n"); exit(0); }

	}



	closesocket(ServerSocket); // ������ �ݽ��ϴ�.

	WSACleanup();

}