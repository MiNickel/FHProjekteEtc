##
## ledanzeige
##
## Author André, Malte, Tim
##
.PHONY: all install run clean debug test

##
## macrodefinitions
##

## pfade
BINLED = ../../bin/ledanzeige
TSTLED = ../../tests/ledanzeige
LIBDIR = ../../lib/ledanzeige

## variablen
CC = gcc
CFLAGS = -c -Wall -ansi -pedantic $(INCLUDE) -fpic -lwiringPi
OBJS = segmentanzeige.o TM1637.o 
INCLUDE = -I../../include
SRC = $(OBJS:%.o=%.c)
LDFLAGS = $(LDLIBS) -lledanzeige
LDLIBS = -L$(LIBDIR)
DYNLIB = libledanzeige.so

##
## rules
##
all: $(OBJS) main.o
	$(CC) -Wl,-rpath=$(LIBDIR) -lwiringPi -o main main.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

segmentanzeige.o: segmentanzeige.c
	$(CC) $(CFLAGS) segmentanzeige.c

TM1637.o: TM1637.c
	$(CC) $(CFLAGS) TM1637.c

all_lib: $(OBJS)
	$(CC) -lwiringPi -shared -o $(DYNLIB) $(OBJS)

install:
	mkdir -p $(BINLED)
	cp *.o $(BINLED)
	cp main $(BINLED)

install_lib:
	mkdir -p $(LIBDIR)
	cp libledanzeige.so $(LIBDIR)

run:
	cd $(BINLED) && ./main

test:
	cd $(TSTLED) && make

clean:
	find -name "*.o" -delete
	find -name "main" -delete
	find -name "*.so" -delete
