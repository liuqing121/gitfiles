#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
int main()
{
	if(fork()>0)
	{
		exit(0);
	}
	umask(0);
	setsid();
	chdir("/");
	close(0);
	close(1);
	close(2);
	signal(SIGCHLD,SIG_IGN);
	while(1)
	{
		sleep(1);
	}
	return 0;
}
