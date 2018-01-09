
CFLAGS = -std=c11 -pedantic -Wall -lwiringPi -DMALLOCSPLIT
INC = -I../../include

run: main
	./main

main: calcTemp.o main.o tempSensor.o ringbuffer.o display.o TM1637.o segmentanzeige.o
	gcc $(CFLAGS) -o main calcTemp.o main.o tempSensor.o ringbuffer.o display.o TM1637.o segmentanzeige.o

calcTemp.o: calcTemp.cpp
	gcc $(INC) -c calcTemp.cpp

main.o: main.cpp
	gcc $(INC) -c main.cpp

tempSensor.o: tempSensor.cpp
	gcc $(INC) -c tempSensor.cpp

ringbuffer.o: ringbuffer.c
	gcc $(INC) -c ringbuffer.c

display.o: display.c
	gcc $(INC) -c display.c

TM1637.o: TM1637.c
	gcc $(INC) -c TM1637.c

segmentanzeige.o: segmentanzeige.c
	gcc $(INC) -c segmentanzeige.c


clean:
	rm -rf main *.~
