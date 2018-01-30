/*!
 * \file segmentanzeige.h
 * \brief Definitionen für die Segmentanzeige und ein Prototyp.
 */
#ifndef SEGMENTANZEIGE_H
#define SEGMENTANZEIGE_H

/**
 * \var unsigned char byte
 * Definition byte - 1 Byte Integer
 */

typedef unsigned char byte;

/**
 * \enum segment {SEG1, SEG2, SEG3, SEG4} 
 * Aufzählug segment
 */
 
typedef enum segment {SEG1, SEG2, SEG3, SEG4} segment;
 
/**
 * \enum dot {OFF, ON}
 * Aufzählung dot
 */
  
typedef enum dot {OFF, ON} dot;

/**
 * \enum brightness {DARK, MEDIUM, BRIGHT=7}
 * Aufzählung brightness
 */

typedef enum brightness {DARK, MEDIUM, BRIGHT=7} brightness;

/**
 * \fn void TM1637_write_byte(byte)
 * Prototyp der Funktion write_byte
 */
void TM1637_write_byte(byte);

#endif
