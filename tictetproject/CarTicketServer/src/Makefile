all: main.o
	make -C net
	make -C db
	make -C functio
	mv *.o ../obj
main.o : main.c
	gcc -o $@ -c $^

