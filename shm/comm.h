#ifndef _COMM_
#define _COMM_

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#define PATHNAME "."
#define PROJID 0
union semun {
	int val; // 使⽤的值
	struct semid_ds *buf; // IPC_STAT、 IPC_SET 使⽤缓存区
	unsigned short *array; // GETALL,、 SETALL 使⽤的数组
	struct seminfo *__buf; // IPC_INFO(Linux特有) 使⽤缓存区
};
int creatShm();
static int commShm(int nsem,int IPC);
int initshm(int semId,int which);
int getShm();
int destoryShm(int semId);
int option(int semId,int which,int flag);
int P(int semId,int which);
int V(int semId,int which);
#endif

