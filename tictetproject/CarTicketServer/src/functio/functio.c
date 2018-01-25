/*************************************************************************
	> File Name: functio.c
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 06:42:20 PM PST
 ************************************************************************/
#include "../include/functio.h"
#include "../include/common.h"
#include "../include/db.h"
#include "../include/net.h"

int welcome()//服务器欢迎界面
{
	int i  = 0;
	int socketID ;
	printf("^===========欢迎使用咸阳汽车南站售票软件============^\n");
	printf("**************************************************\n");
	printf("**************************************************\n");
	printf("********************1.启动服务器******************\n");
	printf("********************2.数据 管 理******************\n");
	printf("********************3.退出 软 件******************\n");
	printf("**************************************************\n");
	printf("**************************************************\n");
	printf("请输入:");
	while(i < 1 || i > 3)
	{
		scanf("%d",&i);
		switch (i){
			case 1: socketID = initSocket();
				if (NET_ERR == socketID)
				{
					return NET_ERR;
				}
				printf("^====================等待客户端连接==================^\n");
				AcceptClient(socketID);	
				break;
			case 2:dataAdmin();break;
			case 3:break;
			default:printf("输入错误,请重新输入:");break;
			}
	}
	return NET_OK;
}

void dataAdmin()//数据管理
{
	int i  = 0;
	printf("^===========欢迎使用咸阳汽车南站售票软件============^\n");
	printf("**************************************************\n");
	printf("**************************************************\n");
	printf("********************1.初始化数据库*****************\n");
	printf("********************2.添加车票*********************\n");
	printf("********************3.查找车票*********************\n");
	printf("********************4.查看乘客信息******************\n");
	printf("********************5.返 回************************\n");
	printf("**************************************************\n");
	printf("**************************************************\n");	
	printf("请输入:");
	while(i < 1 || i > 5)
	{
		scanf("%d",&i);
		switch (i){
			case 1:initData();break;
			case 2:addTicket();break;
			case 3:FindTicket();break;
			case 4:FindPass();break;
			case 5:welcome();break;
			default:printf("输入错误,请重新输入:");break;
			}
	}
}

void initData()//初始化界面
{
	int i = 0;
	printf("**************************************************\n");
	printf("********************1.启动数据库*****************\n");
	printf("********************2.初始化表*********************\n");
	printf("********************3.初始化表信息*****************\n");
	printf("********************4.返  回**********************\n");
	printf("**************************************************\n");
	printf("请输入:");
	while(i < 1 || i > 3)
	{
		scanf("%d",&i);
		switch (i){
			case 1:CreateDb();break;
			case 2:CreateDataTable();break;
			case 3:InsertTableData();break;
			case 4:dataAdmin();break;
			default:printf("输入错误,请重新输入:");break;
			}
	}	
}
int CreateDb()//创建数据库/打开数据库
{
	if (DB_OK != InitDb())
	{
		return DB_ERR;
	}
	printf("初始化数据库完成!\n");
	initData();
	return NET_OK;
}
int CreateDataTable()//创建表
{
	if (DB_OK != CreateTable())
	{
		return DB_ERR;
	}
	printf("初始化表完成!\n");
	initData();
	return NET_OK;	
}
int InsertTableData()//添加表信息
{
	if (DB_OK != InsertTable())
	{
		return DB_ERR;
	}
	printf("初始化表信息完成!\n");
	initData();
	return NET_OK;	
}


int addTicket()//添加车票界面
{
	int i = 0;
	printf("**************************************************\n");
	printf("******************1.查看当前车票信息***************\n");
	printf("******************2.增加新的车票信息***************\n");
	printf("******************3.    返  回     ***************\n");
	printf("**************************************************\n");
	printf("请输入:");
	while(i < 1 || i > 2)
	{
		scanf("%d",&i);
		switch (i){
			case 1:LookTicket();break;
			case 2:addNewTicket();break;
			case 3:dataAdmin();break;
			default:printf("输入错误,请重新输入:");break;
			}
	}
	return NET_OK;	
}

int LookTicket()//查看当前车票信息
{
	if (DB_OK != ShowTicket())
	{
		return DB_ERR;
	}
	addTicket();
	return DB_OK;	
}

int addNewTicket()//添加新的车票信息
{
	if (DB_OK !=addNewMes())
	{
		return DB_ERR;
	}
	addTicket();
	return DB_OK;	
}

int FindTicket()//查找车票
{
	char addr[200] = "";
	printf("请输入要查询车票的目的地:");
	scanf("%s",addr);
	if (DB_OK != ServerFind(addr))
	{
		//return DB_ERR;
	}
	dataAdmin();
	return DB_OK;	
}

int FindPass()//查看乘客信息
{
	
	if (DB_OK !=ShowPass())
	{
		return DB_ERR;
	}
	dataAdmin();
	return DB_OK;
}
