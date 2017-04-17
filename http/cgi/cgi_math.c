#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 1024

void add(char*const data)  //data-> xx=100&yy=200
{
	char* data1=NULL;
	char* data2=NULL;
	char* start=data;
	while(*start!='\0')
	{
		if(*start=='='&&data1==NULL)
		{
			data1=start+1;
			start++;
			continue;
		}
		if(*start=='&')
		{
			*start='\0';
		}
		if(*start=='=' && data1!=NULL)
		{
			data2=start+1;
			break;
		}
		start++;
	}
	int num1=atoi(data1);
	int num2=atoi(data2);
	printf("<h1>data1+data2=%d\n<h1>",num1+num2);
}

int main()
{
	printf("<html>\n");
	printf("<head>math</head>\n");
	printf("<body>\n");

	printf("<h1>hehe</h1>\n");
	printf("<h1>shabi</h1>");
	printf("</body>\n");
	printf("</html>\n");
	//char method[SIZE/2];
	//char query_string[SIZE];
	//char post_data[SIZE];
	//int content_len=-1;

	//由于文件描述符已经重定向，此时的输出直接发送给了浏览器
	//strcpy(method,getenv("METHOD"));
	//if(strcasecmp(method,"get")==0)
	//{
	//	strcpy(query_string,getenv("QUERY_STRING"));
	//	add(query_string);
	//}
	//else
	//{
	//	//post
	//	content_len=atoi(getenv("CONTENT_LEN"));
	//	int i=0;
	//	for(;i<content_len;i++)
	//	{
	//		read(0,post_data[i],1);
	//	}
	//	add(post_data);
	//}
	return 0;
}
