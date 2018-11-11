///*
// * Copyright (c) 1999 - 2005 NetGroup, Politecnico di Torino (Italy)
// * Copyright (c) 2005 - 2006 CACE Technologies, Davis (California)
// * All rights reserved.
// *
// * Redistribution and use in source and binary forms, with or without
// * modification, are permitted provided that the following conditions
// * are met:
// *
// * 1. Redistributions of source code must retain the above copyright
// * notice, this list of conditions and the following disclaimer.
// * 2. Redistributions in binary form must reproduce the above copyright
// * notice, this list of conditions and the following disclaimer in the
// * documentation and/or other materials provided with the distribution.
// * 3. Neither the name of the Politecnico di Torino, CACE Technologies
// * nor the names of its contributors may be used to endorse or promote
// * products derived from this software without specific prior written
// * permission.
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
// */
//
//#include "pcap.h"
//
// /* 4�ֽڵ�IP��ַ */
//typedef struct ip_address {
//	u_char byte1;
//	u_char byte2;
//	u_char byte3;
//	u_char byte4;
//}ip_address;
//
///* IPv4 ͷ�� */
//typedef struct ip_header {
//	u_char  ver_ihl;        // �汾 (4 bits) + �ײ����� (4 bits)
//	u_char  tos;            // ��������(Type of service) 
//	u_short tlen;           // �ܳ�(Total length) 
//	u_short identification; // ��ʶ(Identification)
//	u_short flags_fo;       // ��־λ(Flags) (3 bits) + ��ƫ����(Fragment offset) (13 bits)
//	u_char  ttl;            // ���ʱ��(Time to live)
//	u_char  proto;          // Э��(Protocol)
//	u_short crc;            // �ײ�У���(Header checksum)
//	ip_address  saddr;      // Դ��ַ(Source address)
//	ip_address  daddr;      // Ŀ�ĵ�ַ(Destination address)
//	u_int   op_pad;         // ѡ�������(Option + Padding)
//}ip_header;
//
///* UDP ͷ��*/
//typedef struct udp_header {
//	u_short sport;          // Դ�˿�(Source port)
//	u_short dport;          // Ŀ�Ķ˿�(Destination port)
//	u_short len;            // UDP���ݰ�����(Datagram length)
//	u_short crc;            // У���(Checksum)
//}udp_header;
//
///* TCP ͷ��*/
//typedef struct tcp_header {
//	u_short sport;			// Դ�˿�(Source port)
//	u_short dport;			// Ŀ�Ķ˿�(Destination port)
//	u_int seq;				// ���к�32bit
//	u_int ack;				// ȷ�Ϻ�32bit
//	u_short lenflag;		// ǰ4λ��TCPͷ���ȣ���6λ����������6λ����־λ
//	u_short window;			// ���ڴ�С16bit
//	u_short check;			// �����16bit
//	u_short pointer;		// ��������ƫ����16bit
//
//}tcp_header;
//
///* �ص�����ԭ�� */
//void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
//
//
//int main()
//{
//	pcap_if_t *alldevs;
//	pcap_if_t *d;
//	int inum;
//	int i = 0;
//	pcap_t *adhandle;
//	char errbuf[PCAP_ERRBUF_SIZE];
//	u_int netmask;
//	char packet_filter[] = "tcp or udp port 443 or port 53 and src host 114.114.114.114";
//	struct bpf_program fcode;
//	char a[] = PCAP_SRC_IF_STRING;
//	/* ����豸�б� */
//	if (pcap_findalldevs_ex(a, NULL, &alldevs, errbuf) == -1)
//	{
//		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
//		exit(1);
//	}
//
//	/* ��ӡ�б� */
//	for (d = alldevs; d; d = d->next)
//	{
//		printf("%d. %s", ++i, d->name);
//		if (d->description)
//			printf(" (%s)\n", d->description);
//		else
//			printf(" (No description available)\n");
//	}
//
//	if (i == 0)
//	{
//		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
//		return -1;
//	}
//
//	printf("Enter the interface number (1-%d):", i);
//	scanf_s("%d", &inum);
//
//	if (inum < 1 || inum > i)
//	{
//		printf("\nInterface number out of range.\n");
//		/* �ͷ��豸�б� */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	/* ��ת����ѡ�豸 */
//	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);
//
//	/* �������� */
//	if ((adhandle = pcap_open(d->name,  // �豸��
//		65536,     // Ҫ��׽�����ݰ��Ĳ��� 
//				   // 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
//		PCAP_OPENFLAG_PROMISCUOUS,         // ����ģʽ
//		1000,      // ��ȡ��ʱʱ��
//		NULL,      // Զ�̻�����֤
//		errbuf     // ���󻺳��
//	)) == NULL)
//	{
//		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
//		/* �ͷ��豸�б� */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	/* ���������·�㣬Ϊ�˼򵥣�����ֻ������̫�� */
//	if (pcap_datalink(adhandle) != DLT_EN10MB)
//	{
//		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
//		/* �ͷ��豸�б� */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	if (d->addresses != NULL)
//		/* ��ýӿڵ�һ����ַ������ */
//		netmask = ((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
//	else
//		/* ����ӿ�û�е�ַ����ô���Ǽ���һ��C������� */
//		netmask = 0xffffff;
//
//
//	//���������
//	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
//	{
//		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
//		/* �ͷ��豸�б� */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	//���ù�����
//	if (pcap_setfilter(adhandle, &fcode) < 0)
//	{
//		fprintf(stderr, "\nError setting the filter.\n");
//		/* �ͷ��豸�б� */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	printf("\nlistening on %s...\n", d->description);
//
//	/* �ͷ��豸�б� */
//	pcap_freealldevs(alldevs);
//
//	/* ��ʼ��׽ */
//	pcap_loop(adhandle, 0, packet_handler, NULL);
//
//	return 0;
//}
//
///* �ص����������յ�ÿһ�����ݰ�ʱ�ᱻlibpcap������ */
//void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
//{
//	struct tm ltime;
//	char timestr[16];
//	ip_header *ih;
//	udp_header *uh;
//	u_int ip_len;
//	u_short sport, dport;
//	time_t local_tv_sec;
//
//	/* ��ʱ���ת���ɿ�ʶ��ĸ�ʽ */
//	local_tv_sec = header->ts.tv_sec;
//	localtime_s(&ltime,&local_tv_sec);
//	strftime(timestr, sizeof timestr, "%H:%M:%S", &ltime);
//
//	/* ��ӡ���ݰ���ʱ����ͳ��� */
//	printf("%s len:%d ",timestr,header->len);
//
//	/* ���IP���ݰ�ͷ����λ�� */
//	ih = (ip_header *)(pkt_data +
//		14); //��̫��ͷ������
//
//	printf("protocal:%d ", ih->proto);
//	/* ���UDP�ײ���λ�� */
//	ip_len = (ih->ver_ihl & 0xf) * 4;
//	uh = (udp_header *)((u_char*)ih + ip_len);
//
//	/* �������ֽ�����ת���������ֽ����� */
//	sport = ntohs(uh->sport);
//	dport = ntohs(uh->dport);
//
//	/* ��ӡIP��ַ��UDP�˿� */
//	printf("%d.%d.%d.%d.%d -> %d.%d.%d.%d.%d\n",
//		ih->saddr.byte1,
//		ih->saddr.byte2,
//		ih->saddr.byte3,
//		ih->saddr.byte4,
//		sport,
//		ih->daddr.byte1,
//		ih->daddr.byte2,
//		ih->daddr.byte3,
//		ih->daddr.byte4,
//		dport);
//}
#include <stdlib.h>
#include <stdio.h>

