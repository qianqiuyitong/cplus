#include<sys/types.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<errno.h>
#include<sys/time.h>
#include<stdio.h>
#include<strings.h>
#include<sys/select.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<iostream>
 

struct pack
{
  char ID[32];
  char IP[32];
  char name[32];
  char password[32];
  time_t ltime;
  struct pack *next;
};
struct client_info
{
  char ID[32];
  char name[32];
  char password[32];
  time_t t;
  struct client_info *next;
};
struct pack *Head=NULL;

void c_printf();

int main()
{
 int ret;
 pthread_t idx;
 struct sockaddr_in s_servaddr,s_cliaddr;
 int request_sock,new_sock;
 int nfound,fd,maxfd,readnumber;
 uint32_t addrlen;
 fd_set rset,set;
 char buf[1024];
 //user_line("./data/user_data");
 request_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//开始socket编程
 printf("the request_sock is %d\n",request_sock);
 if(request_sock < 0 )
  {
   printf("socket error");
   return -1;
  }
 memset(&s_servaddr,0,sizeof(s_servaddr));
 s_servaddr.sin_family = AF_INET;//协议族 IPV4
 s_servaddr.sin_addr.s_addr = INADDR_ANY;//经由任何可绑定的地址 IPV4
 s_servaddr.sin_port = htons(8088);//端口
 printf("bind...\n");
        //绑定计算机IP地址和端口信息到socket上
    if(bind(request_sock,(struct sockaddr *)&s_servaddr,sizeof(s_servaddr))<0)
    {
       printf("bind error");
       return -1;
    }
 printf("listen...\n");
       //已绑定的套接口开始监听 10为规定内核为套接口排队的最大连接数
 if(listen(request_sock,10) < 0)
 {
  printf("listen error");
  return -1;
 }
 FD_ZERO(&set);//对指定文件描述符进行清空初始化，否则出问题
 
 std::cout<<"the set is "<<set.fds_bits[0]<<std::endl;
 FD_SET(request_sock,&set);//在文件描述符集合中增加一个新的文件描述符
 maxfd = request_sock;
 std::cout<<"the set is "<<set.fds_bits[0]<<std::endl;
 while(1)
 {
  rset = set;
  printf("select now...\n");
  sleep(3);
  //确定一个和多个套接口的状态(可读)
  nfound = select(maxfd + 1,&rset,(fd_set *)0,(fd_set *)0,NULL);
  printf("%d\n",nfound);

  if(nfound < 0)//不修改任何描述符集
  {
    printf("select error");
    return -1;
  }
  else if(nfound == 0)//描述符被清0
  {
    printf(".");fflush(stdout);
    continue;
  }
 std::cout<<"the request_sock is "<<request_sock<<std::endl;
  if(FD_ISSET(request_sock,&rset))//检测request有无被改变
  {
    printf("request_sock\n");
    addrlen = sizeof(s_cliaddr);
    printf("accept...\n");
    //连接。。
    addrlen=sizeof(struct sockaddr_in);
    new_sock = accept(request_sock,(struct sockaddr*)&s_cliaddr,&addrlen);
	std::cout<<"the new_sock is "<<new_sock<<std::endl;
    if(new_sock < 0)//错误时返回－1
    {
      printf("accept error");
      return -1;
    }
    printf("connection form host %s,port %d,socket%d\r\n",inet_ntoa(s_cliaddr.sin_addr),ntohs(s_cliaddr.sin_port),new_sock);
    FD_SET(new_sock,&set);

    if(new_sock > maxfd)
            maxfd = new_sock;
    inet_ntoa(s_cliaddr.sin_addr);
    FD_CLR(request_sock,&rset);//把负责监听的新我文件描述符清空
    
	nfound--; 
  }
   
    struct client_info *ptr;
    struct pack *str;
    for(fd=0;fd<=maxfd&&nfound>0;fd++)
    {
      if(FD_ISSET(fd,&rset))
      {
        nfound--;
        ptr=(struct client_info *)malloc(sizeof(struct client_info));
        memset(ptr,0,sizeof(struct client_info));
        printf("读包头\n");
        if((readnumber=read(fd,ptr,sizeof(struct client_info)))<0)
        { 
          printf("read error");
          return -1;
        }
        if(readnumber==0)
        {
          printf("read over\n");
          FD_CLR(fd,&set);
          close(fd);
          continue;
        }
     // } 
      str=(struct pack *)malloc(sizeof(struct pack));
      memset(str,0,sizeof(struct pack));
      strcpy(str->ID,ptr->ID);
      strcpy(str->name,ptr->name);
      strcpy(str->password,ptr->password);
      str->ltime=ptr->t;
      str->next=Head;
      Head=str;   
      }
	}	//for
     // c_printf();
             // break;
    }
         // c_printf();
       // sleep(2);
    close(new_sock);
    return 0;
}

void c_printf()
{
  printf("显示在线人员信息\n");
  struct pack *p;
  p=Head;
  printf("客户ID 客户昵称 客户密码 连接时间\n");
  while(p!=NULL)
  {
    printf("99\n"); 
    printf("%3s,%7s,%8s,%13d\n",p->ID,p->name,p->password,p->ltime);
    p=p->next;
  }
}
