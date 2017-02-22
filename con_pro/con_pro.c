#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#define _SIZE_ 64
sem_t blank;
sem_t data;
sem_t pro_lock;
sem_t con_lock;
int ring[_SIZE_];
void* pro_run(void* arg)
{
	pthread_detach(pthread_self());
	int i=0;
	int id=(int)arg;
	while(1)
	{
		sleep(1);
		sem_wait(&blank);
		sem_wait(&pro_lock);
		int num=rand()%1000;
		ring[i++]=num;
		printf("生产者%d生产：%d,tid:%lu\n",id,num,pthread_self());
		i%=_SIZE_;
		sem_post(&pro_lock);
		sem_post(&data);
	}
}


void* con_run(void* arg)
{
	pthread_detach(pthread_self());
	int i=0;
	int id=(int)arg;
	while(1)
	{
		sleep(1);
		sem_wait(&data);
		sem_wait(&con_lock);
		printf("消费者%d消费：%d,tid:%lu\n:",id,ring[i++],pthread_self());
		i%=_SIZE_;
		sem_post(&con_lock);
		sem_post(&blank);
	}
}
int main()
{
	pthread_t producter,consumer,producter1,consumer1;
	sem_init(&blank,0,_SIZE_);
	sem_init(&data,0,0);
	sem_init(&pro_lock,0,1);
	sem_init(&con_lock,0,1);
	int i=0;
	pthread_create(&producter,NULL,pro_run,(void*)i);
	pthread_create(&consumer,NULL,con_run,(void*)i);
	i++;
	pthread_create(&producter1,NULL,pro_run,(void*)i);
	pthread_create(&consumer1,NULL,con_run,(void*)i);
	sem_destroy(&blank);
	sem_destroy(&data);
	pthread_join(producter,NULL);
	pthread_join(consumer,NULL);
	return 0;
}
