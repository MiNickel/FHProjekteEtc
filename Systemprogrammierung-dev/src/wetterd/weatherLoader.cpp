/*!
 * \file weatherLoader.h
 * \brief Der weatherLoader
 */
#include "wetter/weatherLoader.h"
#include "ringbuffer/ringbuffer.h"

WeatherLoader::WeatherLoader() {
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, f);
	curl_easy_setopt(curl, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?id=2871039&APPID=722920868a0a0266c859a174da690bc1&units=metric&mode=xml");
}		

WeatherLoader::WeatherLoader(const WeatherLoader &w):
	curl(w.curl){
		
}

WeatherLoader &WeatherLoader::operator=(const WeatherLoader &w){
	curl = w.curl;	
	return *this;
}

WeatherLoader::~WeatherLoader(){
	curl_easy_cleanup(curl);
}


std::string WeatherLoader::getWeather() {
	std::string buffer;
	curl_easy_setopt(curl,CURLOPT_WRITEDATA, &buffer);
	CURLcode res = curl_easy_perform(curl);
	if (res == CURLE_OK) {
		return buffer;
	}
	return "";
}

size_t WeatherLoader::f(char *data, size_t size, size_t nmemb, void *userdata) {
	std::string *buffer = (std::string *)userdata;
	buffer->append(data, size*nmemb);
	return size*nmemb;
}
