/*!
 * \file main.cpp
 * \brief Main Methode fuer die Innentemperatur
 */
#include "temperatur/calcTemp.h"
#include "temperatur/tempSensor.h"
extern "C" {
	#include "ringbuffer/ringbuffer.h"
	#include "ringbuffer/display.h"
}
#include <unistd.h>

/**
 * \fn void test_free(void *ptr)
 * \brief Methode zum freeeen von pointern
 */
void test_free(void *ptr) {
	free(ptr);
}

/**
 * Main-Methode
 * 
 */
int main() {
	TempSensor tempSensor = TempSensor(calculateTemperature);
	ring_buffer *buffer = init_buffer(10, test_free);
	
	while(true) {
		float *temperature = (float *)malloc(sizeof(float));
		*temperature = tempSensor.getTemp();
		write_buffer(buffer, temperature);
		
		display_status(buffer);
		sleep(2);
	}
}
