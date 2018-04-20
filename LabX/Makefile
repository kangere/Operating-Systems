CC = gcc

all: shell

shell: shell.o
		$(CC) -o shell shell.o

shell.o: shell.c
		$(CC) -c shell.c

clean:
		rm shell *.o
