##
## ringbuffer
##
## Author André, Malte, Tim
##
.PHONY: all

##
## macrodefinitions
##

## pfade
BINSPEICHER = ../../bin/ringbuffer
TSTSPEICHER = ../../tests/ringbuffer
LIBDIR = ../../lib/ledanzeige
LIBRINGDIR = ../../lib/ringbuffer

## variablen
CC = gcc
CFLAGS = -c -std=c11 -pedantic -Wall $(INCLUDE) -fpic -lwiringPi
OBJS = ringbuffer.o display.o
INCLUDE = -I../../include
LDFLAGS = $(LDLIBS) -lledanzeige
LDRINGFLAGS = -L$(LIBRINGDIR) -lringbuffer
LDLIBS = -L$(LIBDIR)
DYNLIB = libringbuffer.so

##
## rules
##
all: $(OBJS) main.o
	$(CC) -lwiringPi -Wl,-rpath=$(LIBRINGDIR) -o main main.o $(LDRINGFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c
 
ringbuffer.o: ringbuffer.c
	$(CC) $(CFLAGS) ringbuffer.c

display.o: display.c
	$(CC) $(CFLAGS) display.c

all_lib: $(OBJS)
	$(CC) -lwiringPi -Wl,-rpath=$(LIBDIR) -shared -o $(DYNLIB) $(OBJS) $(LDFLAGS)

install:
	mkdir -p $(BINSPEICHER)
	cp *.o $(BINSPEICHER)
	cp main $(BINSPEICHER)

install_lib:
	mkdir -p $(LIBRINGDIR)
	cp $(DYNLIB) $(LIBRINGDIR)

run:
	cd $(BINSPEICHER) && ./main

test:
	cd $(TSTSPEICHER) && make

clean:
	find -name "*.o" -delete
	find -name "main" -delete
	find -name "*.so" -delete
