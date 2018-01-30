##
## pruefungen
##
## Author André, Malte, Tim
##
.PHONY: all install run clean test

##
## macrodefinition
##

## pfade
BINPF = ../../bin/pruefungen
TSTPF = ../../tests/pruefungen
STUDI = ../studiverwaltung/studiverwaltung.c
SPFREE = ../studiverwaltung/spfree.c
LIBDIR = ../../lib/ledanzeige

## variablen
CC = gcc
CFLAGS = -c -Wall -ansi -pedantic -lWiringPi $(INCLUDE)
OBJS = studiverwaltung.o pruefungen.o display.o spfree.o
INCLUDE = -I../../include
LDFLAGS = $(LDLIBS) -lledanzeige
LDLIBS = -L$(LIBDIR)

##
## rules
##
all: main.o $(OBJS)
	$(CC) -Wl,-rpath=$(LIBDIR) -lwiringPi -o main main.o $(OBJS) $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

studiverwaltung.o: $(STUDI)
	$(CC) $(CFLAGS) $(STUDI)

pruefungen.o: pruefungen.c
	$(CC) $(CFLAGS) pruefungen.c

display.o: display.c
	$(CC) $(CFLAGS) display.c

spfree.o: $(SPFREE)
	$(CC) $(CFLAGS) $(SPFREE)

install:
	mkdir -p $(BINPF)
	cp *.o $(BINPF)
	cp main $(BINPF)

run:
	cd $(BINPF) && ./main

test:
	cd $(TSTPF) && make

clean:
	find -name "*.o" -delete
	find -name "main" -delete
