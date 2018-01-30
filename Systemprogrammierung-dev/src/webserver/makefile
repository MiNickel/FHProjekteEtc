##
## Webserver
##
## Author André, Malte, Tim
##
.PHONY: all install run clean test

##
## macrodefinitions
##

## pfade
BIN = ../../bin/webserver
LIBDIR = ../../lib/ringbuffer

## variablen
CC = g++
CFLAGS = --std=c++14 -c -Wall -pedantic $(INCLUDE)
OBJS = server.o
INCLUDE = -I../../include
LDFLAGS = $(LDLIBS) ##-lringbuffer
LDLIBS = -L$(LIBDIR)

##
## rules
##
all: main.o $(OBJS)
	$(CC) -Wl,-rpath=$(LIBDIR) -o fbtHttpd main.o $(OBJS) $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp


install:
	mkdir -p $(BIN)
	cp *.o $(BIN)
	cp fbtHttpd $(BIN)

run:
	cd $(BIN) && ./fbtHttpd ../../server 8999

clean:
	find -name "*.o" -delete
	find -name "fbtHttpd" -delete
