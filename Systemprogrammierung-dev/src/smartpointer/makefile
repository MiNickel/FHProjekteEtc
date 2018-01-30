##
## Smartpointer
##
## Author André, Malte, Tim
##
.PHONY: all install run clean test

##
## macrodefinition
##

## pfade
BINSP = ../../bin/smartpointer
TSTSP = ../../tests/smartpointer

## variablen
CC = g++
CFLAGS = --std=c++14 -c -Wall -pedantic $(INCLUDE)
INCLUDE = -I../../include

##
## rules
##
all: RefCounter.cpp
	$(CC) $(CFLAGS) RefCounter.cpp

install:
	mkdir -p $(BINSP)
	cp *.o $(BINSP)
	##cp main $(BINSP)

run:
	##cd $(BINSP) && ./main

test:
	cd $(TSTSP) && make

clean:
	find -name "*.o" -delete
	##find -name "main" -delete
