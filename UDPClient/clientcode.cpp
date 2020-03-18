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

		printf("WinSock �ʱ�ȭ�κп��� ���� �߻�.n");

		WSACleanup();

		exit(0);

	}



	memset(&ToServer, 0, sizeof(ToServer));

	memset(&FromServer, 0, sizeof(FromServer));



	ToServer.sin_family = AF_INET;

	ToServer.sin_addr.s_addr = inet_addr("127.0.0.1");

	ToServer.sin_port = htons(ServerPort); // ��Ʈ��ȣ



	ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);//



	if (ClientSocket == INVALID_SOCKET)

	{

		printf("������ �����Ҽ� �����ϴ�.");

		closesocket(ClientSocket);

		WSACleanup();

		exit(0);

	}

	//##########################################################################

	  //------------------- ��Ŷ�۽� (26����Ʈ�� ���ĺ��빮�ڵ�~)

	Send_Size = sendto(ClientSocket, Buffer, 26, 0,

		(struct sockaddr*) &ToServer, sizeof(ToServer));



	//------------------- ��Ŷ�۽Ž� ����ó��

	if (Send_Size != 26) { printf("sendto() error! \n"); exit(0); }

	//##########################################################################



	FromServer_Size = sizeof(FromServer);



	memset(Buffer, 0, BUFFER_SIZE);



	//------------------- ��Ŷ����

	Recv_Size = recvfrom(ClientSocket, Buffer, BUFFER_SIZE, 0,

		(struct sockaddr*) &FromServer, &FromServer_Size);

	//------------------- ��Ŷ���Ž� ����ó��

	if (Recv_Size < 0) { printf("recvfrom() error! \n"); exit(0); }

	//###########################################################################



	  //------------------- ������ ��Ŷ���� IP / Data ���

	printf("Recv from < %s > \n", inet_ntoa(FromServer.sin_addr));

	printf("Data < %s > \n", Buffer);



	//------------------- ���ϴݱ�

	closesocket(ClientSocket); //������ �ݽ��ϴ�.

	WSACleanup();

}

