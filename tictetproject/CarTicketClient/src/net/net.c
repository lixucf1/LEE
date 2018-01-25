/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Thu 18 Jan 2018 12:52:10 AM PST
 ************************************************************************/

#include "common.h"
#include "net.h"

int initSocket()//创建SOCKET 连接服务器
{
    	int socketID = 0;
    	int ret = 0;
    	int addrLength = 0;
    	struct sockaddr_in serverAddr;
    	addrLength = sizeof(serverAddr);

    	//socket
    	socketID = socket(AF_INET, SOCK_STREAM, 0);
    	if(socketID < 0)
   	{
        	perror("socket error");
        	return NET_ERR;
    	}
    	printf("socket ok\n");

    	//设置连接的服务器
    	memset(&serverAddr, 0, addrLength);
    	serverAddr.sin_family = AF_INET;
    	serverAddr.sin_port = htons(PORT);
    	serverAddr.sin_addr.s_addr = inet_addr(IP);
	ret = connect(socketID, (struct sockaddr *)&serverAddr,addrLength);
    	if(ret < 0)
    	{
        	perror("connect error");
        	close(socketID);
		return NET_ERR;
   	}
	return socketID;	
}

void AcceptServer(int socketID,char *buf)//向服务器发送消息并且接受消息
{

	char buffer[100]= "";
        int ret = 0;
	send(socketID, buf, strlen(buf), 0);
        memset(buffer, 0, 100);
        ret = recv(socketID, buffer,99, 0);
        printf("%s\n",buffer);
  
}
