/*!
 * \file calcTemp.cpp
 * \brief kalkuliert die Temperatur
 */
 #include "temperatur/calcTemp.h"

float calculateTemperature(int raw) {
	return ((float)raw*3.3/1024-0.5)*100.0;
}
