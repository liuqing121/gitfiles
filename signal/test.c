#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void fun()
{
	int count=0;
	int i=5;
	while(i--)
	{
		sleep(1);
		count++;
		printf("count:%d\n",count);
	}
}
int main()
{
	signal(2,fun);
	fun();
	return 0;
}
