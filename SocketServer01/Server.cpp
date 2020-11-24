#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <thread>



#pragma comment(lib,"ws2_32")





using namespace std;

//전역변수 
static int SysEnd = 1;  // 채팅기능 온오프 표시 1은 on 0은 off


const int PacketSize = 1024;  // 상수 패킷사이즈 
const int Port = 4579;        // 상수 포트 번호 





void f_recv(SOCKET *m_hClnt,char *m_cBuffer,char *m_cMsg)
{
	while (1)
	{
		recv(*m_hClnt, m_cBuffer, PacketSize, 0);


		if (SysEnd == 0) { system("cls"); printf(" 시스템 종료 "); break; } // 시스템이 꺼지면 보내는 기능도 정지

		if (m_cBuffer[0] == '/' && m_cBuffer[1] == 'Q')   // /Q 입력시  서버 클라이언트 종료 .
		{
			send(*m_hClnt, m_cBuffer, strlen(m_cMsg), 0);
			SysEnd = 0;
			break;
		

		}
		else if (m_cBuffer[0] != 0)
		{
			printf(" 클라이언트 : %s \n", m_cBuffer);
			memset(m_cBuffer, 0, (size_t)PacketSize);
		}


	}
	return;
}

void f_send(SOCKET* m_hClnt, char* m_cBuffer, char* m_cMsg)
{
	while (1)
	{
		
		printf(" 입력 : ");

		cin >> m_cMsg;

		if (SysEnd == 0) { system("cls"); printf(" 서비스  종료 "); break; } // 시스템이 꺼지면 보내는 기능도 정지


		if (m_cMsg[0] == '/' && m_cMsg[1] == 'Q')   // /Q 입력시  서버 클라이언트 종료 .
		{
			send(*m_hClnt, m_cMsg, strlen(m_cMsg), 0);
			SysEnd = 0;
			system("cls");
			printf(" 시스템 종료 ");
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

	// 버퍼와 메세지 선언 

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