#include <pcap.h>
#include"mutility.h"

void main(int argc, char **argv)
{
	pcap_t *fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_char packet[100];

	///* ��������в����ĺϷ��� */
	//if (argc != 2)
	//{
	//	printf("usage: %s interface (e.g. 'rpcap://eth0')", argv[0]);
	//	return;
	//}
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i = 0;
	pcap_t *adhandle;
	int res;
	struct tm *ltime;
	char timestr[16];
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	time_t local_tv_sec;
	u_char f = 0x11;

	/* ��ȡ�����豸�б� */
	char a[] = PCAP_SRC_IF_STRING;
	if (pcap_findalldevs_ex(a, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* ��ӡ�б� */
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return;
	}

	printf("Enter the interface number (1-%d):", i);
	scanf_s("%d", &inum);

	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return;
	}

	/* ��ת����ѡ�е������� */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);
	/* ������豸 */
	if ((fp = pcap_open(d->name,            // �豸��
		100,                // Ҫ����Ĳ��� (ֻ����ǰ100���ֽ�)
		PCAP_OPENFLAG_PROMISCUOUS,  // ����ģʽ
		1000,               // ����ʱʱ��
		NULL,               // Զ�̻�����֤
		errbuf              // ���󻺳�
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", argv[1]);
		return;
	}

	///* ��������̫���ϣ�����MAC��Ŀ�ĵ�ַΪ 1:1:1:1:1:1 */
	packet[0] = 1;
	packet[1] = 1;
	packet[2] = 1;
	packet[3] = 1;
	packet[4] = 1;
	packet[5] = 1;

	/* ����MACԴ��ַΪ 2:2:2:2:2:2 */
	packet[6] = 2;
	packet[7] = 2;
	packet[8] = 2;
	packet[9] = 2;
	packet[10] = 2;
	packet[11] = 2;

	/* ���ʣ�µ����� */
	for (i = 12; i < 100; i++)
	{
		packet[i] = i % 256;
	}

	/* �������ݰ� */
	if (int ret=pcap_sendpacket(fp, packet, 100 /* size */) != 0)
	{
		fprintf(stderr, "\nError sending the packet: \n", pcap_geterr(fp));
	}
	system("pause");
	return;
}