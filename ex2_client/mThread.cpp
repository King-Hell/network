#include"mThread.h"
#include<iostream>

recvThread::recvThread() {
	stopFlag = false;
}

void recvThread::init(msocket &sock)
{
	this->sock = sock;
}

void recvThread::run() {
	//�����̣߳����ڽ�����Ϣ
	while (!stopFlag) {
		QString message = QString::fromStdString(sock.recv());
		QStringList str = message.split(":");
		QString ins = str[0];
		QString content = str[1];
		if (ins == "CHAT") {
			QStringList info = content.split(";");
			QString chatTo = info[0];
			QString chatContent = info[1];
			QString disp = QTime::currentTime().toString() + "  " + chatTo + ":\n" + chatContent + "\n\n";
			emit sendChat(chatTo,disp);
		}
		else if (ins == "INFO") {
			QStringList info = content.split(";");
			QString chatTo = info[0];
			QString chatContent = info[1];
			if (chatTo == "LOGIN") {
				//�������û�
				emit addUser(chatContent);
			}
			else if (chatTo == "LOGOUT") {
				//ɾ���û�
				emit deleteUser(chatContent);
			}

		}
	}
}

void recvThread::stop()
{
	stopFlag = true;
}
