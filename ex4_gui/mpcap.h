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
	QStringList getDevices();//��ȡ�豸�б�
	void freeAllDevices();//�ͷ������豸
	QStringList getData();//ץȡ����
	bool openDevice(int index);//��һ���豸
	void clear();//����豸�б�
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
	QString packet_filter = "tcp or udp";//����ѡ��
	QMap<int, mdata*> dataMap;
	int id;//��¼���ݰ�ID
	bool scanOpen;
	QSet<int> openPort;
};

