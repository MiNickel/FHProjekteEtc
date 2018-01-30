/*!
 * \file main.cpp
 * \brief Main Methode fuer die Aussentemperatur
 */
#include "temperatur/calcTemp.h"
#include "temperatur/tempSensor.h"
extern "C" {
	#include "ringbuffer/ringbuffer.h"
	#include "ringbuffer/display.h"
	#include "ledanzeige/TM1637.h"
}
#include <unistd.h>
#include "wetter/xmlParser.h"
#include "wetter/weatherLoader.h"
#include "wetter/datenbank.h"
#include <string>
#include <iostream>

using namespace std;

#define LOOPCOUNT 3

/**
 * \fn void test_free(void *ptr)
 * \brief Methode zum freeeen von pointern
 */
void test_free(void *ptr) {
	free(ptr);
}

/**
 * \fn float calcAverage(ring_buffer *buffer)
 * \brief kalkuliert den Durchschnitt der Innentemperatur
 */

float calcAverage(ring_buffer *buffer) {
	int count = buffer->count; 
	float sum = 0;
	float *temp;
	while(buffer->count > 0) {
		temp = (float *)read_buffer(buffer);
		sum += *temp;
		free(temp);
	}
	return sum/(float)count;
}
/**
 * Main-Methode	
 * 
 */
int main() {
	
	WeatherLoader *weatherLoader = new WeatherLoader();
	XmlParser xmlParser = XmlParser();
	Database database = Database();
	
	TempSensor tempSensor = TempSensor(calculateTemperature);
	ring_buffer *buffer = init_buffer(10, test_free);
	int counter = 1;
			
	while(true) {
		float *temperature = (float *)malloc(sizeof(float));
		*temperature = tempSensor.getTemp();
		write_buffer(buffer, temperature);
		
		if(counter == LOOPCOUNT) {
			
			delete weatherLoader;	
			weatherLoader = new WeatherLoader();
			
			string result = weatherLoader->getWeather();
			xmlParser.parseString(result);
			string outsideTemp = xmlParser.getOutsideTemp();
			float outsideFloat = std::stof(outsideTemp, NULL);
			database.writeDatabase(outsideFloat, calcAverage(buffer));
			counter = 1;
		} else  {
			counter++;
		}
		
		display_status(buffer);
		sleep(2);
	}
	
	return 0;
}
