#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<poll.h>
#define _SIZE_ 128
int startup(char* ip,int port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(ip);
	local.sin_port=htons(port);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock,5)<0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}


int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("usage:%s [local_ip] [loacl_port]\n",argv[0]);
		return 1;
	}
	int listen_sock=startup(argv[1],atoi(argv[2]));

	struct pollfd nfds[_SIZE_];
	int k=0;
	for(k=0;k<_SIZE_;k++)
	{
		nfds[k].fd=-1;
		nfds[k].events=-1;
		nfds[k].revents=0;
	}
	nfds[0].fd=listen_sock;
	nfds[0].events=POLLIN;
	nfds[0].revents=0;
	int timeout=5000;
	while(1)
	{
		switch(poll(nfds,_SIZE_,timeout))
		{
			case 0:
				printf("timeout...\n");
				break;
			case -1:
				perror("poll");
				break;
			default:
				{
					int i=0;
					for(i=0;i<_SIZE_;i++)
					{
						if(nfds[i].revents!=0 && nfds[i].fd==listen_sock)
						{
							struct sockaddr_in peer;
							socklen_t len=sizeof(peer);
							int new_sock=accept(listen_sock,\
									(struct sockaddr*)&peer,&len);
							if(new_sock<0)
							{
								perror("accept");
								continue;
							}
							int j=0;
							for(j=0;j<_SIZE_;j++)
							{
								if(nfds[j].fd==-1)  //找到一个无效的位置
								{
									nfds[j].fd=new_sock;
									nfds[j].events=POLLIN;
									break;
								}
							}
							if(j==_SIZE_)
							{
								close(new_sock);
								printf("many client than size\n");
							}
							printf("get a client ip:%s,port:%d\n"\
									,inet_ntoa(peer.sin_addr),\
									ntohs(peer.sin_port));
						}//if
						else if(nfds[i].fd!=listen_sock && nfds[i].fd!=-1 && (nfds[i].events&POLLIN && nfds[i].revents!=0))
						{
							char buf[_SIZE_];
							ssize_t s=read(nfds[i].fd,buf,_SIZE_-1);
							if(s>0)
							{
								buf[s]=0;
								printf("client send:%s\n",buf);
							}
							else if(s==0)
							{
								printf("client is quit\n");
								close(nfds[i].fd);
								nfds[i].fd=-1;
								continue;
							}
							else
							{
								perror("read");
								continue;
							}
						}//else if
						else
						{//other thing
						}
					}//for
				}//default
				break;
		}//switch
	}
	return 0;
}
