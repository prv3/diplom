CC=gcc
CFLAGS=-c -Wall

all: diplom

diplom: diplom.c
	$(CC) diplom.c -o diplom

clean:
	rm -rf *tmp diplom
