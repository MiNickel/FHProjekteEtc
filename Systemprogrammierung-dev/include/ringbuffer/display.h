/*!
 * \file display.h
 * \brief Definitionen für den display
 */
 
#include "ringbuffer/ringbuffer.h"

/**
 * \fn void display_status(const ring_buffer *cb) gibt den Fuellstand des Buffers aus
 * \param const ring_buffer *cb ist der auszugebende Buffer(der Fuellstand nicht der Inhalt)
 * 
 */
void display_status(const ring_buffer *cb);
