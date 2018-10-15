#include "msocketServer.h"

msocketServer::msocketServer(int port) {
	//构造方法
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //加载套接字库
		error(string("Failed to load Winsock"));
	//创建用于监听的套接字
	sockServer = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(port); //1024以上的端口号
	address.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //INADDR_ANY 代表任意ip

	int retVal = bind(sockServer, (LPSOCKADDR)&address, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR)
		error(string("Failed bind:%d\n") + to_string(WSAGetLastError()));

	if (listen(sockServer, 10) == SOCKET_ERROR) //10代表允许连接的个数
		error(string("Listen failed:%d") + to_string(WSAGetLastError()));

}

msocketServer::~msocketServer() {
	//析构方法
	close();
}

msocket* msocketServer::accept() {
	//等待客户端连接
	SOCKADDR_IN address;
	int len = sizeof(SOCKADDR);
	SOCKET sock =_WINSOCK2API_::accept(sockServer, (SOCKADDR*)&address, &len);//会阻塞进程，直到有客户端连接上来为止
	msocket *client = new msocket(sock,address);
	if (sock == SOCKET_ERROR) 
		error(string("Accept failed:")+to_string(WSAGetLastError()));
	return client;
}

void msocketServer::error(string info) {
	//错误处理
	cout << info << endl;
	throw exception();
}

void msocketServer::close() {
	//关闭连接
	closesocket(sockServer);
	WSACleanup();
}
