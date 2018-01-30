##
## Temperatur
##
## Author André, Malte, Tim
##
.PHONY: all install run clean test

##
## macrodefinitions
##

## pfade
BIN = ../../bin/temperatur
LIBDIR = ../../lib/ringbuffer

## variablen
CC = g++
CFLAGS = -c -Wall -pedantic $(INCLUDE)
OBJS = calcTemp.o tempSensor.o
INCLUDE = -I../../include
LDFLAGS = $(LDLIBS) -lringbuffer
LDLIBS = -L$(LIBDIR)

##
## rules
##
all: main.o $(OBJS)
	$(CC) -lwiringPi -Wl,-rpath=$(LIBDIR) -o main main.o $(OBJS) $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

calcTemp.o: calcTemp.cpp
	$(CC) $(CFLAGS) calcTemp.cpp

tempSensor.o: tempSensor.cpp
	$(CC) $(CFLAGS) tempSensor.cpp

install:
	mkdir -p $(BIN)
	cp *.o $(BIN)
	cp main $(BIN)

run:
	cd $(BIN) && ./main

clean:
	find -name "*.o" -delete
	find -name "main" -delete
