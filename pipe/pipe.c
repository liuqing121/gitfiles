#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main()
{
	int _file[2]={0,0};
	int ret=pipe(_file);
	if(ret==-1)
	{
		perror("pipe");
		return 1;
	}
	
	pid_t id=fork();
	if(id==0)
	{
		//子进程
		close(_file[0]); //子进程关闭读端
		char * meg="i am child";
		int count=5;
		while(count--)
		{
			write(_file[1],meg,strlen(meg));	
			sleep(1);
		}
		close(_file[1]);
	}
	else if(id>0)
	{
		//father
		close(_file[1]);  //父进程关闭写端
		int count=5;
		char meg[100];
		while(count--)
		{
			int s=read(_file[0],meg,100);
			meg[s]='\0';
			printf("father read:%s\n",meg);
			fflush(stdout);
		}
		close(_file[0]);
	}
	else
		perror("fork");
	return 0;
}
