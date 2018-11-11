#include "msocket.h"

msocket::msocket(char *ip,int port) {
	//���췽��
	//�����׽���
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		error(string("Failed to load Winsock"));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if (inet_pton(AF_INET, ip, &address.sin_addr.S_un.S_addr) <= 0)  //��ַ
		error(string("ip address error for")+ ip);
	//�����ͻ����׽���
	sockClient = socket(AF_INET, SOCK_RAW, 0);//ԭʼ�׽���
	if (SOCKET_ERROR == sockClient)
		error(string("Socket() error:")+to_string(WSAGetLastError()));
}

msocket::msocket(SOCKET sock, SOCKADDR_IN address){
	this->sockClient = sock;
	this->address = address;
}

msocket::~msocket() {
	//��������
	close();
}

void msocket::connect() {
	if (_WINSOCK2API_::connect(sockClient, (struct sockaddr*)&address, sizeof(address)) == INVALID_SOCKET) 
		error(string("���ӷ�����ʧ��"));
}

void msocket::send(string message) {
	//���ͷ���
	const char *ch = message.c_str();
	strcpy_s(buff, message.length() + 1, ch);
	int ret =_WINSOCK2API_::send(sockClient, buff, sizeof(buff), 0);
	if (ret == SOCKET_ERROR) 
		error(string("send failed"));
}

string msocket::recv() {
	//���ܷ���
	int ret = _WINSOCK2API_::recv(sockClient, buff, sizeof(buff), 0);
	if(ret==SOCKET_ERROR)
		error(string("receive failed"));
	string message = buff;
	return message;
}

void msocket::error(string info) {
	//��������
	cout << info << endl;
	throw exception();
}

void msocket::close() {
	//�ر�����
	closesocket(sockClient);
}

string msocket::getAddress()
{
	char ip[20];
	inet_ntop(AF_INET, (void *)&address.sin_addr, ip, 16);
	return string(ip);
}
