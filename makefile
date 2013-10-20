#makefile

CC = gcc -ansi -pedantic -Wall -Wextra -Werror -g

ttrekisteri: main.o sub.o 
	$(CC) -o ttrekisteri main.o sub.o
sub.o: sub.c sub.h
	$(CC) -c sub.c
main.o: main.c sub.h
	$(CC) -c main.c
