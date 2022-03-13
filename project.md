socket 底层原理


## 简易的linux socket聊天室
这是linux系统下一个简易的用socket实现的聊天室
主要采用C/S模式，基于socket编程，实现各个客户端之间的正常通信，服务器端使用sqlite数据库存储用户数据

+ 实现了用户注册，登录功能。
+ 实现了用户间公聊、私聊功能。
+ 实现离线上线提示。
+ 在线查看聊天记录功能。

+ 服务器端使用epoll边缘触发模式。
+ 客户端使用多线程保证键盘读入与读入同时进行

1.统一定义了通信格式
里面cmd表示功能，state表示请求的响应状态，name标识用户，data传输的数据
(宏定义完成)

#define BROADCAST 0X00000001   //广播数据
#define PRIVATE 0X00000002     //私聊
#define REGISTE 0X00000004     //注册账号
#define LOGIN 0X00000008       //登录
#define ONLINEUSER     0X00000010 //显示在线用户
#define LOGOUT     0X00000020    //退出
								//在线查看聊天记录
								//注册登录

state
#define OP_OK    0X80000000         //操作成功
#define ONLINEUSER_OK    0X80000001  //显示在线用户，未结束
#define ONLINEUSER_OVER  0X80000002  //显示在线用户，已经发送完毕
#define NAME_EXIST 0X80000003       //注册信息，用户名已经存在
#define NAME_PWD_NMATCH 0X80000004 //登录时，输入的用户名密码不对
#define USER_LOGED 0X80000005     //登录时，提示该用户已经在线
#define USER_NOT_REGIST 0X80000006  //登录时，提示用户没有注册


2.数据库两张表，一张主要用于保存用户信息、一张用于记录聊天信息。
用户名、密码、在线状态、socket描述符
socket描述符 信息

sqlite3具体操作
```cpp
#include <stdio.h>
#include "sqlite3.h"
int main(int argc, char const *argv[])
{
	sqlite3*db;
	int ret = sqlite3_open("xixi.db",&db);
	if (ret !=SQLITE_OK)
	{
		perror("SQLITE_OK\n");
		return 0;
	}
	char table_name[50] = "";

	printf("请输入你要创建的表\n");
	scanf("%s",table_name);
	// 2.写一个创建表的sql语句.
	//再去定义一个数组用来保存我重新组的新字符串
	char cmd[100] = "";
	sprintf(cmd,"create table %s (id int ,name text);",table_name);//完成了一个组包的操作

	// 3.看自己是读操作还是写操作
	// 	如果是写操作就使用sqlite3_exec
	// 	如果是读操作就使用sqlite3_get_table
	// 4.调用就行了
	char *errmsg = NULL;
	sqlite3_exec(db,cmd,NULL,NULL,&errmsg);
	if (errmsg != NULL)//如果我们出现错误就会打印errmsg
	{
		printf("%s\n", errmsg);
	}
	int id = 0;
	char name[50] = "";
	printf("请输入你的id\n");
	scanf("%d",&id);
	printf("请输入你的name\n");
	scanf("%s",name);
	char cmd2[100] = "";
	sprintf(cmd2,"insert into %s values(%d,\'%s\');",table_name,id,name);//   \'就相当于引号
	sqlite3_exec(db,cmd2,NULL,NULL,&errmsg);
	if (errmsg != NULL)//如果我们出现错误就会打印errmsg
	{
		printf("%s\n", errmsg);
	}
	char cmd3[100] = "";
	sprintf(cmd3,"select name from %s where id = %d;",table_name,id);
	char  **table = NULL;//用来存放你数据库查到的结果
	int r,c;//r行数 c列数
	sqlite3_get_table(db, cmd3,&table,&r,&c,&errmsg);
	if (errmsg != NULL)//如果我们出现错误就会打印errmsg
	{
		printf("%s\n", errmsg);
	}

	printf("%s\n", table[1]);
	//由于你只有1列，最上方的列名是table[0]，因此你的name就是tabel[1]

	char cmd4[100] = "";
	sprintf(cmd4,"select * from %s; ",table_name);
	sqlite3_get_table(db, cmd4,&table,&r,&c,&errmsg);
	if (errmsg != NULL)//如果我们出现错误就会打印errmsg
	{
		printf("%s\n", errmsg);
	}
	int i,k;
	for (i = 0; i < r+1; ++i)//r+1是因为多出来一个列名一行
	{
		for (k = 0; k < c; ++k)
		{
			printf("%s", table[i*c+k]);
		}
		printf("\n");
	}
	printf("\n");
	sqlite3_close(db);
	return 0;
}
```
3.