/*!
 * \file ringbuffer.h
 * \brief Definitionen für den ringbuffer
 */
 
 #include <stdlib.h>
 
 #ifndef RINGBUFFER_H
 #define RINGBUFFER_H
 /**
 * \struct ring_buffer
 * \var size Groesse des ringbuffers
 * \var count aktuelle Anzahl Elemente im ringbuffer
 * \var head zeigt auf das älteste Element der Liste(Anfang)
 *  
 */
typedef struct ring_buffer {
	size_t size, count, head;
	void **elems;
	void (*free_callback)(void *p);
} ring_buffer;

/**
 * \fn ring_buffer *init_buffer(const size_t n, void (*f)(void *p)) initialisiert den buffer
 * \param size_t n legt die Groesse des Arrays fest
 * \param void (*f)(void *p) ist die Callback-Funktion, die augerfufen wird, wenn Speicher freigegeben werden soll
 * 
 */
ring_buffer *init_buffer(const size_t n, void (*f)(void *p));

/**
 * \fn void *read_buffer(ring_buffer *cb) liest das aelteste Objekt aus dem buffer aus
 * \param ring_buffer *cb ist der auszulesende Buffer
 * 
 */
void *read_buffer(ring_buffer *cb);

/**
 * \fn void write_buffer(ring_buffer *cb, void *data) schreibt ein neues Element in den Buffer
 * \param ring_buffer *cb ist der zu beschreibende Buffer
 * \param void *data ist der zu schreibende Inhalt
 * 
 * Ist der Puffer voll, wird der das aelteste entfernt
 * 
 */
void write_buffer(ring_buffer *cb, void *data);

/**
 * \fn int free_buffer(ring_buffer *cb) gibt den kompletten Buffer frei
 * \param ring_buffer *cb ist der freizugebende Buffer
 * 
 */
int free_buffer(ring_buffer *cb);

/**
 * \fn int count_elements(const ring_buffer *cb) zählt die derzeitigen Elemente im buffer
 * \param const ring_buffer *cb ist der buffer, in dem die Elemente gezählt werden sollen
 * 
 */
int count_elements(const ring_buffer *cb);

#endif
