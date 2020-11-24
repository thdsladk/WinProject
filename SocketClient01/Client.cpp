#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <thread>


#pragma comment(lib,"ws2_32")



//192.168.219.104

using namespace std;


//�������� 
static int SysEnd = 1;   // ä�ñ�� �¿��� ǥ�� 1�� on 0�� off

char IPv4[16] = { 0, };  // ����  IPv4 �ּ� 

const int PacketSize = 1024;  // ��� ��Ŷ������ 
const int Port = 4579;        // ��� ��Ʈ ��ȣ 


void f_recv(SOCKET* m_hSock, char* m_cBuffer, char* m_cMsg)
{
	while (1)
	{

		recv(*m_hSock, m_cBuffer, PacketSize, 0);
		

		if (SysEnd == 0) { system("cls"); printf(" �ý��� ���� "); break; } // �ý����� ������ ������ ��ɵ� ����

		if (m_cBuffer[0] == '/' && m_cBuffer[1] == 'Q')   // /Q �Է½�  ���� Ŭ���̾�Ʈ ���� .
		{
			send(*m_hSock, m_cBuffer, strlen(m_cMsg), 0);
			SysEnd = 0;
			break;
		}
		else if (m_cBuffer[0] != 0)
		{
			printf(" ���� : %s \n", m_cBuffer);
			memset(m_cBuffer, 0, (size_t)PacketSize);
		}
		

		

	}
	return  ;
}


void f_send(SOCKET* m_hSock, char* m_cBuffer, char* m_cMsg)
{
	while (1)
	{

		//ä�ñ���� �ٽ� 

		printf(" �Է� : ");

		//scanf("%s \n", cMsg);     
		//scanf�� �����Է��Ŀ� �ѹ��� �����Է��ؾ��� 

		cin >> m_cMsg;


		if (SysEnd == 0) { system("cls"); printf(" ���� ���� "); break; } // �ý����� ������ ������ ��ɵ� ����

		if (m_cMsg[0] == '/' && m_cMsg[1] == 'Q')   // /Q �Է½�  ���� Ŭ���̾�Ʈ ���� .
		{
			send(*m_hSock, m_cMsg, strlen(m_cMsg), 0);
			SysEnd = 0;
			system("cls"); 
			printf(" �ý��� ���� ");
			break;
		}

		send(*m_hSock, m_cMsg, strlen(m_cMsg), 0);



	}
	return ;
}


int main()
{
	cout << "���� �ּҸ� �Է��ϼ��� : ";
	cin >> IPv4;
	system("cls");


	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hSocket;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(Port);
	tAddr.sin_addr.s_addr = inet_addr(IPv4);

	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

	// ���ۿ�  �޼��� ���� 

	char cMsg[] = "Client Send";


	char cBuffer[PacketSize] = {};

	thread Recv(f_recv, &hSocket, cBuffer, cMsg);
	thread Send(f_send, &hSocket, cBuffer, cMsg);

	

	Recv.join();
	Send.join();

	closesocket(hSocket);

	WSACleanup();

	return 0;
}
