#ifndef _HTTP_H_
#define _HTTP_H_
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <ctype.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _DEBUG_
#define SIZE 1024
static void clear_head(int sock);
static int readline(int sock,char* buf,int size);
int startup(const char* ip,int port);
void* handle_sock(void* sock);
#endif
