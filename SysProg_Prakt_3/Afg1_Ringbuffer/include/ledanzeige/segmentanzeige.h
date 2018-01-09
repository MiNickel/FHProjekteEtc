
#ifndef  SEGMENT_H
#define  SEGMENT_H
/*
Deklaration der Vorgabedateitypen 
*/

/**
 * einfache Implementation eines bytes
 */
typedef unsigned char byte;

/**
 * ein enum das die 4 Segmente der LED Anzeige repräsentiert
 */
typedef enum Segment  {SEG1, SEG2, SEG3, SEG4 }segment;

/**
 * ein enum mit an und aus Stati für den Dezimalpunkt der LED Anzeige
 */
typedef enum Dot {OFF,ON}dot;

/**
 * ein enum das verschiebene Helligkeitswerte der LED Anzeige repräsentiert
 */
typedef enum Brightness{DARK,MEDIUM,BRIGHT=7}brightness;

#endif
