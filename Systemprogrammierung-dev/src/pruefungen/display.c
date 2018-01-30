#include "pruefungen/display.h"
#include "ledanzeige/TM1637.h"
#include "pruefungen/pruefungen.h"
#include <wiringPi.h>
/*!
 * \file display.c
 * \brief Darstellen der Ergebniss aus pruefungen auf der Segmentanzeige.
 */

void display_average(void) {
	float average = calculate_average();
	
	TM1637_setup();
	TM1637_brightness(BRIGHT);
	
	TM1637_display_number(average);
	delayMicroseconds(1000000);
	TM1637_clear_display();
}

void display_absolute(void) {
	int i;
	extern student *exams[];
	
	TM1637_setup();
	TM1637_brightness(BRIGHT);
	
	for(i = 0; i < NUM_EXAMS; i++) {
		TM1637_display_number((float) i);
		delayMicroseconds(1000000);
		
		if(exams[i]){
			TM1637_display_number((float) exams[i]->cps);
			delayMicroseconds(1000000);
		} else {
			TM1637_display_number((float) -1);
			delayMicroseconds(1000000);
		}
	}
	TM1637_clear_display();
}
