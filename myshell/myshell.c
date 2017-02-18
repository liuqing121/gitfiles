#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#define MAX 80
int main()
{
	while(1)
	{
		printf("liuqing@bogon code]@ ");
		fflush(stdout);
		char buf[MAX];
		char * p=NULL;
		char * myArgv[MAX];
		int i=1;
		int num=read(0,buf,1024);  //等待输入
		if(num>0)   //读到了内容
		{
			buf[num]='\0';
		}
		else
		{
			continue;
		}

		p=buf;
		myArgv[0]=p;
		while(*p)
		{
			if(isspace(*p))
			{
				
				*p='\0';
				p++;
				myArgv[i++]=p;
			}
			else
			{
				p++;
			}
		}
		myArgv[i-1]=NULL;
		pid_t pid=fork();

		if(pid==0)
		{
			//child
			execvp(myArgv[0],myArgv);
			printf("error");
		}
		else if(pid>0)
		{
			//farther
			wait(NULL);
		}
		else
			printf("fork error");
	}

	return 0;
}
