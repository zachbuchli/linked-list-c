# Makefile for stringlist project
CC = gcc

CFLAGS  = -g -Wall

# the build 
default: all

all: stringlist

stringlist: main.o list.o
	$(CC) $(CFLAG) main.o list.o -o stringlist 

main.o: main.c list.c
	$(CC) $(CFLAG) -c main.c

list.o: list.c
	$(CC) $(CFLAG) -c list.c

# removes object files
clean: 
	$(RM) stringlist *.o *~

# make command to generate docs
docs:
	doxygen ./Doxyfile

# links dependancies 
main.o: main.c list.c list.h
list.o: list.c list.h

