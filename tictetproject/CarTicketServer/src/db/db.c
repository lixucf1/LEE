#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "db.h"
#include "sqliteinterface.h"

#define FILEPATH_MAX (80)

int InitDb()//创建数据库/打开数据库
{
    /*db name start*/
    char *pPath = NULL;
    char dbName[] = "/mysqlite";
    pPath = (char *) malloc (FILEPATH_MAX + 10);
    if (NULL == pPath)
    {
        return DB_ERR;
    }
    memset(pPath, 0, FILEPATH_MAX + 10);
    getcwd(pPath, FILEPATH_MAX);
    printf("%s %d\n",pPath,strlen(pPath));
    memcpy(pPath + strlen(pPath), dbName, strlen(dbName));
    printf("%s %d\n",pPath,strlen(pPath));
    /*db name end*/
    //init db
    if (DB_ERROR_OK != InitConnection())
    {
        printf("invoke InitConnection function error!\n");
        return DB_ERR;
    }
    //open or create db
    if (DB_ERROR_OK != OpenConnection(pPath))
    {
        printf("invoke OpenConnection function error!\n");
        return DB_ERR;
    }
    return DB_OK;
}

int CreateTable()//创建车票信息表 乘客信息表
{
	char TablePassenger[] = "create table passenger (id integer primary key autoincrement,"
							" pass_name text not null,"
							" id_number text not null, "
							" pass_addr text not null )";
							//"foreign key(pass_addr) references station(addr_name))";
	if (DB_ERROR_OK != ExecSQL(TablePassenger))
    	{
		perror("create passenger table error\n");
        	return DB_ERR;
    	}
 	char sqlCreateTableCar[] = "create table station (id integer primary key autoincrement,"
                                                    "addr_name text not null,"
                                                    " plate_numer text not null,"
                                                    "depart_time text not null,"
                                                    "price text not null)";
    	if (DB_ERROR_OK != ExecSQL(sqlCreateTableCar))
    	{
		perror("create station table error\n");
        	return DB_ERR;
    	}
	return DB_OK;
}
int InsertTable()//初始化插入信息
{
    	char sqlInsert[] = "insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(1, '泾阳', '陕D-JY666', '06:30', '12元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(2, '三原', '陕D-SY666', '06:40', '15元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(3, '阎良', '陕D-YL666', '07:20', '21元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(4, '户县', '陕D-HS666', '06:00', '12元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(5, '大荔', '陕D-DL666', '08:30', '25元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(6, '洛川', '陕D-LC666', '08:50', '30元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(7, '富平', '陕D-FP666', '09:00', '30元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(8, '延安', '陕D-YA666', '09:30', '45元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(9, '周至', '陕D-ZZ666', '10:00', '20元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(10, '蒲城', '陕D-PC666', '10:30', '26元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(11, '高陵', '陕D-GL666', '11:40', '35元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(12, '临潼', '陕D-LT666', '12:30', '27元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(13, '渭南', '陕D-WL666', '13:30', '28元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(14, '铜川', '陕D-TC666', '14:30', '40元');" \
			"insert into station (id, addr_name, plate_numer, depart_time, price )" \
			"values(15, '汉中', '陕D-HZ666', '17:30', '45元');" \
			"insert into passenger(id, pass_name, id_number, pass_addr)" \
			"values(1, '张三', '610426199603054663', '阎良');";
	if (DB_ERROR_OK != ExecSQL(sqlInsert))
    	{
        	printf("create table sql error\n");
		return DB_ERR;
    	}
    	return DB_OK;
}

int ShowTicket()//显示车票表信息
{
	char sqlSelect[200] = "select * from station";
    	char** ppTable = NULL;
    	char* pErrMsg = NULL;
    	int iRow = 0;
    	int iColumn = 0;
    	if (DB_ERROR_OK != GetTable(sqlSelect, &ppTable, &iRow, &iColumn))
    	{
        	printf("select sql error\n");
		return DB_ERR;
    	}
	printf("编号 目的地  车牌号     发车时间   价格\n");
    	if (NULL != ppTable)
    	{
        	int i = 1;
        	for (; i <=iRow; i++)
        	{
            		int j = 0;
            		for (; j < iColumn; j++)
            		{
                		if (NULL != ppTable[i * iColumn + j])
                		{
                    			printf("%s    ",ppTable[i * iColumn + j]);
                		}
                
            		}
            		printf("\n");
        	}
	}
    	ReleaseTableResult(ppTable);	
	return DB_OK;
}

