#include"comm.h"

static int commMegqueue(int ID)
{
	key_t key=ftok(PATHNAME,PROJID);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}
	int msgid=msgget(key,ID);
	if(msgid<0)
	{
		perror("msgget");
		return -2;
	}
	return msgid;
}
int creatMegqueue()
{
	return commMegqueue(IPC_CREAT|IPC_EXCL|0666);
}
int getMegqueue()
{
	return commMegqueue(0);

}
int destoryMegqueue(int msgid)
{
	if(msgctl(msgid,IPC_RMID,NULL)==-1)
	{
		perror("msgctl");
		return -1;
	}
	return 0;
}

int rcvMeg(int msgid,char out[],int type)
{
	meginfo info;
	int size=msgrcv(msgid,&info,sizeof(info),type,0);
	if(size<0)
	{
		perror("msgrcv");
		return -1;
	}
	strncpy(out,info.mtext,size);
	out[size]='\0';
	return size;
}
int sndMeg(int msgid,int type,char* meg)
{
	meginfo info;
	info.mtype=type;
	strcpy(info.mtext,meg);
	if(msgsnd(msgid,&info,sizeof(info.mtext),0)==-1)
	{
		perror("msgsnd");
		return -1;
	}
	else
		return 0;
}

