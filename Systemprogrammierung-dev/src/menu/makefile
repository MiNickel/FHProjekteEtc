##
## WebserverMenu
##
## Author André, Malte, Tim
##
.PHONY: all install run clean test

##
## macrodefinitions
##

## pfade
BIN = ../../bin/menu
LIBDIR = ../../lib/ringbuffer

## variablen
CC = g++
CFLAGS = --std=c++14 -c -Wall -pedantic $(INCLUDE)
OBJS = webserverMenu.o
INCLUDE = -I../../include
LDFLAGS = -lncurses -lmenu
LDLIBS = -L$(LIBDIR)

##
## rules
##
all: main.o $(OBJS)
	$(CC) $(LDFLAGS) -o main main.o $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

webserverMenu.o: webserverMenu.cpp
	$(CC) $(CFLAGS) webserverMenu.cpp


install:
	mkdir -p $(BIN)
	cp *.o $(BIN)
	cp main $(BIN)

run:
	cd $(BIN) && ./main

clean:
	find -name "*.o" -delete
	find -name "main" -delete
