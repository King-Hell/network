#pragma once
#include<pcap.h>
char *iptos(u_long in);
char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen);
#pragma comment(lib, "ws2_32.lib")
#pragma pack(1)

/* 4�ֽڵ�IP��ַ */
typedef struct ip_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

typedef struct eth_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	u_char byte5;
	u_char byte6;
}eth_address;

/* Macͷ�� */
typedef struct eth_header
{
	eth_address dmac;			//Ŀ��mac��ַ  
	eth_address smac;			//Դmac��ַ  
	u_short eth_type;		//��̫������  
}eth_hdr;

/* IPv4 ͷ�� */
typedef struct ip_header {
	u_char  ver_ihl;        // �汾 (4 bits) + �ײ����� (4 bits)
	u_char  tos;            // ��������(Type of service) 
	u_short tlen;           // �ܳ�(Total length) 
	u_short identification; // ��ʶ(Identification)
	u_short flags_fo;       // ��־λ(Flags) (3 bits) + ��ƫ����(Fragment offset) (13 bits)
	u_char  ttl;            // ���ʱ��(Time to live)
	u_char  proto;          // Э��(Protocol)
	u_short crc;            // �ײ�У���(Header checksum)
	ip_address  saddr;      // Դ��ַ(Source address)
	ip_address  daddr;      // Ŀ�ĵ�ַ(Destination address)
	//u_int   op_pad;         // ѡ�������(Option + Padding)
}ip_header;

/* UDP ͷ��*/
typedef struct udp_header {
	u_short sport;          // Դ�˿�(Source port)
	u_short dport;          // Ŀ�Ķ˿�(Destination port)
	u_short len;            // UDP���ݰ�����(Datagram length)
	u_short crc;            // У���(Checksum)
}udp_header;

/* TCP ͷ��*/
typedef struct tcp_header {
	u_short sport;			// Դ�˿�(Source port)
	u_short dport;			// Ŀ�Ķ˿�(Destination port)
	u_int seq;				// ���к�32bit
	u_int ack;				// ȷ�Ϻ�32bit
	u_short lenflag;		// ǰ4λ��TCPͷ���ȣ���6λ����������6λ����־λ
	u_short window;			// ���ڴ�С16bit
	u_short check;			// �����16bit
	u_short pointer;		// ��������ƫ����16bit

}tcp_header;

u_short checkIP(char *ih);

struct syn {
	eth_header eh;
	ip_header ih;
	tcp_header th;
	syn(ip_address sip, ip_address dip, u_short dport) {
		eh.smac.byte1 = 0x00;
		eh.smac.byte2 = 0xdb;
		eh.smac.byte3 = 0xdf;
		eh.smac.byte4 = 0xb7;
		eh.smac.byte5 = 0x34;
		eh.smac.byte6 = 0x9b;
		eh.dmac.byte1 = 0x28;
		eh.dmac.byte2 = 0xa2;
		eh.dmac.byte3 = 0x4b;
		eh.dmac.byte4 = 0xf6;
		eh.dmac.byte5 = 0x12;
		eh.dmac.byte6 = 0xa0;
		/*eh.smac.byte1 = 1;
		eh.smac.byte2 = 1;
		eh.smac.byte3 = 1;
		eh.smac.byte4 = 1;
		eh.smac.byte5 = 1;
		eh.smac.byte6 = 1;
		eh.dmac.byte1 = 2;
		eh.dmac.byte2 = 2;
		eh.dmac.byte3 = 2;
		eh.dmac.byte4 = 2;
		eh.dmac.byte5 = 2;
		eh.dmac.byte6 = 2;*/
		eh.eth_type = htons(0x0800);
		ih.ver_ihl = 0x45;
		ih.tos = 0x00;
		ih.tlen = htons(0x0028);
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
		th.dport = htons(dport);
		th.seq = htonl(rand() % 65535);
		th.ack = 0;
		th.lenflag = htons(0x5002);
		th.window = htons(0x0c00);
		th.pointer = 0;
		th.check = 0;
	}
};

u_short checkTCP(syn &pack);

/* TCPαͷ�� */
struct fake_tcp {
	ip_address  saddr;      // Դ��ַ(Source address)
	ip_address  daddr;      // Ŀ�ĵ�ַ(Destination address)
	u_char placeholder;	//���λ��
	u_char proto;			//Э��(Protocol)
	u_short len;			//TCPͷ����
	fake_tcp(syn& pack) {
		saddr = pack.ih.saddr;
		daddr = pack.ih.daddr;
		placeholder = 0;
		proto = pack.ih.proto;
		len = htons(sizeof(tcp_header));
	}
};
