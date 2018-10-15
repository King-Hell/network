#pragma once
#include <WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#include<iostream>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
//·â×°socket
class msocket {
public:
	msocket() {};
	msocket(char*,int);
	msocket(SOCKET, SOCKADDR_IN);
	~msocket();
	void connect();
	void send(string);
	string recv();
	void error(string);
	void close();
	string getAddress();
private:
	SOCKET sockClient;
	SOCKADDR_IN address;
	char buff[1024];
};