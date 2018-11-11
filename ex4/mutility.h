#pragma once
#include<pcap.h>
char *iptos(u_long in);
char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen);
#pragma comment(lib, "ws2_32.lib")


/* 4字节的IP地址 */
typedef struct ip_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

/* Mac头部 */
typedef struct eth_header
{
	u_char dmac[6];			//目标mac地址  
	u_char smac[6];			//源mac地址  
	u_short eth_type;		//以太网类型  
}eth_hdr;

/* IPv4 头部 */
typedef struct ip_header {
	u_char  ver_ihl;        // 版本 (4 bits) + 首部长度 (4 bits)
	u_char  tos;            // 服务类型(Type of service) 
	u_short tlen;           // 总长(Total length) 
	u_short identification; // 标识(Identification)
	u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)
	u_char  ttl;            // 存活时间(Time to live)
	u_char  proto;          // 协议(Protocol)
	u_short crc;            // 首部校验和(Header checksum)
	ip_address  saddr;      // 源地址(Source address)
	ip_address  daddr;      // 目的地址(Destination address)
	u_int   op_pad;         // 选项与填充(Option + Padding)
}ip_header;

/* UDP 头部*/
typedef struct udp_header {
	u_short sport;          // 源端口(Source port)
	u_short dport;          // 目的端口(Destination port)
	u_short len;            // UDP数据包长度(Datagram length)
	u_short crc;            // 校验和(Checksum)
}udp_header;

/* TCP 头部*/
typedef struct tcp_header {
	u_short sport;			// 源端口(Source port)
	u_short dport;			// 目的端口(Destination port)
	u_int seq;				// 序列号32bit
	u_int ack;				// 确认号32bit
	u_short lenflag;		// 前4位：TCP头长度；中6位：保留；后6位：标志位
	u_short window;			// 窗口大小16bit
	u_short check;			// 检验和16bit
	u_short pointer;		// 紧急数据偏移量16bit

}tcp_header;

u_short checkIP(char *ih);

struct syn {
	eth_header eh;
	ip_header ih;
	tcp_header th;
	syn(ip_address sip, ip_address dip, u_short dport) {
		eh.smac[0] = 0x00;
		eh.smac[1] = 0xdb;
		eh.smac[2] = 0xdf;
		eh.smac[3] = 0xb7;
		eh.smac[4] = 0x34;
		eh.smac[5] = 0x9b;
		eh.dmac[0] = 0x28;
		eh.dmac[1] = 0xa2;
		eh.dmac[2] = 0x4b;
		eh.dmac[3] = 0xf6;
		eh.dmac[4] = 0x12;
		eh.dmac[5] = 0xa0;
		eh.eth_type = htons(0x0800);
		ih.ver_ihl = 0x45;
		ih.tos = 0x00;
		ih.tlen = htons(0x002c);
		ih.identification = 123;
		ih.flags_fo = 0x0000;
		ih.ttl = 128;
		ih.proto = 0x06;
		ih.crc = htons(0x0000);
		ih.saddr = sip;
		ih.daddr = dip;
		ih.crc = htons(checkIP((char*)&ih));
		srand(time(NULL));
		th.sport = htons(rand() % 65535);
		th.dport = dport;
		th.seq = htonl(rand() % 65535);
		th.ack = 0;
		th.lenflag = htons(0x6002);
		th.window = htons(0x0c00);
		th.pointer = 0;
		th.check = 0;
	}
};

u_short checkTCP(syn &pack);

/* TCP伪头部 */
struct fake_tcp {
	ip_address  saddr;      // 源地址(Source address)
	ip_address  daddr;      // 目的地址(Destination address)
	u_char placeholder;	//填充位置
	u_char proto;			//协议(Protocol)
	u_short len;			//TCP头长度
	fake_tcp(syn& pack) {
		saddr = pack.ih.saddr;
		daddr = pack.ih.daddr;
		placeholder = 0;
		proto = pack.ih.proto;
		len = htons(sizeof(tcp_header));
	}
};