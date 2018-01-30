/*!
 * \file weatherLoader.h
 * \brief Definitionen für den weatherLoader.
 */
#include <curl/curl.h>
#include <string>
#include "ringbuffer/ringbuffer.h"
#include <iostream>

				
/**
 * \class WeatherLoader
 * \brief WeatherLoader holt Daten aus dem Internet, um sie dann zum Verarbeiten weiterzugeben
 * 
 */
class WeatherLoader {
	private:		
		/**
		 * \var Curl *curl 
		 * \brief Objekt zum Benutzen der Internetseite
		 * 
		 */
		CURL *curl;		
		
		/**
		 * \fn static size_t f(char *data, size_t size, size_t nmemb, void *userdata)
		 * \brief f ist eine Callback Funktion, die Daten aus data in userdata uebertraegt
		 * \param char *data sind die Daten
		 * \param size_t size ist die Groesse eines Buchstabens
		 * \param size_t nmemb ist die Groesse der Daten
		 * \param void *userdata ist der Ort, wo die Daten reingeschrieben werden
		 * 
		 */	
		static size_t f(char *data, size_t size, size_t nmemb, void *userdata);
		
		
	public:
		/**
		 * \brief Standard Konstruktor
		 * 
		 */
		WeatherLoader();
				
		/**
		 * \brief Copy Konstruktor
		 * 
		 */
		WeatherLoader(const WeatherLoader &w);
				
		/**
		 * \brief Zuweisungsoperator
		 * 
		 */
		WeatherLoader &operator=(const WeatherLoader &w);
				
		/**
		 * \brief Destruktor
		 * 
		 */
		~WeatherLoader();
				
		/**
		 * \fn std::string getWeather() 
		 * \brief holt die Daten aus dem Internet und gibt sie als String zurueck
		 * \return std::string mit den XMLDaten
		 */
		std::string getWeather();
};
