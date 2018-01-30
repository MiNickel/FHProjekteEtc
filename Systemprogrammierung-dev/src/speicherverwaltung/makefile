##
## speicherverwaltung
##
## Author André, Malte, Tim
##
.PHONY: all

##
## macrodefinitions
##

## pfade
BINSPEICHER = ../../bin/speicherverwaltung
TSTSPEICHER = ../../tests/speicherverwaltung
LIBDIR = ../../lib/ledanzeige

## variablen
CC = gcc
CFLAGS = -c -std=c11 -pedantic -Wall $(INCLUDE) -lwiringPi -DMALLOCSPLIT
OBJS = speicherverwaltung.o display.o
INCLUDE = -I../../include
LDFLAGS = $(LDLIBS) -lledanzeige
LDLIBS = -L$(LIBDIR)

##
## rules
##
all: $(OBJS) main.o
	$(CC) -Wl,-rpath=$(LIBDIR) -DMALLOCSPLIT -lwiringPi -g -o main main.o $(OBJS) $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

speicherverwaltung.o: speicherverwaltung.c
	$(CC) $(CFLAGS) speicherverwaltung.c

display.o: display.c
	$(CC) $(CFLAGS) display.c

install:
	mkdir -p $(BINSPEICHER)
	cp *.o $(BINSPEICHER)
	cp main $(BINSPEICHER)

run:
	cd $(BINSPEICHER) && ./main

test:
	cd $(TSTSPEICHER) && make

clean:
	find -name "*.o" -delete
	find -name "main" -delete
