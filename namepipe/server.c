#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main()
{
	int fd=open("./fifo",O_RDONLY);
	if(fd<0)
	{
		perror("open");
		return -1;
	}
	char ret[100];
	while(1)
	{

		int s=read(fd,ret,100);
		if(s>0)
		{
					ret[s]='\0';
			printf("server read:%s\n",ret);
		}
		else
		{
			perror("read\n");
			break;
		}
	}
	close(fd);
	return 0;
    }
