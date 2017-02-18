#include"comm.h"
int main()
{
	int megid=creatMegqueue();
	if(megid<0)
	{
		printf("creat meg error!\n");
		return -1;
	}
	char buf[100];
	char out[100];
	while(1)
	{

		printf("client enter:");
		fflush(stdout);
		int s=read(0,buf,100);
		if(s>0)
		{
			buf[s]='\0';
			sndMeg(megid,CLIENT_TYPE,buf);
			sleep(1);
		}
		else
		{
			break;
		}
		if(rcvMeg(megid,out,SERVER_TYPE)<0)
		{
			break;
		}
	}
	destoryMegqueue(megid);
	return 0;
}
