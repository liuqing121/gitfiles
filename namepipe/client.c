#include<string.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	umask(0);
	if(mkfifo("./fifo",S_IFIFO|0666)==-1)
	{
		perror("mkfifo");
		return -1;
	}
    int fd=open("./fifo",O_WRONLY);
	printf("sd");
	if(fd<0)
	{
		perror("open");
		return -2;
	}
	char buf[100];
	while(1)
	{

		printf("please enter:");
		fflush(stdout);
		int s=read(0,buf,100);
		if(s>0)
		{
			buf[s]='\0';
			write(fd,buf,strlen(buf));
		}
		else
			break;
	}
	close(fd);
	return 0;
}
