#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define _SIZE_ 128

int gfds[_SIZE_];

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
	socklen_t len=sizeof(local);

	if(bind(sock,(struct sockaddr*)&local,len)<0)
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
		printf("usage:%s,[local_ip][local_port]\n",argv[0]);
		return 1;
	}
	int i=0;
	for(;i<_SIZE_;i++)  //初始化全局的文件描述符集合为无效
	{
		gfds[i]=-1;
	}
	
	int listen_sock=startup(argv[1],atoi(argv[2]));
	fd_set rfds;
	while(1)
	{
		gfds[0]=listen_sock;

		FD_ZERO(&rfds);
		FD_SET(listen_sock,&rfds);
		int max_fd=-1;
		int j=0;
	
		for(;j<_SIZE_;j++)
		{
			if(gfds[j]!=-1)
			{
				if(max_fd<gfds[j])
				{
					max_fd=gfds[j];
				}
				FD_SET(gfds[j],&rfds);
			}
		}
		struct timeval timeout={5,0};
		switch(select(max_fd+1,&rfds,NULL,NULL,/*&timeout*/NULL))
		{
			case 0:
				printf("timeout...\n");
				break;
			case -1:
				perror("select");
				break;
			default:
				{
					int k=0;
					for(;k<_SIZE_;k++)
					{
						if(gfds[k]==-1)
						{
							break;
						}
						else if(gfds[k]==listen_sock&&FD_ISSET(gfds[k],&rfds))
						{
							struct sockaddr_in peer;
							socklen_t len=sizeof(peer);
							int new_sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
							printf("get a client:%s:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
							if(new_sock<0)
							{
								perror("accept");
								continue;
							}
							else//产生了一个新的套接字，需要set进rfds。
							{
								int m=0;
								for(;m<_SIZE_;m++)
								{
									if(gfds[m]==-1) //找到一个无效的位置
									{
										gfds[m]=new_sock;
										FD_SET(new_sock,&rfds);
										break;
									}
								}
								if(m==_SIZE_)  //没有无效的位置，处理不了了
								{
									close(new_sock);
									printf("too many client\n ");
								}
							}
						}
						else if(FD_ISSET(gfds[k],&rfds))
						{
							char buf[1024];
							int s=read(gfds[k],buf,sizeof(buf)-1);
							if(s<0)
							{
								perror("read");
								break;
							}
							else if(s==0)
							{
								printf("client is quit!\n");
								close(gfds[k]);
								gfds[k]=-1;   
								continue;
							}
							else
							{
								buf[s]=0;
								printf("client:%s\n",buf);

							}
						}
						else
						{
							continue;
						}

					}
					
				}
				break;
		}

	}
	close(listen_sock);
	return 0;
}

