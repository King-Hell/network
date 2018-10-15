#pragma once
#pragma execution_character_set("utf-8")
#include <WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib, "ws2_32.lib")
#include<qmessagebox.h>

using namespace std;
//·â×°socket
class msocket {
public:
	msocket() {};
	msocket(char*,int);
	~msocket();
	void connect();
	void send(string);
	string recv();
	void error(string&);
	void close();
	string getAddress();
private:
	SOCKET sockClient;
	SOCKADDR_IN address;
	char buff[1024];
};