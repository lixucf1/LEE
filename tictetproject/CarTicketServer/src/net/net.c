

#include "common.h"
#include "net.h"
#include "db.h"
#define BUF_SIZE 100

struct Command//结构体
{
	char m_strName[20];
	FuncType *m_proc;//函数指针
};

struct Command CommandTable[] = 
{
	{"find", FindSqlTicket},
    	{"buy", InsertPass},
};//赋值

int  getorder(char *buf,char *argv[])//分割字符串
{
    if((NULL == buf)&&(NULL == argv))//传参判断
    {
        return NET_ERR;
    }
    char *p;
    p = strtok(buf," ");//strtok 函数第一步必须填入buf  
    int i = 0;
    while(NULL != p)//p == null 分割完成
    {
        argv[i] = p;//将第一个分割的字符给argv第一个
        p = strtok(NULL," ");//再次调用strtok 填NULL 表示直到分割完后返回NULL
        argv[i++];
    }
    return NET_OK;

}

void AcceptClient(int socketID)//连接客户端
{
	int maxFd = 0;
	fd_set readFds;
	fd_set tmpFds;
	int newID = 0;
	int i = 0;
	int ret = 0;
	int addrLength = 0;
	struct sockaddr_in addr;
	char buf[SIZE] = {'\0'};
	//struct timeval tv;
	
	addrLength = sizeof(addr);
	
	if (NET_ERR == socketID)
	{
		return ;
	}
	
	//select
	maxFd = socketID;
	FD_ZERO(&readFds);
	FD_SET(socketID, &readFds);
	tmpFds = readFds;	
	
	while(1)
	{
		readFds = tmpFds;
		//tv.tv_sec = 4;
	//	tv.tv_usec = 0;
		
		ret = select(maxFd + 1, &readFds, NULL, NULL, NULL);
		if (ret < 0)
		{
			perror("select error");
			break;
		}
		else if (0 == ret)
		{
			continue;
		}
		
		for (i = 0; i <= maxFd; i++)
		{
			if (socketID == i)
			{
				if (FD_ISSET(socketID, &readFds))
				{
					newID = accept(socketID, (struct sockaddr *)&addr, &addrLength);
					if (newID < 0)
					{
						perror("accept error");
						break;
					}
					FD_SET(newID, &tmpFds);
					if (maxFd < newID)
					{
						maxFd = newID;
					}
					printf("客户端 %d 已连接！\r\n", ntohs(addr.sin_port));
				}
			}
			else if (FD_ISSET(i, &readFds))
			{
				memset(buf, 0, SIZE);
				ret = recv(i, buf, SIZE - 1, 0);
				if (ret < 0)
				{
					perror("recv error");
					close(i);
					FD_CLR(i, &tmpFds);					
				}
				else if (0 == ret)
				{
					printf("客户端%d已退出!\r\n",i);					
					close(i);
					FD_CLR(i, &tmpFds);
				}
				else 
				{
					int argc = 0;
					char *argv[20] = {0};
					ret = getorder(buf, argv);//分割字符
				
					if(NET_OK == ret)
					{
						int k = 0;
						int iCount = sizeof(CommandTable) / sizeof(struct Command);//获取数组大小
						for(; k < iCount;k++)
						{
							if(0 == (strcmp(argv[0], CommandTable[k].m_strName)))
							{
								CommandTable[k].m_proc(i, argv[1],argv);//掉用对应函数
								break;
							}
						}
					}
				}
			}//else if (FD_ISSET(i))
		}//for (i = 0; i <= maxFd)
	}//while(1)
	
	for (i = 0; i <= maxFd; i++)
	{
		close(i);
	}
	
	
}

int initSocket()
{
	int socketID = 0;
	int addrLength = 0;
	struct sockaddr_in addr;
	socketID = socket(AF_INET, SOCK_STREAM , 0);
	if (socketID < 0)
	{
		perror("socket error");
		return NET_ERR;
	}
	printf("socket ok\r\n");
	addrLength = sizeof(addr);
	memset(&addr, 0, addrLength);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (0 > bind(socketID, (struct sockaddr *)&addr, addrLength))
	{
		perror("bind error");
		close(socketID);
		return NET_ERR;
	}
	printf("bind ok\r\n");
	listen(socketID, 5);
	return socketID;
}
