#include"comm.h"

int main()
{
	int megid=getMegqueue();
	if(megid<0)
	{
		printf("get megid error!\n");	
		return -1;
	}
	char out[100];
	while(1)
	{
		int sz=rcvMeg(megid,out,CLIENT_TYPE);
		if(sz>0)
		{
			printf("server recerve:%s",out);
			fflush(stdout);
		}
		else
		{
			break;
		}
		if(sndMeg(megid,SERVER_TYPE,out)<0)
		{
			break;
		}
		sleep(1);
	}
	return 0;
}
