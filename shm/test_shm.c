#include"comm.h"

int main()
{
	int semid=creatShm();
	if(semid<0)
	{
		printf("creat shm error\n");
		return -1;
	}
	initshm(semid,0);
	pid_t id=fork();
	if(id==0)
	{
		//child
		while(1)
		{
			P(semid,0);
			usleep(10000);
			printf("A");
			fflush(stdout);
			usleep(100);
			printf("A");
			fflush(stdout);
			V(semid,0);
		}
	}
	else if(id>0)
	{
		//father
		while(1)
		{
			P(semid,0);
			usleep(100000);
			printf("B");
			fflush(stdout);
			usleep(1000);
			printf("B");
			fflush(stdout);
			V(semid,0);
		}
		wait(NULL);
	}
	destoryShm(semid);
	return 0;
}

