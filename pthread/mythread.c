#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;
typedef struct node
{
	int _data;
	struct node* _next;
}node,*pnode;

typedef struct Linklist
{
	node * phead;
}Linklist,*pLinklist;

pnode creatNode(int data)
{
	pnode newnode=(pnode)malloc(sizeof(node));
	if(newnode==NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	newnode->_data=data;
	newnode->_next=NULL;
	return newnode;
}

void initList(pLinklist plist)
{
	assert(plist);
	//pLinklist head=(pLinklist)malloc(sizeof(Linklist));
//	plist=head;
	plist->phead=NULL;

}


void pushHead(pLinklist list,int data)
{
	assert(list);
	pnode newnode=creatNode(data);
	if(list->phead==NULL)
	{
		list->phead=newnode;
		return;
	}
	newnode->_next=list->phead;
	list->phead=newnode;
}


void popHead(pLinklist list,int* data)
{
	assert(list);
	if(list->phead==NULL)
	{
		printf("list empty!\n");
		return;
	}
	pnode del=list->phead;
	*data=del->_data;
	list->phead=del->_next;
	del->_next=NULL;
	free(del);
}

void destoryList(pLinklist list)
{
	assert(list);
	if(list->phead!=NULL)
	{
		pnode cur =list->phead;
		while(cur)
		{
			pnode del=cur;
			cur=cur->_next;
			free(del);
			del=NULL;
		}
	}
	list->phead=NULL;

}

void showList(pLinklist list)
{
	assert(list);
	pnode cur=list->phead;
	while(cur!=NULL)
	{
		printf("%d ",cur->_data);
		cur=cur->_next;
	}
	printf("\n");
}
void* producter_thread(void* arg)
{
	pLinklist list=(pLinklist)arg;
	while(1)
	{
			
		sleep(1);
		pthread_mutex_lock(&mylock);   //访问临界区前加锁
		pushHead(list,rand()%1000);
		pthread_cond_signal(&mycond);   //生产完毕唤醒等待在该条件变量下的线程
		pthread_mutex_unlock(&mylock);  //访问结束解锁
		printf("producter success %d\n",list->phead->_data);
	}
}

void* consumer_thread(void* arg)
{
	pLinklist list=(pLinklist)arg;
	while(1)
	{
		sleep(1);

		pthread_mutex_lock(&mylock);  //加锁
		int data=0;
		while(list->phead==NULL)
		{
			pthread_cond_wait(&mycond,&mylock);  //若链表中无数据，则消费者需要等待。
		}
		popHead(list,&data);
		pthread_mutex_unlock(&mylock);    //解锁
		printf("consumer success %d\n",data);
	}
}
int main()
{
	Linklist list;


	initList(&list);
	
//	pushHead(&list,1);
//	pushHead(&list,2);
//	pushHead(&list,3);
//	pushHead(&list,4);
//	pushHead(&list,5);
//	showList(&list);
//
//	int data;
//	popHead(&list,&data);
//	popHead(&list,&data);
//	popHead(&list,&data);
//	popHead(&list,&data);
//	popHead(&list,&data);
//	popHead(&list,&data);
//	showList(&list);

	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,producter_thread,(void*)&list);//创建线程
	pthread_create(&tid2,NULL,consumer_thread,(void*)&list);

	pthread_join(tid1,NULL);   //等待线程结束回收线程
	pthread_join(tid2,NULL);

	destoryList(&list);
	return 0;
}
