## Object Dateien die generiert werden sollen
OBJ = main_led.o segmentanzeige.o TM1637.o

## Dateipfade zu include und src
INCLUDE?=$(shell realpath "$(shell pwd)/../../include/")

## Compiler und flags
CC=gcc
CFLAGS=-ansi -pedantic -Wall -lwiringPi
CFLAGS+=-fPIC
CFLAGS+=-DNDEBUG
CFLAGS+=-I$(INCLUDE)

## Regel die für all .o Dateien die jeweilige .c und alle .h voraussetzt
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

## Kompiliert alle in OBJ gelisteten .c Dateien in .o
ledanzeige: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

## lib erstellen
.Phony: lib
lib: $(OBJ)
	gcc -shared -o libledanzeige.so $^ $(CFLAGS)

## Saubermachen
.Phony: clean
clean:
	rm -rf *.d *.o *.so ledanzeige
