/*!
 * \file main.c
 * \brief Main Methode fuer den ringbuffer
 * 
 */
#include "ringbuffer/ringbuffer.h"
#include "ringbuffer/display.h"

/**
 * \fn void test_free(void *ptr)
 * \brief Beispiel einer free Methode
 * 
 */
void test_free(void *ptr) {
	free(ptr);
}

int main() {
	ring_buffer *buffer = init_buffer(10, test_free);
	
	int *num = (int *)malloc(sizeof(int));
	int *num1 = (int *)malloc(sizeof(int));
	double *num2 = (double *)malloc(sizeof(double));
	double *num3 = (double *)malloc(sizeof(double));
	
	if (buffer && num && num1 && num2 && num3) {
		write_buffer(buffer, num);
		write_buffer(buffer, num1);
		write_buffer(buffer, num2);
		write_buffer(buffer, num3);
		
		display_status(buffer);
		
		read_buffer(buffer);
		read_buffer(buffer);
			
		display_status(buffer);
		
		free_buffer(buffer);
	}
}