int addNewMes()//添加新的车票信息
{
	char addr[100]="";
	char plateNUm[100]="";
	char departTime[100]="";
	char price[100]="";
	printf("请输入目的地:");
	scanf("%s",addr);
	printf("请输入车牌号:");
	scanf("%s",plateNUm);
	printf("请输入发车时间:");
	scanf("%s",departTime);
	printf("请输入车票价格:");
	scanf("%s",price);
	char buf[1000] = "insert into station(addr_name,plate_numer,depart_time,price) values ('";
	strcat(buf,addr);
	strcat(buf,"','");
	strcat(buf,plateNUm);
	strcat(buf,"','");
	strcat(buf,departTime);
	strcat(buf,"','");
	strcat(buf,price);
	strcat(buf,"元')");
	if (DB_ERROR_OK != ExecSQL(buf))
    	{
        	printf("add ticket error\n");
		return DB_ERR;
    	}
	return DB_OK;
}

int FindSqlTicket(int socketID,char *addr,char *buffer[])//通过客户端发送的信息，对车票表进行查找 并返回查找到的车票信息给客户端
{
	char sqlSelect[200] = "select * from station where addr_name ='";	
	strcat(sqlSelect,addr);
	strcat(sqlSelect,"'");
    	char** ppTable = NULL;
    	char* pErrMsg = NULL;
    	int iRow = 0;
    	int iColumn = 0;
    	if (DB_ERROR_OK != GetTable(sqlSelect, &ppTable, &iRow, &iColumn))
    	{
        	printf("select sql error\n");
		return DB_ERR;
    	}
	char buf[200] = "";
	//printf("编号 目的地  车牌号     发车时间   价格\n");
    	if (NULL != ppTable)
    	{
        	int i = 1;
        	for (; i <=iRow; i++)
        	{
            		int j = 0;
            		for (; j < iColumn; j++)
            		{
                		if (NULL != ppTable[i * iColumn + j])
                		{
					strcat(buf,ppTable[i * iColumn + j]);
					strcat(buf, "     ");
                		}
                
            		}
            		//printf("\n");
        	}
	}
    	ReleaseTableResult(ppTable);
	send(socketID, buf, strlen(buf), 0);
	return DB_OK;	
}

int InsertPass(int socketID,char *addr,char *buffer[])//通过客户端购买车票返回发送的乘客信息对乘客信息表进行插入信息
{
	char buf[1000] = "insert into passenger(pass_name,id_number,pass_addr) values ('";
	strcat(buf,buffer[2]);
	strcat(buf,"','");
	strcat(buf,buffer[3]);
	strcat(buf,"','");
	strcat(buf,addr);
	strcat(buf,"')");
	if (DB_ERROR_OK != ExecSQL(buf))
    	{
        	printf("add ticket error\n");
		return DB_ERR;
    	}
	char message[100] = " 购买成功!";
	send(socketID, message, strlen(message), 0);
	return DB_OK;		
}

int ShowPass()//显示当前的乘客信息
{
	char sqlSelect[200] = "select * from passenger";
    	char** ppTable = NULL;
    	char* pErrMsg = NULL;
    	int iRow = 0;
    	int iColumn = 0;
    	if (DB_ERROR_OK != GetTable(sqlSelect, &ppTable, &iRow, &iColumn))
    	{
        	printf("select sql error\n");
		return DB_ERR;
    	}
	//printf("编号 姓名  身份证号  乘票号\n");
    	if (NULL != ppTable)
    	{
        	int i = 1;
        	for (; i <=iRow; i++)
        	{
            		int j = 0;
            		for (; j < iColumn; j++)
            		{
                		if (NULL != ppTable[i * iColumn + j])
                		{
                    			printf("%s    ",ppTable[i * iColumn + j]);
                		}
                
            		}
            		printf("\n");
        	}
	}
    	ReleaseTableResult(ppTable);	
	return DB_OK;	
}

int ServerFind(char *addr)//服务器查找车票信息
{
	char sqlSelect[200] = "select * from station where addr_name ='";	
	strcat(sqlSelect,addr);
	strcat(sqlSelect,"'");
    	char** ppTable = NULL;
    	char* pErrMsg = NULL;
    	int iRow = 0;
    	int iColumn = 0;
    	if (DB_ERROR_OK != GetTable(sqlSelect, &ppTable, &iRow, &iColumn))
    	{
        	printf("select sql error\n");
		return DB_ERR;
    	}
	//printf("编号 目的地  车牌号     发车时间   价格\n");
    	if (NULL != ppTable)
    	{
        	int i = 1;
        	for (; i <=iRow; i++)
        	{
            		int j = 0;
            		for (; j < iColumn; j++)
            		{
                		if (NULL != ppTable[i * iColumn + j])
                		{
					printf("%s    ",ppTable[i * iColumn + j]);
                		}
                
            		}
            		printf("\n");
        	}
	}
    	ReleaseTableResult(ppTable);	
	return DB_OK;
}
