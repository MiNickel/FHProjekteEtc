#include <wiringPi.h>
#include "ledanzeige/segmentanzeige.h"
#include "ledanzeige/TM1637_intern.h"
#include "ledanzeige/TM1637.h"
#include <stdio.h>
#include <stdlib.h>
/*! \file main.c
 	\brief Die Main zum starten des Programms.
 */
 
 /**
  * \fn main()
  * Methode zum starten des Programms.
  */
int main() {
	int i;

	TM1637_setup();
	TM1637_brightness(BRIGHT);


	for(i=0; i<10; i++) {
		TM1637_display_number((float)i);
		delayMicroseconds(1000000);
	}
	
	TM1637_clear_display();
	return EXIT_SUCCESS;
}
