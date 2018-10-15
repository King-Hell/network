#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include<WS2tcpip.h>
//#include <pthread.h> 
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
		cout << endl;
		if (nRecv > 0)cout << "他说：" << recvBuf << endl;
		else break;
	}
}
DWORD WINAPI send1(LPVOID args) {
	SOCKET sockClient1 = (SOCKET)args;//建立套接字
	while (true) {
		char buff1[10000];
		//cout<<"请输入"<<endl;
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
	WSADATA wsaData;
	int port = 5099;

	char buf[] = "Server: hello, I am a server.....";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //加载套接字库
	{
		printf("Failed to load Winsock");
		return 0;
	}

	//创建用于监听的套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port); //1024以上的端口号
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //INADDR_ANY 代表任意ip

	int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR) {
		printf("Failed bind:%d\n", WSAGetLastError());
		return 0;
	}

	if (listen(sockSrv, 10) == SOCKET_ERROR) {//10代表允许连接的个数
		printf("Listen failed:%d", WSAGetLastError());
		return 0;
	}

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1)
	{
		//等待客户请求到来
		SOCKET sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);//会阻塞进程，直到有客户端连接上来为止
		if (sockConn == SOCKET_ERROR) {
			printf("Accept failed:%d", WSAGetLastError());
			break;
		}
		char IPdotdec[20];
		inet_ntop(AF_INET, (void *)&addrClient.sin_addr, IPdotdec,16);
		printf("Accept client IP:[%s]\n", IPdotdec);

		//发送数据
		//send1(sockConn);

		int iSend = send(sockConn, buf, sizeof(buf), 0);
		if (iSend == SOCKET_ERROR) {
			printf("send failed");
			break;
		}
		//pthread_t tids[2];
		//int ret = pthread_create( &tids[0], NULL, send1, (void*)&sockConn ); //参数：创建的线程id，线程参数，线程运行函数的起始地址，运行函数的参数
		HANDLE hThread = CreateThread(NULL, 0, send1, (LPVOID)sockConn, 0, NULL);
		if (hThread == NULL) //创建线程成功返回0
		{
			cout << "Create Thread Failed!" << endl;
		}
		recv1(sockConn);
		//if(recvBuf == "end")break;
		closesocket(sockConn);
	}

	closesocket(sockSrv);
	WSACleanup();
	system("pause");
}
