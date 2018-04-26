CC=gcc
# warnings all and debugging
CFLAGS=-c -Wall -g
CURRENT_DIR := $(mem basename `pwd`)
THIS_FILE := $(lastword $(MAKEFILE_LIST))

all: final

final: cachewizard.o main.o
	$(CC) cachewizard.o main.o -o main

cachewizard.o: cachewizard.c cachewizard.h
	$(CC) $(CFLAGS) cachewizard.c

main.o:	main.c cachewizard.h
	$(CC) $(CFLAGS) main.c

clean:
	/bin/rm -f main *.o *~

run:
	./main