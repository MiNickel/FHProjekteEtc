#include "ledanzeige/segmentanzeige.h"
#include "ledanzeige/TM1637_intern.h"
#include "wiringPi.h"

void TM1637_write_byte(byte wr_data) {
    unsigned char i, s=1;
    
    for(i = 0; i < 8; i++) {
		digitalWrite(PIN_CLOCK, LOW);
		delayMicroseconds(DELAY_TIMER);
        if(wr_data & s) {
            digitalWrite(PIN_DATA, HIGH);

        } else {
            digitalWrite(PIN_DATA, LOW);
        }
		delayMicroseconds(DELAY_TIMER);
        digitalWrite(PIN_CLOCK, HIGH);
		delayMicroseconds(DELAY_TIMER);
        s= s << 1;
    }
    

    TM1637_ack();
}
