#include"mutility.h"

/* 将数字类型的IP地址转换成字符串类型的 */
#define IPTOSBUFFERS    12
char *iptos(u_long in)
{
	static char output[IPTOSBUFFERS][3 * 4 + 3 + 1];
	static short which;
	u_char *p;

	p = (u_char *)&in;
	which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
	sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output[which];
}


char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen)
{
	socklen_t sockaddrlen;

#ifdef WIN32
	sockaddrlen = sizeof(struct sockaddr_in6);
#else
	sockaddrlen = sizeof(struct sockaddr_storage);
#endif


	if (_WINSOCK2API_:: getnameinfo(sockaddr,sockaddrlen,address,addrlen,NULL,0,NI_NUMERICHOST) != 0) 
		address = NULL;

	return address;
}

u_short checkIP(char* ih)
{
	char* ptr_data = ih;
	u_long  tmp = 0;
	u_long  sum = 0;
	for (int i = 0; i < 20; i += 2)
	{
		tmp += (u_char)ptr_data[i] << 8;
		tmp += (u_char)ptr_data[i + 1];
		sum += tmp;
		tmp = 0;
	}
	u_short lWord = sum & 0x0000FFFF;
	u_short hWord = sum >> 16;
	u_short checksum = lWord + hWord;
	checksum = ~checksum;
	return checksum;
}

u_short checkTCP(syn& pack)
{
	fake_tcp ft(pack);
	int buf_size = sizeof(fake_tcp) + sizeof(tcp_header);
	u_char *buffer = new u_char[buf_size];
	memset(buffer, 0x00, buf_size);
	memcpy(buffer, (char*)&ft, sizeof(fake_tcp));
	memcpy(buffer + sizeof(fake_tcp), (char*)&pack.th, sizeof(tcp_header));
	u_long  tmp = 0;
	u_long  sum = 0;
	u_char *ptr_data = buffer;
	for (int i = 0; i < buf_size; i += 2)
	{
		tmp += (u_char)ptr_data[i] << 8;
		tmp += (u_char)ptr_data[i + 1];
		sum += tmp;
		tmp = 0;
	}
	u_short lWord = sum & 0x0000FFFF;
	u_short hWord = sum >> 16;
	u_short checksum = lWord + hWord;
	checksum = ~checksum;

	return checksum;
}
