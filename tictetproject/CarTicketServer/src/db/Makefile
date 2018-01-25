all : db.o sqlite3.o sqliteinterface.o
	mv *.o ../../obj
db.o : db.c
	gcc -o $@ -c $^ -I../include 
sqliteinterface.o : sqliteinterface.c
	gcc -o $@ -c $^
sqlite3.o : sqlite3.c
	gcc -o $@ -c $^ -lpthread -ldl
