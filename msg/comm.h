#ifndef _COMM_
#define _COMM_
#define MAX_SIZE 100
#define PATHNAME "."
#define PROJID 0
#define CLIENT_TYPE 1
#define SERVER_TYPE 2
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<unistd.h>
#include<sys/msg.h>
int creatMegqueue();
int destoryMegqueue(int msgid);
int getMegqueue();
int rcvMeg(int msgid,char out[],int type);
int sndMeg(int msgid,int type,char* meg);

typedef struct meginfo{
	long mtype;
	char mtext[MAX_SIZE];
}meginfo;

#endif  //_COMM
