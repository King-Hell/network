#include <WinSock2.h>
#include <stdio.h> 
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include<iostream>
using namespace std;
void recv1(SOCKET sockConn)
{
	char recvBuf[10000];
	memset(recvBuf, 0, sizeof(recvBuf));
	//接收数据
	while (true) {
		int nRecv = ::recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		if (nRecv > 0)cout << "他说：" << recvBuf << endl;
		else break;
	}
}

DWORD WINAPI send1(LPVOID args) {
	SOCKET sockClient1 = (SOCKET)args;
	while (true) {
		char buff1[10000];
		//cout<<"我说：";
		cin >> buff1;
		if (buff1 == "") {
			break;
		}

		int e = send(sockClient1, buff1, sizeof(buff1), 0);
		if (e == SOCKET_ERROR) {
			printf("send failed");
			break;
		}
		cout << "我说：" << buff1 << endl;
	}
	return 0;
}
int main()
{
	//加载套接字
	WSADATA wsaData;
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock");
		return 0;
	}

	SOCKADDR_IN addrSrv; //服务端地址
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5099);
	char ipdomin[20];
	cout << "请输入IP地址或域名" << endl;
	cin >> ipdomin;
	if (inet_pton(AF_INET, ipdomin, &addrSrv.sin_addr.S_un.S_addr) <= 0) //地址
	{                                                        
		struct hostent *hptr;                                 //通过域名获取ip
		hptr = gethostbyname(ipdomin);
		if (hptr == NULL)
		{
			printf("ip address or domin error for %s\n", ipdomin);
			return 1;
		}
		addrSrv.sin_addr = *(struct in_addr *)hptr->h_addr;
	}
	//inet_pton(AF_INET, "127.0.0.1", (void *)&addrSrv.sin_addr.S_un.S_addr);
	//addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//创建客户端套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);//流步套接字
	if (SOCKET_ERROR == sockClient) {
		printf("Socket() error:%d", WSAGetLastError());
		return 0;
	}

	//向服务器发出连接请求
	if (_WINSOCK2API_::connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET) {
		printf("Connect failed:%d", WSAGetLastError());
		return 0;
	}
	else
	{
		HANDLE hThread = CreateThread(NULL, 0, send1, (LPVOID)sockClient, 0, NULL);
		//pthread_t tids[2];
			//int ret = pthread_create( &tids[0], NULL, send1, (void*)&sockClient ); //参数：创建的线程id，线程参数，线程运行函数的起始地址，运行函数的参数
		if (hThread == NULL) //创建线程成功返回0
		{
			cout << "Create Thread Failed!" << endl;
		}

		//接收数据
		recv(sockClient, buff, sizeof(buff), 0);
		printf("%s\n", buff);
	}

	recv1(sockClient);
	//send1((void*)&sockClient);
	//关闭套接字
	closesocket(sockClient);
	WSACleanup();
}
