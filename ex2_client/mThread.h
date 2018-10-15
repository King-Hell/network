#pragma once
#include<qthread.h>
#include<qdatetime.h>

#include"msocket.h"
class recvThread :public QThread {
	//接受消息线程
	Q_OBJECT
public:
	recvThread();
	void init(msocket&);
	void run();
	void stop();
signals:
	void sendChat(QString username,QString message);//打开新聊天窗口
	void addUser(QString username);//新增用户
	void deleteUser(QString username);//删除用户
private:
	msocket sock;
	bool stopFlag;
};