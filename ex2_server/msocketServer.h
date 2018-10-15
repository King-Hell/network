#pragma once
#include <WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#include<iostream>
#pragma comment(lib, "ws2_32.lib")

#include"msocket.h"

using namespace std;
//·â×°socket
class msocketServer {
public:
	msocketServer(int);
	~msocketServer();
	msocket* accept();
	void error(string);
	void close();
private:
	SOCKET sockServer;
	SOCKADDR_IN address;
	char buff[1024];
};