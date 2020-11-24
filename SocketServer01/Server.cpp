#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <thread>



#pragma comment(lib,"ws2_32")





using namespace std;

//�������� 
static int SysEnd = 1;  // ä�ñ�� �¿��� ǥ�� 1�� on 0�� off


const int PacketSize = 1024;  // ��� ��Ŷ������ 
const int Port = 4579;        // ��� ��Ʈ ��ȣ 





void f_recv(SOCKET *m_hClnt,char *m_cBuffer,char *m_cMsg)
{
	while (1)
	{
		recv(*m_hClnt, m_cBuffer, PacketSize, 0);


		if (SysEnd == 0) { system("cls"); printf(" �ý��� ���� "); break; } // �ý����� ������ ������ ��ɵ� ����

		if (m_cBuffer[0] == '/' && m_cBuffer[1] == 'Q')   // /Q �Է½�  ���� Ŭ���̾�Ʈ ���� .
		{
			send(*m_hClnt, m_cBuffer, strlen(m_cMsg), 0);
			SysEnd = 0;
			break;
		

		}
		else if (m_cBuffer[0] != 0)
		{
			printf(" Ŭ���̾�Ʈ : %s \n", m_cBuffer);
			memset(m_cBuffer, 0, (size_t)PacketSize);
		}


	}
	return;
}

void f_send(SOCKET* m_hClnt, char* m_cBuffer, char* m_cMsg)
{
	while (1)
	{
		
		printf(" �Է� : ");

		cin >> m_cMsg;

		if (SysEnd == 0) { system("cls"); printf(" ����  ���� "); break; } // �ý����� ������ ������ ��ɵ� ����


		if (m_cMsg[0] == '/' && m_cMsg[1] == 'Q')   // /Q �Է½�  ���� Ŭ���̾�Ʈ ���� .
		{
			send(*m_hClnt, m_cMsg, strlen(m_cMsg), 0);
			SysEnd = 0;
			system("cls");
			printf(" �ý��� ���� ");
			break;
		}


		send(*m_hClnt, m_cMsg, strlen(m_cMsg), 0);

	}
	return ;
}



int main()
{
	


	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(Port);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);

	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

	// ���ۿ� �޼��� ���� 

	char cBuffer[PacketSize] = {};

	char cMsg[] = "Server Send";

	thread Recv(f_recv,&hClient,cBuffer,cMsg);

	thread Send(f_send, &hClient, cBuffer, cMsg);



	Recv.join();
	Send.join();


	closesocket(hClient);
	closesocket(hListen);

	WSACleanup();



	return 0;
}
