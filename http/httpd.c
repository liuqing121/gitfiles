#include"httpd.h"
static void clear_head(int sock)
{
	int ret=0;
	char buf[SIZE];
	do{
		ret=readline(sock,buf,sizeof(buf));
	}while(ret>0 && strcmp(buf,"\n")!=0);
}
static void show_404(int sock)
{
	clear_head(sock); 
	char* msg="HTTP/1.0 404	Not Found\r\n"; 
	send(sock,msg,strlen(msg),0);         //发送状态行 
	send(sock,"\r\n",strlen("\r\n"),0);      //发送空行 
 
	struct stat st; 
	stat("wwwroot/404.html",&st); 
	int fd=open("wwwroot/404.html",O_RDONLY); 
	sendfile(sock,fd,NULL,st.st_size); 
	close(fd); 

}
static void show_405(int sock)
{
	clear_head(sock); 
	char* msg="HTTP/1.0 405	Not Found\r\n"; 
	send(sock,msg,strlen(msg),0);         //发送状态行 
	send(sock,"\r\n",strlen("\r\n"),0);      //发送空行 
 
	struct stat st; 
	stat("wwwroot/405.html",&st); 
	int fd=open("wwwroot/405.html",O_RDONLY); 
	sendfile(sock,fd,NULL,st.st_size); 
	close(fd); 

}

static void show_500(int sock)
{
	clear_head(sock); 
	char* msg="HTTP/1.0 500	Service Error\r\n"; 
	send(sock,msg,strlen(msg),0);         //发送状态行 
	send(sock,"\r\n",strlen("\r\n"),0);      //发送空行 
 
	struct stat st; 
	stat("wwwroot/500.html",&st); 
	int fd=open("wwwroot/500.html",O_RDONLY); 
	sendfile(sock,fd,NULL,st.st_size); 
	close(fd); 
}
void echo_error(int sock,int num)
{
	switch(num)
	{
		case 404:
			show_404(sock);
			break;
		case 405:   //请求方法不正确
			show_405(sock);
			break;  
		case 500:   //服务器遇到错误，无法处理请求
			show_500(sock);
			break;
		default:
			break;
	}
}
void print_log(const char* ident,int degree,const char* meg)
{
	int flag=-1;
	switch(degree)
	{
		case 0:
			flag=LOG_ERR;
			break;
		case 1:
			flag=LOG_ALERT;
			break;
		case 2:
			flag=LOG_WARNING;
		case 3:
			flag=LOG_INFO;
			break;
		default:
			break;
	}
	//openlog(ident, LOG_CONS | LOG_PID, LOG_USER); 
	openlog(ident,LOG_CONS | LOG_PID,LOG_USER);
	//syslog(flag, "%s",meg);
	syslog(flag,"%s",meg);
	closelog();
}

