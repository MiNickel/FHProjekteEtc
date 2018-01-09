#include "ledanzeige/TM1637.h"

int main(void){
	
	int i;
	TM1637_setup();


	for(i=0;i<999;i++){
		TM1637_display_number(i);
	}
	
	
	return 0;
}

