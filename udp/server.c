#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//server.c
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("usage:%s,[local_ip],[local_port]\n",argv[0]);
		exit(1);
	}
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("sock");
		exit(2);
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(argv[1]);
	local.sin_port=htons(atoi(argv[2]));

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(3);
	}

	char buf[1024];
	while(1)
	{
		struct sockaddr_in peer;
		socklen_t len=sizeof(peer);
		memset((void*)&peer,0,sizeof(peer));
		int s=recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&peer,&len);
		if(s<0)
		{
			perror("recvfrom");
			continue;
		}
		else if(s>0)
		{
			printf("client's ip:%s,port is:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
			buf[s]='\0';
			printf("client#%s\n",buf);
		}
		else
		{
			printf("debug\n");
		}
	}
	close(sock);

	return 0;
}
