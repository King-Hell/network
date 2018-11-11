#pragma once
#include<qstringlist.h>
#include<qmap.h>
#include<pcap.h>
#include<qset.h>
#include"mutility.h"
#pragma execution_character_set("utf-8")
struct mdata {
	int length;
	u_char* content;
	mdata(int length, u_char* content) :length(length), content(content) {};
	~mdata() { delete content; }
};

class mpcap {
public:
	mpcap();
	QStringList getDevices();//获取设备列表
	void freeAllDevices();//释放所有设备
	QStringList getData();//抓取数据
	bool openDevice(int index);//打开一个设备
	void clear();//清空设备列表
	void setFilter(QString option);
	void clearData();
	mdata* getData(int id);
	void sendSyn(ip_address &dip,int port);
	QSet<int> getOpen() { return openPort;}


private:
	pcap_if_t *alldevs;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE], sip[16], dip[16], port[6], protocal[4], timestr[16];
	QList<pcap_if_t*> devicesList;
	QString packet_filter = "tcp or udp";//过滤选项
	QMap<int, mdata*> dataMap;
	int id;//记录数据包ID
	bool scanOpen;
	QSet<int> openPort;
};

