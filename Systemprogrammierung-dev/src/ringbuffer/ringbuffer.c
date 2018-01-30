/*!
 * \file ringbuffer.c
 * \brief Der Ringbuffer in dem Dinge gespeichert werden
 */
#include "ringbuffer/ringbuffer.h"

ring_buffer *init_buffer(const size_t n, void (*f)(void *p)) {
	if (!n || !f) {
		return NULL;
	}
	ring_buffer *buffer = malloc(sizeof(ring_buffer));
	if (buffer) {
		buffer-> elems = (void **) malloc(n * sizeof(void *));
		if (buffer->elems) {
			buffer-> size = n;
			buffer-> count = 0;
			buffer-> head = 0;
			buffer-> free_callback = f;
			return buffer;
		}
	}
	return 0;
}

void *read_buffer(ring_buffer *cb) {
	if (!cb || cb->count == 0) {
		return NULL;
	}
	void *ret = cb->elems[cb->head];
	cb->head++;
	if (cb->head == cb->size) {cb->head = 0;}
	cb->count--;
	return ret;
}

void write_buffer(ring_buffer *cb, void *data) {
	if (cb && data) {
		size_t pos = (cb->head + cb->count) % cb->size;
		if (pos == cb->head && cb->count != 0) {
			cb->free_callback(cb->elems[pos]);
			cb->head = (cb->head+1) % cb->size;
		}else {
			cb->count++;
		}
		cb->elems[pos] = data;
	}
}

int free_buffer(ring_buffer *cb) {
	if (!cb) {
		return -1;
	}
	int size = cb->size;
	int counter = 0;
	while (counter < cb->count) {
		cb->free_callback(cb->elems[(counter+cb->head)%size]);
		counter++;
	}
	free(cb->elems);
	free(cb);
	return counter;
}

int count_elements(const ring_buffer *cb) {
	if (cb) {
		return cb->count;
	}
	return -1;
}
