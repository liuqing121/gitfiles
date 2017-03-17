#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int startup(const char* ip,int port)  //创建监听套阶字
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(ip);
	server.sin_port=htons(port);
	socklen_t len=sizeof(server);
	int on=1;  
	if((setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)
 	{  
		 perror("setsockopt");  
		 exit(4);  
    }  
	if(bind(sock,(struct sockaddr*)&server,len)<0)
	{
		perror("bind");
		exit(2);
	}
	if(listen(sock,5)<0)
	{
		perror("listen");
		exit(3);
	}
	return sock;
}


int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Use way:%s,[IP],[port]\n",argv[0]);
		return -1;
	}
	int listen_sock=startup(argv[1],atoi(argv[2]));
	struct sockaddr_in remote;
	socklen_t relen=sizeof(remote);
	while(1)   //接收连接
	{
		int ret=accept(listen_sock,(struct sockaddr*)&remote,&relen);
		printf("client's ip is %s,port is %d\n",inet_ntoa(remote.sin_addr),ntohs(remote.sin_port));
		if(ret<0)
		{
			perror("accept");
			continue;
		}	
		else
		{
			pid_t id=fork();
			if(id==0)
			{
        		//child
        		pid_t id1=fork();
        		if(id1==0)  //孙子进程
        		{
        
        		    char buf[1024];
        		    while(1)
        		    {
        		    	int s=read(ret,buf,sizeof(buf)-1);
        		    	if(s>0)
        		    	{
        		    		buf[s]='\0';
        		    		printf("client#:%s\n",buf);
        		    	}
        		    	else
        		    	{
        		    		printf("client is quit!\n");
        		    		break;
        		    	}
        		    }
					close(ret);
        		}
        		else
        		{
        			exit(0);
        		}
			}
			else if(id>0)
			{
				//father
				continue;
			}
			else
			{
				perror("fork");
				close(ret);
			}
		}
	}
	return 0;
}