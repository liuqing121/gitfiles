#include"comm.h"

static int commShm(int nsem,int IPC)
{
	key_t key=ftok(PATHNAME,PROJID);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}
	int id=semget(key,nsem,IPC);
	if(id<0)
	{
		perror("semget");
		return -1;
	}
	return id;
}
int creatShm()
{
	return commShm(1,IPC_CREAT|IPC_EXCL|0666);
}

int getShm()
{
	return commShm(0,0);
}

int destoryShm(int semId)
{
	int ret=semctl(semId,0,IPC_RMID,NULL);
	if(ret==-1)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}
int initshm(int semId,int which)
{
	union semun _semun;
	_semun.val=1;
	int ret=semctl(semId,which,SETVAL,_semun);
	if(ret==-1)
	{
		perror("semctl");
		return -1;
	}
	return ret;
}
int option(int semId,int which,int flag)
{
	struct sembuf sem;
	sem.sem_num=which;
	sem.sem_op=flag;
	sem.sem_flg=0;
	return semop(semId,&sem,1);
}

int P(int semId,int which)
{
	return option(semId,which,-1);
}

int V(int semId,int which)
{
	return option(semId,which,1);
}
