#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//client.c
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("usage:%s,[peer_ip],[peer_port]\n",argv[0]);
		exit(1);
	}
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("sock");
		exit(2);
	}

	char buf[1024];
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));

	while(1)
	{
		printf("please enter:");
		fflush(stdout);
		int s=read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			int m=sendto(sock,buf,s,0,(struct sockaddr*)&server,sizeof(server));

			if(m<0)
			{
				perror("sendto");
				continue;
			}
		}
	}
	close(sock);
	return 0;
}
