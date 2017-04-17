#include"httpd.h"

int main(int argc, char* argv[])
{
	if(argc!=3)
	{
		printf("usage:%s [ip] [port]",argv[0]);
		return 1;
	}

	int listen_sock=startup(argv[1],atoi(argv[2]));
	struct sockaddr_in peer;
	socklen_t len=sizeof(peer);
	while(1)
	{
		int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
		if(sock<0)
		{
			perror("accept");
			return 2;
		}
		printf("get a client ip:%s port:%d\n",inet_ntoa(peer.sin_addr),peer.sin_port);
#ifdef _DEBUG_
		printf("sock is:%d\n",sock);
#endif
		pthread_t id;
		pthread_create(&id,NULL,handle_sock,(void*)sock);
	}
	return 0;
}
