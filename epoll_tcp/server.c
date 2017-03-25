#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<string.h>
#define _SIZE_ 10240
typedef struct epbuf
{
	int fd;
	char buf[_SIZE_];
}epbuf_t,*epbuf_p;

static epbuf_p alloc_epbuf(int fd)
{
	epbuf_p ptr=(epbuf_p)malloc(sizeof(epbuf_t));
	if(NULL==ptr)
	{
		perror("malloc");
		exit(7);
	}
	ptr->fd=fd;
	return ptr;
}
static void del_epbuf(epbuf_p ptr)
{
	if(NULL!=ptr)
	{
		free(ptr);
	}
}
int startup(char* ip,int port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(2);
	}
	int opt=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
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

	int epfd=epoll_create(256);
	if(epfd<0)
	{
		perror("epoll_create");
		return 5;
	}
	struct epoll_event ep;
	ep.events=EPOLLIN|EPOLLET;
	ep.data.ptr=alloc_epbuf(listen_sock);
	epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&ep);
	while(1)
	{
		struct epoll_event evs[32];
		int max_evs=32;    //就绪队列的长度为32.
		int timeout=5000;
		int nums=0;
		switch((nums=epoll_wait(epfd,evs,max_evs,timeout)))
		{
			case 0:
				printf("timeout\n");
				break;
			case -1:
				perror("epoll_wait");
				break;
			default:
				{
					int i=0;
					for(;i<nums;i++)
					{
						int fd=((epbuf_p)(evs[i].data.ptr))->fd;
						if(fd==listen_sock && (evs[i].events&EPOLLIN))
						{
							struct sockaddr_in peer;
							socklen_t len = sizeof(peer);
							int sock=accept(fd,(struct sockaddr*)&peer,&len);
							if(sock<0)
							{
								perror("accept");
								continue;
							}

							printf("get a client:ip[%s],port[%d]\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
							ep.events=EPOLLIN;
							ep.data.ptr=alloc_epbuf(sock);
							if(epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ep)<0)
							{
								perror("epoll_ctl");
							}
						}	//if
						else if(fd!=listen_sock && (evs[i].events&EPOLLIN))
						{
							char* buf=((epbuf_p)(evs[i].data.ptr))->buf;
							ssize_t s=read(fd,buf,_SIZE_-1);
							if(s<0)
							{
								perror("read");
								break;
							}
							else if(s==0)  //客户端退出
							{
								printf("client is quit\n");
								del_epbuf(evs[i].data.ptr);
								evs[i].data.ptr=NULL;
								epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
								close(fd);
							}
							else
							{
								buf[s]=0;
								printf("client:%s\n",buf);
								ep.events=EPOLLOUT;
								epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ep);
							}
						}//else if
						else if(fd!=listen_sock && (evs[i].events&EPOLLOUT))
						{
						
							const char* msg="HTTP/1.0 200 OK\r\n\r\n<html><h1>hello world</h1></html>\n";
							write(fd,msg,strlen(msg));
							del_epbuf(evs[i].data.ptr);
							evs[i].data.ptr=NULL;
							//响应一次就断开连接。
							epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
							close(fd);
						} //else if epollout
						else //关心的其他事件
						{
						}

					}//for
				}//default
				break;
		}
	}
	return 0;
}
