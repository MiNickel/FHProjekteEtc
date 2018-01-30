##
##Wetter tests
##

##
## Makros
##

CC = g++
CFLAGS = -c -lxml2 -Wall -pedantic $(INCLUDE)

OBJS =xmlParser.o xmlParser_test.o datenbank.o datenbank_test.o
INCLUDE = -I../../include -I/usr/include/libxml2
LIBS = -lsqlite3 -lxml2 -lgtest -lgmock -lgmock_main 

##
## Regeln
##
all: test
	./wetter_test

test:$(OBJS)
	$(CC) -pthread $(LIBS) -o wetter_test $(OBJS)

xmlParser_test.o: xmlParser_test.cpp
	$(CC) $(CFLAGS) xmlParser_test.cpp

xmlParser.o: ../../src/wetter/xmlParser.cpp
	$(CC) $(CFLAGS) ../../src/wetter/xmlParser.cpp

datenbank_test.o: datenbank_test.cpp
	$(CC) $(CFLAGS) datenbank_test.cpp

datenbank.o: ../../src/wetter/datenbank.cpp
	$(CC) $(CFLAGS) ../../src/wetter/datenbank.cpp

.Phony: clean
clean:
	rm -rf *.d *.o *.so *_test
