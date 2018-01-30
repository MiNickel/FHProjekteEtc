/*!
 * \file display.c
 * \brief Displayd den ringbuffer
 */
#include "ringbuffer/display.h"
#include "ringbuffer/ringbuffer.h"
#include "ledanzeige/TM1637.h"
#include <wiringPi.h>

void display_status(const ring_buffer *cb) {
	if (cb) {
		int count = cb->count;
		int size = cb->size;
		float relativeSize = (float) count/size * 100.0f;
		
		TM1637_setup();
		TM1637_brightness(BRIGHT);

		TM1637_display_number(relativeSize);
		delayMicroseconds(1000000);
	
		TM1637_clear_display();
	}
}
