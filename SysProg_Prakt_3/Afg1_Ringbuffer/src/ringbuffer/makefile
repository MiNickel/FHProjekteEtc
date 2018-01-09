
CFLAGS = -std=c11 -pedantic -Wall -lwiringPi -DMALLOCSPLIT
INC = -I../../include

run: main
	./main

main: main_buffer.o ringbuffer.o display.o TM1637.o segmentanzeige.o
	gcc $(CFLAGS) -o main main_buffer.o ringbuffer.o display.o TM1637.o segmentanzeige.o

main_buffer.o: main_buffer.c
	gcc $(INC) -c main_buffer.c

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
