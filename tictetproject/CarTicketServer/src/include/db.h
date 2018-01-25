#ifndef _DB_H_
#define _DB_H_

enum DB_ERR_TYPE
{
	DB_ERR = -1,
	DB_OK
};

int InitDb();
int InsertTable();
int CreateTable();
int ShowTicket();
int addNewMes();
int FindSqlTicket(int socketID,char *addr,char *buffer[]);
int InsertPass(int socketID,char *addr,char *buffer[]);
int ShowPass();
int ServerFind(char *addr);
#endif //_DB_H_
