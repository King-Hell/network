#pragma once
#include<qthread.h>
#include<qdatetime.h>

#include"msocket.h"
class recvThread :public QThread {
	//������Ϣ�߳�
	Q_OBJECT
public:
	recvThread();
	void init(msocket&);
	void run();
	void stop();
signals:
	void sendChat(QString username,QString message);//�������촰��
	void addUser(QString username);//�����û�
	void deleteUser(QString username);//ɾ���û�
private:
	msocket sock;
	bool stopFlag;
};