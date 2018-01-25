#ifndef _COMMON_H_
#define _COMMON_H_



#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

typedef int FuncType(int socketID, char *addr,char *buffer[]);
#endif //_C0MMON_H_
