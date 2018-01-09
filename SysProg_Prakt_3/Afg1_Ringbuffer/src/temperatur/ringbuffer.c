#include <stdlib.h>
#include "ringbuffer/ringbuffer.h"

ring_buffer *init_buffer(const size_t n, void (*f)(void *p)) {
    if (!n || !f)
        return NULL;
    ring_buffer *buffer = malloc(sizeof(ring_buffer));
    buffer->elems = malloc(sizeof(void *) * n);
    buffer->size = n;
    buffer->count = 0;
    buffer->head = 0;
    buffer->free_callback = f;
    return buffer;
}

void *read_buffer(ring_buffer *cb) {
    if (!cb || (cb->count == 0))
        return NULL;
    void *ret = cb->elems[cb->head];
    cb->head = (cb->head + 1) % cb->size;
    cb->count--;
    return ret;
}

void write_buffer(ring_buffer *cb, void *data) {
    if (!cb || !data)
        return;

    if (cb->count == cb->size) {
        cb->free_callback(cb->elems[cb->head]); //Alten Datensatz freigeben
        cb->elems[cb->head] = data; //Neuen Datensatz eintragen
        cb->head = (cb->head + 1) % cb->size; //Header inkrementieren
    } else {
        size_t idx = (cb->head + cb->count) % cb->size; //Index mit Wraparound festlegen
        cb->elems[idx] = data; //Datensatz eintragen
        cb->count++; //Zähler inkrementieren
    }
}

int free_buffer(ring_buffer *cb) {
    if (!cb)
        return -1;

    for (size_t i = 0; i < cb->count; i++) {
        size_t idx = (cb->head + i) % cb->size;
        void *val = cb->elems[idx];
        cb->free_callback(val);
    }
    int ret = (int) cb->count;
    free(cb->elems);
    free(cb);
    return ret;
}

int count_elements(const ring_buffer *cb) {
    if (cb)
        return (int) cb->count;
    return -1;
}

