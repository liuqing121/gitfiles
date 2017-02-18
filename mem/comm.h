#ifndef _COMM_
#define _COMM_
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int creatShm();
int atShm();
int dtShm();
int destoryShm();

#endif //_COMM_
