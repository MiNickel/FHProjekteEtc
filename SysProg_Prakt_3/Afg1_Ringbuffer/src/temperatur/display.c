#include <stdio.h>
#include "ringbuffer/ringbuffer.h"
#include "ledanzeige/TM1637.h"

void display_status(const ring_buffer *cb) {

    TM1637_setup();
    float fill = 0;
    if (cb->size > 0)
        fill = cb->count / (float) cb->size * 100;

    PRINTF("Gefülter Speicher: %f\n", fill);
    TM1637_display_number(fill);
}
