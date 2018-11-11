#include "mpcap.h"

mpcap::mpcap()
{//���캯��
	alldevs = NULL;
	adhandle = NULL;
	id = 0;
	scanOpen = false;
}

QStringList mpcap::getDevices()
{
	char rpcap[] = PCAP_SRC_IF_STRING;
	/* ��ȡ���ػ����豸�б� */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
		exit(1);
	}
	QStringList list;
	pcap_if_t *d;
	pcap_addr_t *a;
	/* ��ӡ�б� */
	for (d = alldevs; d != NULL; d = d->next)
	{
		devicesList.push_back(d);
		QString info;
		if (d->description) {
			QString	str = d->description;
			QStringList sp = str.split('\'');
			info.append(sp[1]);
		}
		/* IP��ַ */
		for (a = d->addresses; a; a = a->next) {
			switch (a->addr->sa_family)
			{
			case AF_INET:
				info.append("\nIPv4��ַ:");
				if (a->addr)
					info.append(iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
				break;
			case AF_INET6:
				info.append("\nIPv6��ַ:");
				char ip6str[128];
				if (a->addr)
					info.append(ip6tos(a->addr, ip6str, sizeof(ip6str)));
				break;

			default:
				info.append("\nδ֪����Э��");
				break;
			}

		}
		list.append(info);
	}

	return list;
}

void mpcap::freeAllDevices()
{
	if (alldevs != NULL)
		pcap_freealldevs(alldevs);
}

QStringList mpcap::getData()
{
	int res;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	struct tm ltime;
	time_t local_tv_sec;
	ip_header *ih;
	udp_header *uh;
	tcp_header *th;
	u_int ip_len;
	u_short sport, dport;
	QStringList info;
	for (int i = 0; i < 7; i++)
		info.append("");
	info.append(QString::number(id));
	/* ��ȡ���ݰ� */
	if ((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0) {
		if (res == 0) {
			/* ��ʱʱ�䵽 */
			return info;
		}
		/* ��ʱ���ת���ɿ�ʶ��ĸ�ʽ */
		local_tv_sec = header->ts.tv_sec;
		localtime_s(&ltime, &local_tv_sec);
		strftime(timestr, sizeof timestr, "%H:%M:%S", &ltime);

		/* ��ӡ���ݰ���ʱ��� */
		info[0] = timestr;
		info[6] = QString::number(header->len);
		/* ���IP���ݰ�ͷ����λ�� */
		ih = (ip_header *)(pkt_data + 14); //��̫��ͷ������

		/* ���UDP�ײ���λ�� */
		ip_len = (ih->ver_ihl & 0xf) * 4;
		//Դ��ַ��Ŀ�ĵ�ַ
		sprintf(sip, "%d.%d.%d.%d", ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4);//Դ��ַ
		info[2] = sip;
		sprintf(dip, "%d.%d.%d.%d", ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4);//Ŀ�ĵ�ַ
		info[4] = dip;
		if (ih->proto == 6) {
			//TCPЭ��
			info[1] = "TCP";
			th = (tcp_header *)((u_char*)ih + ip_len);
			/* �������ֽ�����ת���������ֽ����� */
			sport = ntohs(th->sport);//Դ�˿�
			sprintf(port, "%d", sport);
			info[3] = port;
			dport = ntohs(th->dport);//Ŀ�Ķ˿�
			sprintf(port, "%d", dport);
			info[5] = port;
			if (scanOpen&&ntohl(th->seq )!= 0) {
				openPort.insert(ntohs(th->sport));
			}
		}
		else if (ih->proto == 17) {
			//UDPЭ��
			info[1] = "UDP";
			uh = (udp_header *)((u_char*)ih + ip_len);
			/* �������ֽ�����ת���������ֽ����� */
			sport = ntohs(uh->sport);//Դ�˿�
			sprintf(port, "%d", sport);
			info[3] = port;
			dport = ntohs(uh->dport);//Ŀ�Ķ˿�
			sprintf(port, "%d", dport);
			info[5] = port;
		}
		else if (ih->proto == 1) {
			//ICMPЭ��
			info[1] = "ICMP";
		}
		else {
			//δ֪Э��
			sprintf(protocal, "%d", ih->proto);
			info[1] = protocal;
		}
		u_char *dataContent = new u_char[header->len];
		for (int i = 0; i < header->len; i++)
			dataContent[i] = pkt_data[i];
		mdata *da = new mdata(header->len, dataContent);
		dataMap.insert(id, da);
	}

	if (res == -1) {
		printf("Error reading the packets: %s\n", pcap_geterr(adhandle));
		info[0] = ("Error reading the packets");
	}
	id++;
	return info;
}

bool mpcap::openDevice(int index)
{//��һ��������
	u_int netmask;
	struct bpf_program fcode;
	/* ���豸 */
	if ((adhandle = pcap_open(devicesList[index]->name,          // �豸��
		65536,            // Ҫ��׽�����ݰ��Ĳ��� 
						  // 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
		PCAP_OPENFLAG_PROMISCUOUS,    // ����ģʽ
		1000,             // ��ȡ��ʱʱ��
		NULL,             // Զ�̻�����֤
		errbuf            // ���󻺳��
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", devicesList[index]->name);
		return false;
	}
	/* ���������·�㣬Ϊ�˼򵥣�����ֻ������̫�� */
	if (pcap_datalink(adhandle) != DLT_EN10MB)
	{
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return false;
	}

	if (devicesList[index]->addresses != NULL)
		/* ��ýӿڵ�һ����ַ������ */
		netmask = ((struct sockaddr_in *)(devicesList[index]->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* ����ӿ�û�е�ַ����ô���Ǽ���һ��C������� */
		netmask = 0xffffff;


	//���������
	if (pcap_compile(adhandle, &fcode, packet_filter.toStdString().c_str(), 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return false;
	}

	//���ù�����
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return false;
	}
	return true;
}

void mpcap::clear()
{
	devicesList.clear();
}

void mpcap::setFilter(QString option) {
	packet_filter = option;
}

void mpcap::clearData()
{
	dataMap.clear();
	id = 0;
}

mdata * mpcap::getData(int id)
{
	if (dataMap.find(id) != dataMap.end())
		return dataMap.find(id).value();
	else
		return NULL;
}

void mpcap::sendSyn(ip_address &dip,int port)
{
	//QStringList list =QString(iptos(((struct sockaddr_in *)devicesList[currentID]->addresses->addr)->sin_addr.s_addr)).split(".");
	scanOpen = true;
	QStringList list = QString("172.25.140.122").split(".");
	ip_address sip;
	sip.byte1 = list[0].toUInt();
	sip.byte2 = list[1].toUInt();
	sip.byte3 = list[2].toUInt();
	sip.byte4 = list[3].toUInt();
	syn pack(sip,dip,port);
	pack.th.check =htons (checkTCP(pack));
	u_char *data_pack = (u_char*)&pack;
	int ret=pcap_sendpacket(adhandle,data_pack, sizeof(syn));
}

