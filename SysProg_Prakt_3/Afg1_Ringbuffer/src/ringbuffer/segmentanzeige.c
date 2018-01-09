#include <wiringPi.h>
#include "ledanzeige/segmentanzeige.h"
#include "ledanzeige/TM1637_intern.h"
#include <stdio.h>
/*! \file segmentanzeige.c
 	\brief Die Segmentanzeige verwaltet das Schreiben der einzelnen Bytes auf die Segmentanzeige. 
 */
 
/**
 * \fn setHigh()
 * schaltet eine LED an
 */
void setHigh() {
	digitalWrite(PIN_CLOCK, LOW);
	delayMicroseconds(DELAY_TIMER);
	digitalWrite(PIN_DATA, HIGH);
	delayMicroseconds(DELAY_TIMER);
	digitalWrite(PIN_CLOCK, HIGH);
	delayMicroseconds(DELAY_TIMER);
}

/**
 * \fn setLow()
 * schaltet eine LED aus
 */
void setLow() {
	digitalWrite(PIN_CLOCK, LOW);
	delayMicroseconds(DELAY_TIMER);
	digitalWrite(PIN_DATA, LOW);
	delayMicroseconds(DELAY_TIMER);
	digitalWrite(PIN_CLOCK, HIGH);
	delayMicroseconds(DELAY_TIMER);
}

/**
 * \fn TM1637_write_byte(byte wr_data)
 * \param wr_data byte, der dargestellt werden soll.
 * write_byte sendet die Daten eines Bytes an eine LED-Anzeige
 */
void TM1637_write_byte(byte wr_data) {
	int i;
	for(i=0 ; i<8 ; i++) {
		if((wr_data % 2) == 1){
			setHigh();
		}else{
			setLow();
		}
		
		wr_data >>= 1;
	}
	TM1637_ack();
}