int startup(const char* ip,int port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		const char* meg="apply sock error";
		print_log("socket",0,meg);
		exit(3);
	}
	int on=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=inet_addr(ip);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		const char* meg="bind sock filed";
		print_log("bind",0,meg);
		exit(4);
	}
	if(listen(sock,5)<0)
	{
		const char*meg="set listen sock filed!";
		print_log("listen",0,meg);
		exit(5);
	}
	return sock;
}
static int readline(int sock,char* buf,int size)
{
	if(buf==NULL || size<0)
	{
		return -1;
	}
	char ch='\0';
	int i=0;
	while(ch!='\n'&&(i<size-1))
	{
		if(recv(sock,&ch,1,0)<0) //读失败
		{
			const char* meg="recv char error!";
			print_log("recv",0,meg);
			perror("recv");
			exit(6);
		}
		if(ch=='\r')  //把\r \n \r\n全部转换成\n
		{
			recv(sock,&ch,1,MSG_PEEK); //窥探下一个字符
			if(ch=='\n')    //如果是\n则直接读取，相当与把 \r\n->\n
			{
				recv(sock,&ch,1,0);
			}
			
			ch='\n';  //\r->\n
			
		}
		buf[i++]=ch;
	}
	buf[i]='\0';
	return i;
}
static int echo_www(int sock,const char*path,int len) //处理非cgi请求
{
	int fd=open(path,O_RDONLY);
	if(fd<0)
	{
		echo_error(sock,404);
		return 9;
	}
	char buf[SIZE];
	char buf1[SIZE];
	sprintf(buf,"HTTP/1.0 200 OK\r\n");
	send(sock,buf,sizeof(buf),0);
	sprintf(buf1,"Content-Type: text/html;charset=GBK\r\n");
	send(sock,buf1,sizeof(buf1),0);
	send(sock,"\r\n",sizeof("\r\n"),0);
	if(sendfile(sock,fd,NULL,len)<0)
	{
		echo_error(sock,500);
		const char* meg="sendfile error!";
		print_log("sendfile",1,meg);
		close(fd);
		return 10;
	}
	close(fd);

}
static int exec_cgi(int sock,const char*path,const char* method,const char*query_string)
{
#ifdef _DEBUG_
	printf("exec_cgi begin\n");
	printf("cgi path is:%s\n",path);
#endif
	//双向通信的管道
	int input[2];
	int output[2];
	int content_length=-1;
	char buf[SIZE];
	int ret=-1;
#ifdef _DEBUG_
	printf("exec_cgi method:%s\n",method);
#endif
	if(strcasecmp(method,"get")==0)  //get则参数已经在query_string保存
	{
		clear_head(sock);
	}
	//post 拿到参数的字节数
	else
	{
    	do{
    		memset(buf,'\0',sizeof(buf));
    		ret=readline(sock,buf,sizeof(buf));
    		if(strncasecmp(buf,"Content-Length:",strlen("Content-Length:"))==0)
    		{
    			content_length=atoi(&buf[16]);
    #ifdef _DEBUG_
    	printf("post readline is:%s\n",buf);
    	printf("content_length:%d\n",content_length);
    #endif
    		}
    	}while( ret >0 && strcmp(buf,"\n")!=0);
	    if(content_length==-1)
	    {
	    	echo_error(sock,404);  //post方法一定得有Content_length字段	
			return 12;
	    }
	}


	if(pipe(input)<0)
	{
#ifdef _DEBUG_
	printf("pipe error\n");
#endif
		const char* meg="creat pipe error!";
		print_log("pipe",0,meg);  //管道资源不足
		return 11;
	}
	if(pipe(output)<0)
	{
#ifdef _DEBUG_
	printf("pipe error\n");
#endif
		close(input[0]);
		close(input[1]);
		const char* meg="creat pipe error!";
		print_log("pipe",0,meg);
		return 12;
	}
	char sbuf[SIZE];
	sprintf(sbuf,"HTTP/1.0 200 OK\r\n");
	send(sock,sbuf,sizeof(sbuf),0);
	memset(sbuf,'\0',sizeof(sbuf));
	sprintf(sbuf,"Content-Type: text/html;charset=GBK\r\n");
	send(sock,sbuf,sizeof(sbuf),0);
	send(sock,"\r\n",sizeof("\r\n"),0);
#ifdef _DEBUG_
	printf("send title success\n");
#endif
	char query_env[SIZE/2];
	char method_env[SIZE/2];
	char content_env[SIZE/10];
	memset(query_env,'\0',sizeof(query_env));
	memset(method_env,'\0',sizeof(method_env));
	memset(content_env,'\0',sizeof(content_env));
	sprintf(method_env,"METHOD=%s",method);
	putenv(method_env);
	if(strcasecmp(method,"get")==0)
	{
		sprintf(query_env,"QUERY_STRING=%s",query_string);
		putenv(query_env);
	}
	if(strcasecmp(method,"post")==0)
	{
		sprintf(content_env,"CONTENT_LEN=%d",content_length);
		putenv(content_env);
	}
#ifdef _DEBUG_
		printf("putenv success\n");
#endif
	pid_t id=fork();
	if(id<0)
	{
#ifdef _DEBUG_
	printf("fork filed\n");
#endif
		close(input[0]);
		close(input[1]);
		close(output[0]);
		close(output[1]);
		const char* meg="fork error";
		print_log("fork",0,meg);
		echo_error(sock,500);  //资源不够，服务器错误
		return 13;
	}
	else if(id==0)
	{
		//child
#ifdef _DEBUG_
	printf("child begin\n");
#endif
		close(input[1]);
		close(output[0]);
		//文件描述符重定向

		dup2(input[0],0);
		dup2(output[1],1);
		//执行程序替换
		execl(path,path,NULL);
		exit(1);
	}
	else
	{
		//father
#ifdef _DEBUG_
	printf("father begin\n");
#endif
		close(input[0]); //关闭input的读端
		close(output[1]);  //关闭output的写端
		char ch='\0';
		int i=0;
		if(strcasecmp(method,"post")==0)//从sock里读数据写给子进程
		{
			for(;i<content_length;i++)
			{
				recv(sock,&ch,1,0);
				write(input[1],&ch,1);
			}

		}
    	char buf[SIZE];
    	char buf1[SIZE];
    	sprintf(buf,"HTTP/1.0 200 OK\r\n");
    	send(sock,buf,sizeof(buf),0);
    	sprintf(buf1,"Content-Type: text/html;charset=GBK\r\n");
    	send(sock,buf1,sizeof(buf1),0);
    	send(sock,"\r\n",sizeof("\r\n"),0);
		//从子进程里读数据写进sock。
		while(read(output[0],&ch,1)>0)
		{
			send(sock,&ch,1,0);
		}
		close(input[1]);
		close(output[0]);
		waitpid(id,NULL,0);
#ifdef _DEBUG_
		printf("waitpid success\n");
#endif
	}
}
void* handle_sock(void* fd)
{

	pthread_detach(pthread_self());
	int sock=(int)fd;
	char request_line[SIZE];
	char method[SIZE];
	char path[SIZE];
	char url[SIZE];
	char* query_string=NULL;
	int cgi=0;
	int ret=0;
//	do{
//		//读取请求行
//		ret=readline(sock,request_line,sizeof(request_line));
//		printf("%s\n",request_line);
//		fflush(stdout);
//
//	}while(ret>0 &&(strcmp(request_line,"\n")!=0));
	//获取请求方法
	if(readline(sock,request_line,sizeof(request_line))<0)
	{
		ret=6;
		goto end;
	}

#ifdef _DEBUG_
	printf("%s\n",request_line);
#endif
	int i=0;
	int j=0;
	while((i<sizeof(request_line)-1)&&(j<sizeof(method)-1)&&(!isspace(request_line[i])))
	{
		method[j++]=request_line[i++];
	}
	method[j]='\0';
#ifdef _DEBUG_
	printf("method:%s\n",method);
#endif
	//目前只处理get和post方法
	if((strcasecmp(method,"GET")!=0) && (strcasecmp(method,"POST")!=0))
	{
		echo_error(sock,405);
		ret=7;
		goto end;
	}
	//get方法会将参数放在url中，而post方法参数在请求正文里。一旦有参数传递，我们都要使得cgi有效。且post方法一定使用cgi接口
	if(strcasecmp(method,"post")==0)
	{
		cgi=1;
	}	
	while(isspace(request_line[i])) //请求方法后可能会有多个空格
	{
		i++;
	}
	//获取url
	j=0;
	while((i<sizeof(request_line)-1) && (j<sizeof(request_line)-1) &&(!isspace(request_line[i])))
	{
		url[j++]=request_line[i++];
	}
	url[j]='\0';
	//get方法可在url中拿到参数
	if(strcasecmp(method,"get")==0)
	{
		query_string=url;
		//参数以？作为分割符
		while(*query_string!='\0' && *query_string!='?')
		{
			query_string++;
		}
		if(*query_string=='?') //有参数
		{
			cgi=1;   
			*query_string++='\0';
		}
	}
	sprintf(path,"wwwroot%s",url);
	if(path[strlen(path)-1]=='/')   //如果请求的是根目录
	{
		strcat(path,"index.html"); //返回首页
	}
	//判断请求的资源类型
	struct stat st;
	if(stat(path,&st)<0)
	{
		echo_error(sock,404);
		//exit(8);
		ret=8;
		clear_head(sock);
		goto end;
	}
	if(S_ISDIR(st.st_mode)) //请求的是一个目录
	{
		strcat(path,"wwwroot/index.html");
	}
	else if((st.st_mode&S_IXUSR) ||(st.st_mode&S_IXGRP)|| (st.st_mode&S_IXOTH))
		//请求的是一个可执行程序
	{
		cgi=1;
	}
	else
	{}

	if(cgi)
	{
		ret=exec_cgi(sock,path,method,query_string);
	}
	else
	{
		clear_head(sock);
		ret=echo_www(sock,path,st.st_size);
	}
end:
	close(sock);
	return (void*)ret;
}
