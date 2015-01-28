#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<errno.h>
#include<sys/time.h>
#include<ctype.h>
#include<sys/select.h>
#include<pthread.h>
#include<time.h>

struct client_info
{
  char ID[32];
  char name[32];
   char password[32];
   time_t t;
   struct client_info *next;
};
static int connect_server(struct sockaddr_in c_servaddr)
{
  int chose;
  int ret;
  char buf[100]="hello word";
  int c_sockfd;
  struct hostent *server;
  if(inet_pton(AF_INET,"127.0.0.1",&c_servaddr.sin_addr.s_addr)<=0)
  {
    printf("inet_pton error");
   return -1;
  }
 if((c_sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
  {
    printf("c_sockfd error");
    return -1;
  }
  c_servaddr.sin_family=AF_INET;
  c_servaddr.sin_port=htons(8088);
  struct client_info *ptr;
  ptr=(struct client_info *)malloc(sizeof(struct client_info));
  printf("请输入ID号\n");
  scanf("%s",ptr->ID);
  getchar();
  printf("请输入昵称\n");
  scanf("%s",ptr->name);
  getchar();
  printf("请输入密码\n");
  scanf("%s",ptr->password);
  ptr-> t=time(NULL);
  getchar();
  printf("连接中发送中........\n");

  ret=connect(c_sockfd,(struct sockaddr *)&c_servaddr,sizeof(c_servaddr));

 if(ret<0)
 {
   printf("connect error\n");
   return -1;
 }
 else
 {  
	 int count=0;
	 while(count<2)
	 {
		write(c_sockfd,ptr,sizeof(struct client_info));
		sleep(2);
		count++;
	 }
    //if(write(c_sockfd,ptr,sizeof(struct client_info))<0)
   // {
     //  printf("write error");
      // return -1;
    //}
  }
  
 fflush(stdout);
}
int main()
{
  struct sockaddr_in c_servaddr;
  connect_server(c_servaddr);
  return 0;
}
