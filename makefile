CC=gcc

all: server.c client.c
	nasm -f elf64 assem.asm
	$(CC) server.c assem.o -Wall -lpthread -o server
	$(CC) client.c -Wall -lpthread -o client
