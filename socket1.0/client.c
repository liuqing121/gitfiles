#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("use way is %s,[ip],[port]\n",argv[0]);
		return -1;
	}
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));
	socklen_t len=sizeof(server);

	if(connect(sock,(struct sockaddr*)&server,len)<0)
	{
		perror("connect");
		exit(2);
	}
	char buf[1024];
	while(1)
	{
		printf("send#:");
		fflush(stdout);
		int s=read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1]='\0';
			write(sock,buf,s);
		}
	}
	close(sock);
	return 0;
}
