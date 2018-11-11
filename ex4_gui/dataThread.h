#pragma once
#include<qthread.h>
#include<qdatetime.h>

#include"mpcap.h"
class dataThread :public QThread {
	//接受消息线程
	Q_OBJECT
public:
	dataThread(mpcap*);
	void run();
	void stop();
	void setIndex(int index);
signals:
	void updateList(QStringList);
private:
	mpcap *mp;
	bool runFlag;
	int index;
};
