//WeatherData.hpp
#include <iostream>
#include <string>
#include </curl/curl.h>

class WeatherData
{
private:
  CURL          *m_easy_handle;
  CURLcode      m_res;
  std::string   m_readBuffer;

  WeatherData   *m_ptr;
private:
 // callback-Function, f�r das f�llen von Daten
//the write_callback function must match this	prototype: Wenn dieser Callback nicht gesetzt ist, verwendet libcurl standardm��ig 'fwrite'.
// 1. ptr_contents zeigt auf die gelieferten Daten
// 2.Gr��e der Daten auf die ptr_contents zeigt
// 3.nmemb Anzahl von member
// 4. ptr_userdata: cahr Buffer
static size_t WriteCallback( char       *ptr_contents,
                             size_t     size,
                             size_t     nmemb,
                             void       *ptr_userdata)
{
    ((std::string*)ptr_userdata)->append(ptr_contents, size * nmemb);
    return size * nmemb;
}

public:
    // simple constructor
    WeatherData();
    // copy constructor
    WeatherData(const WeatherData &obj);
    // destructor
    ~WeatherData(void);


    // zust�ndig f�r das Laden der Wetterdaten
    void LoadWeatherData(void);
    // druckt bufferd data auf der Konsole!
    void PrintBuffer(void);
    // liefertder buffer zur�ck
    std::string GetBuffer(void);
};
