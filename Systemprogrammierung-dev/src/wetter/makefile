##
## Wetter
##
## Author André, Malte, Tim
##
.PHONY: all install run clean test

##
## macrodefinitions
##

## pfade
BIN = ../../bin/wetter
TSTSPEICHER = ../../tests/wetter
LIBDIR = ../../lib/ringbuffer

## variablen
CC = g++
CFLAGS = -c -Wall -pedantic $(INCLUDE)
OBJS = weatherLoader.o xmlParser.o tempSensor.o calcTemp.o datenbank.o
INCLUDE = -I../../include -I/usr/include/libxml2
LDFLAGS = $(LDLIBS) -lringbuffer
LDLIBS = -L$(LIBDIR)

##
## rules
##
all: $(OBJS) main.o
	$(CC) -lwiringPi -lcurl -lxml2 -lsqlite3 -Wl,-rpath=$(LIBDIR) -o main main.o $(OBJS) $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

weatherLoader.o: weatherLoader.cpp
	$(CC) $(CFLAGS) -lcurl weatherLoader.cpp

xmlParser.o: xmlParser.cpp
	$(CC) $(CFLAGS) xmlParser.cpp

tempSensor.o: ../temperatur/tempSensor.cpp
	$(CC) $(CFLAGS) ../temperatur/tempSensor.cpp

calcTemp.o: ../temperatur/calcTemp.cpp
	$(CC) $(CFLAGS) ../temperatur/calcTemp.cpp

datenbank.o: datenbank.cpp
	$(CC) $(CFLAGS) datenbank.cpp

install:
	mkdir -p $(BIN)
	cp *.o $(BIN)
	cp main $(BIN)

run:
	cd $(BIN) && ./main

test:
	cd $(TSTSPEICHER) && make

clean:
	find -name "*.o" -delete
	find -name "main" -delete
