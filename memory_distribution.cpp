#include <stdio.h>
#include <malloc.h>
#include<malloc.h>
void print(char *,int);
int main()
{
    char *s1 = "abcde";
    char *s2 = "abcde";
    char s3[] = "abcd";
    long int *s4[100];
    char *s5 = "abcde";
    int a = 5;
    int b =6;//a,b在栈上，&a>&b 地址反向增长

    printf("variables address in main function:n s1=%p s2=%p s3=%p s4=%p s5=%p a=%p b=%pnn\n",s1,s2,s3,s4,s5,&a,&b);
    printf("variables address in process call:n\n");
    print("ddddddddd",5);//参数入栈从右至左进行,p先进栈,str后进 &p>&str
    printf("nmain=%p print=%pn\n",main,print);
    //打印代码段中主函数和子函数的地址，编译时先编译的地址低，后编译的地址高main<print
	return 0;
}

void print(char *str,int p)
{
    char *s1 = "abcde";//abcde在常量区，s1在栈上
    char *s2 = "abcde";//abcde在常量区，s2在栈上 s2-s1=6可能等于0，编译器优化了相同的常量，只在内存保存一份
    //而&s1>&s2
    char s3[] = "abcdeee";//abcdeee在常量区，s3在栈上，数组保存的内容为abcdeee的一份拷贝
    long int *s4[100];
    char *s5 = "abcde";
    int a = 5;
    int b =6;
    int c;
    int d;//a,b,c,d均在栈上，&a>&b>&c>&d 地址反向增长
    char *q=str;//
    int m=p;//
    char *r=(char *)malloc(1);
    char *w=(char *)malloc(1);// r<w 堆正向增长

    printf("s1=%p s2=%p s3=%p s4=%p s5=%p n\na=%p b=%p c=%p d=%pn str=%p q=%p p=%p m=%p r=%p w=%pn\n",s1,s2,s3,s4,s5,&a,&b,&c,&d,&str,q,&p,&m,r,w);
}
