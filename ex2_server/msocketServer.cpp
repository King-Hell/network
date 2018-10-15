#include "msocketServer.h"

msocketServer::msocketServer(int port) {
	//���췽��
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //�����׽��ֿ�
		error(string("Failed to load Winsock"));
	//�������ڼ������׽���
	sockServer = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(port); //1024���ϵĶ˿ں�
	address.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //INADDR_ANY ��������ip

	int retVal = bind(sockServer, (LPSOCKADDR)&address, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR)
		error(string("Failed bind:%d\n") + to_string(WSAGetLastError()));

	if (listen(sockServer, 10) == SOCKET_ERROR) //10�����������ӵĸ���
		error(string("Listen failed:%d") + to_string(WSAGetLastError()));

}

msocketServer::~msocketServer() {
	//��������
	close();
}

msocket* msocketServer::accept() {
	//�ȴ��ͻ�������
	SOCKADDR_IN address;
	int len = sizeof(SOCKADDR);
	SOCKET sock =_WINSOCK2API_::accept(sockServer, (SOCKADDR*)&address, &len);//���������̣�ֱ���пͻ�����������Ϊֹ
	msocket *client = new msocket(sock,address);
	if (sock == SOCKET_ERROR) 
		error(string("Accept failed:")+to_string(WSAGetLastError()));
	return client;
}

void msocketServer::error(string info) {
	//������
	cout << info << endl;
	throw exception();
}

void msocketServer::close() {
	//�ر�����
	closesocket(sockServer);
	WSACleanup();
}
