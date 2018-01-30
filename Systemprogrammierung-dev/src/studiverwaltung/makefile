##
## studiverwaltung
##
## Author André, Malte, Tim
##
.PHONY: all install run clean test

##
## macrodefinitions
##

## pfade
BINSTUDI = ../../bin/studiverwaltung
TSTSTUDI = ../../tests/studiverwaltung

## variablen
CC = gcc
CFLAGS = -c -Wall -ansi -pedantic $(INCLUDE)
OBJS = studiverwaltung.o spfree.o
INCLUDE = -I../../include

##
## rules
##
all: main.o $(OBJS)
	$(CC) -o main main.o $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

studiverwaltung.o: studiverwaltung.c
	$(CC) $(CFLAGS) studiverwaltung.c

spfree.o: spfree.c
	$(CC) $(CFLAGS) spfree.c

install:
	mkdir -p $(BINSTUDI)
	cp *.o $(BINSTUDI)
	cp main $(BINSTUDI)

run:
	cd $(BINSTUDI) && ./main

test:
	cd $(TSTSTUDI) && make

clean:
	find -name "*.o" -delete
	find -name "main" -delete
