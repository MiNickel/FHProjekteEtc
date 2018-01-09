#include <stdio.h>
#include "ringbuffer/ringbuffer.h"
#include "ringbuffer/display.h"
#include "ledanzeige/TM1637.h"



void freeElem(void *p) ;

int main() {
    void (*ptr)(void *p);
    ptr = freeElem;
    ring_buffer *buffer = init_buffer(8, ptr);

    PRINTF("Buffer created, size: %d\n", buffer->size);

    write_buffer(buffer, 8);
    write_buffer(buffer, 7);
    write_buffer(buffer, 6);
    write_buffer(buffer, 5);
    write_buffer(buffer, 4);
    write_buffer(buffer, 3);
    write_buffer(buffer, 2);
    write_buffer(buffer, 1);

    printBuffer(buffer);

    write_buffer(buffer, 0);

    printBuffer(buffer);

    PRINTF("Reading: %d\n", read_buffer(buffer));
    PRINTF("Reading: %d\n", read_buffer(buffer));

    printBuffer(buffer);

	display_status(buffer);

    free_buffer(buffer);

    return 0;
}

void freeElem(void *p) {
    PRINTF("  Freeing: %d\n", p);
}

void printBuffer(ring_buffer *buffer) {

    PRINTF("Printing Buffer\n");
    int cnt = 0;
    while(cnt<buffer->count)
    {
        int idx = (buffer->head + cnt) % buffer->size;
        PRINTF("  %d (%d): %d\n", cnt, idx, buffer->elems[idx]);
        cnt++;
    }

}
