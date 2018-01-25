#ifndef _NET_H_
#define _NET_H_

#define IP "127.0.0.1"
#define PORT 10086
#define SIZE 200


enum NET_ERR_TYPE
{
	NET_ERR = -1,
	NET_OK
};

int initSocket();
void AcceptClient(int socketID);

#endif //_NET_H_
