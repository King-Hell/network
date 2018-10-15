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
	//��������
	while (true) {
		int nRecv = ::recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		cout << endl;
		if (nRecv > 0)cout << "��˵��" << recvBuf << endl;
		else break;
	}
}
DWORD WINAPI send1(LPVOID args) {
	SOCKET sockClient1 = (SOCKET)args;//�����׽���
	while (true) {
		char buff1[10000];
		//cout<<"������"<<endl;
		cin >> buff1;
		if (buff1 == "") {
			break;
		}

		int e = send(sockClient1, buff1, sizeof(buff1), 0);
		if (e == SOCKET_ERROR) {
			printf("send failed");
			break;
		}
		cout << "��˵��" << buff1 << endl;
	}
	return 0;
}
int main()
{
	WSADATA wsaData;
	int port = 5099;

	char buf[] = "Server: hello, I am a server.....";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //�����׽��ֿ�
	{
		printf("Failed to load Winsock");
		return 0;
	}

	//�������ڼ������׽���
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port); //1024���ϵĶ˿ں�
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //INADDR_ANY ��������ip

	int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR) {
		printf("Failed bind:%d\n", WSAGetLastError());
		return 0;
	}

	if (listen(sockSrv, 10) == SOCKET_ERROR) {//10�����������ӵĸ���
		printf("Listen failed:%d", WSAGetLastError());
		return 0;
	}

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1)
	{
		//�ȴ��ͻ�������
		SOCKET sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);//���������̣�ֱ���пͻ�����������Ϊֹ
		if (sockConn == SOCKET_ERROR) {
			printf("Accept failed:%d", WSAGetLastError());
			break;
		}
		char IPdotdec[20];
		inet_ntop(AF_INET, (void *)&addrClient.sin_addr, IPdotdec,16);
		printf("Accept client IP:[%s]\n", IPdotdec);

		//��������
		//send1(sockConn);

		int iSend = send(sockConn, buf, sizeof(buf), 0);
		if (iSend == SOCKET_ERROR) {
			printf("send failed");
			break;
		}
		//pthread_t tids[2];
		//int ret = pthread_create( &tids[0], NULL, send1, (void*)&sockConn ); //�������������߳�id���̲߳������߳����к�������ʼ��ַ�����к����Ĳ���
		HANDLE hThread = CreateThread(NULL, 0, send1, (LPVOID)sockConn, 0, NULL);
		if (hThread == NULL) //�����̳߳ɹ�����0
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
