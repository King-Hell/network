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
// /* 4字节的IP地址 */
//typedef struct ip_address {
//	u_char byte1;
//	u_char byte2;
//	u_char byte3;
//	u_char byte4;
//}ip_address;
//
///* IPv4 头部 */
//typedef struct ip_header {
//	u_char  ver_ihl;        // 版本 (4 bits) + 首部长度 (4 bits)
//	u_char  tos;            // 服务类型(Type of service) 
//	u_short tlen;           // 总长(Total length) 
//	u_short identification; // 标识(Identification)
//	u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)
//	u_char  ttl;            // 存活时间(Time to live)
//	u_char  proto;          // 协议(Protocol)
//	u_short crc;            // 首部校验和(Header checksum)
//	ip_address  saddr;      // 源地址(Source address)
//	ip_address  daddr;      // 目的地址(Destination address)
//	u_int   op_pad;         // 选项与填充(Option + Padding)
//}ip_header;
//
///* UDP 头部*/
//typedef struct udp_header {
//	u_short sport;          // 源端口(Source port)
//	u_short dport;          // 目的端口(Destination port)
//	u_short len;            // UDP数据包长度(Datagram length)
//	u_short crc;            // 校验和(Checksum)
//}udp_header;
//
///* TCP 头部*/
//typedef struct tcp_header {
//	u_short sport;			// 源端口(Source port)
//	u_short dport;			// 目的端口(Destination port)
//	u_int seq;				// 序列号32bit
//	u_int ack;				// 确认号32bit
//	u_short lenflag;		// 前4位：TCP头长度；中6位：保留；后6位：标志位
//	u_short window;			// 窗口大小16bit
//	u_short check;			// 检验和16bit
//	u_short pointer;		// 紧急数据偏移量16bit
//
//}tcp_header;
//
///* 回调函数原型 */
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
//	/* 获得设备列表 */
//	if (pcap_findalldevs_ex(a, NULL, &alldevs, errbuf) == -1)
//	{
//		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
//		exit(1);
//	}
//
//	/* 打印列表 */
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
//		/* 释放设备列表 */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	/* 跳转到已选设备 */
//	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);
//
//	/* 打开适配器 */
//	if ((adhandle = pcap_open(d->name,  // 设备名
//		65536,     // 要捕捉的数据包的部分 
//				   // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
//		PCAP_OPENFLAG_PROMISCUOUS,         // 混杂模式
//		1000,      // 读取超时时间
//		NULL,      // 远程机器验证
//		errbuf     // 错误缓冲池
//	)) == NULL)
//	{
//		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
//		/* 释放设备列表 */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	/* 检查数据链路层，为了简单，我们只考虑以太网 */
//	if (pcap_datalink(adhandle) != DLT_EN10MB)
//	{
//		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
//		/* 释放设备列表 */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	if (d->addresses != NULL)
//		/* 获得接口第一个地址的掩码 */
//		netmask = ((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
//	else
//		/* 如果接口没有地址，那么我们假设一个C类的掩码 */
//		netmask = 0xffffff;
//
//
//	//编译过滤器
//	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
//	{
//		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
//		/* 释放设备列表 */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	//设置过滤器
//	if (pcap_setfilter(adhandle, &fcode) < 0)
//	{
//		fprintf(stderr, "\nError setting the filter.\n");
//		/* 释放设备列表 */
//		pcap_freealldevs(alldevs);
//		return -1;
//	}
//
//	printf("\nlistening on %s...\n", d->description);
//
//	/* 释放设备列表 */
//	pcap_freealldevs(alldevs);
//
//	/* 开始捕捉 */
//	pcap_loop(adhandle, 0, packet_handler, NULL);
//
//	return 0;
//}
//
///* 回调函数，当收到每一个数据包时会被libpcap所调用 */
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
//	/* 将时间戳转换成可识别的格式 */
//	local_tv_sec = header->ts.tv_sec;
//	localtime_s(&ltime,&local_tv_sec);
//	strftime(timestr, sizeof timestr, "%H:%M:%S", &ltime);
//
//	/* 打印数据包的时间戳和长度 */
//	printf("%s len:%d ",timestr,header->len);
//
//	/* 获得IP数据包头部的位置 */
//	ih = (ip_header *)(pkt_data +
//		14); //以太网头部长度
//
//	printf("protocal:%d ", ih->proto);
//	/* 获得UDP首部的位置 */
//	ip_len = (ih->ver_ihl & 0xf) * 4;
//	uh = (udp_header *)((u_char*)ih + ip_len);
//
//	/* 将网络字节序列转换成主机字节序列 */
//	sport = ntohs(uh->sport);
//	dport = ntohs(uh->dport);
//
//	/* 打印IP地址和UDP端口 */
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

	///* 检查命令行参数的合法性 */
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

	/* 获取本机设备列表 */
	char a[] = PCAP_SRC_IF_STRING;
	if (pcap_findalldevs_ex(a, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* 打印列表 */
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
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return;
	}

	/* 跳转到已选中的适配器 */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);
	/* 打开输出设备 */
	if ((fp = pcap_open(d->name,            // 设备名
		100,                // 要捕获的部分 (只捕获前100个字节)
		PCAP_OPENFLAG_PROMISCUOUS,  // 混杂模式
		1000,               // 读超时时间
		NULL,               // 远程机器验证
		errbuf              // 错误缓冲
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", argv[1]);
		return;
	}

	///* 假设在以太网上，设置MAC的目的地址为 1:1:1:1:1:1 */
	packet[0] = 1;
	packet[1] = 1;
	packet[2] = 1;
	packet[3] = 1;
	packet[4] = 1;
	packet[5] = 1;

	/* 设置MAC源地址为 2:2:2:2:2:2 */
	packet[6] = 2;
	packet[7] = 2;
	packet[8] = 2;
	packet[9] = 2;
	packet[10] = 2;
	packet[11] = 2;

	/* 填充剩下的内容 */
	for (i = 12; i < 100; i++)
	{
		packet[i] = i % 256;
	}

	/* 发送数据包 */
	if (int ret=pcap_sendpacket(fp, packet, 100 /* size */) != 0)
	{
		fprintf(stderr, "\nError sending the packet: \n", pcap_geterr(fp));
	}
	system("pause");
	return;
}