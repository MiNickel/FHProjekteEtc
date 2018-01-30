/*!
 * \file display.c
 * \brief Implementierung der diplay_heap Methode
 */
#include "speicherverwaltung/speicherverwaltung.h"
#include "ledanzeige/TM1637.h"
#include <wiringPi.h>

int run_trough_the_heap(CountType type) {
	char *currentblock = mempool;
	int retVal = 0;
	while (((int) currentblock) < (MEM_POOL_SIZE + ((int) mempool))) {
		int blocklength = ((memblock *) currentblock)->size;
		if ((int)(((memblock *) currentblock)->next) == MAGIC_INT) {
			if (type == TSM_BYTE) {
				retVal += sizeof(memblock) + blocklength;
			} else {
				retVal++;
			}
		}
		currentblock += sizeof(memblock) + blocklength;
	}
	return retVal;
}

int count_free_blocks(void) {
	memblock * currentmem = freemem;
	int count = 0;
	while (currentmem) {
		count++;
		currentmem = currentmem->next;
	}
	return count;
}

int count_occupied_blocks(void) {
	return run_trough_the_heap(TSM_COUNT);
}

float calculate_heap_level() {
	return ((float) run_trough_the_heap(TSM_BYTE)) / MEM_POOL_SIZE * 100.0f;
}

void display_heap(void) {
	TM1637_setup();
	TM1637_brightness(BRIGHT);

	TM1637_display_number(count_free_blocks());
	delayMicroseconds(1000000);
	TM1637_display_number(count_occupied_blocks());
	delayMicroseconds(1000000);
	TM1637_display_number(calculate_heap_level());
	delayMicroseconds(1000000);
	
	TM1637_clear_display();
}
