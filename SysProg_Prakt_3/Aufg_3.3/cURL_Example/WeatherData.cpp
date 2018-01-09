#include "WeatherData.hpp"

using namespace std;

// konstruktor
WeatherData::WeatherData()
{
    m_easy_handle = NULL;
    m_ptr = NULL;
}

// copy constructor
WeatherData::WeatherData(const WeatherData &obj) {
   cout << "Copy constructor allocating m_ptr." << endl;
   m_ptr = new WeatherData();
   *m_ptr = *obj.m_ptr; // copy the value
}

// destructor
WeatherData::~WeatherData(void) {
    cout << "Freeing memory!" << endl;

    // Timeouts einstellen, Mehrere Threads verwenden für mehrere simultane Übertragungen!
    curl_easy_cleanup(m_easy_handle); // close handle
    m_easy_handle = NULL;

    if(m_ptr != NULL)
        delete m_ptr;
}

// zuständig für das Laden der Wetterdaten
void WeatherData::LoadWeatherData(void)
{
    m_easy_handle = curl_easy_init();  // create an "easy handle" to a	transfer (REUSE!)
  /*
CURLM	*multi_handle	=	curl_multi_init();
    //Adding	an	easy	handle	to	the	multi	handle	is	very	easy:
curl_multi_add_handle(	multi_handle,	easy_handle	);
    //Removing	one	is	just	as	easily	done:
curl_multi_remove_handle(	multi_handle,	easy_handle	);
-----------------------------------------------------------------------
multi_socket ...
  */

  if(m_easy_handle) {
      // Dann legen Sie verschiedene Optionen in diesem Handle fest,#
      //num die bevorstehende Übertragung zu steuern. In diesem Beispiel wird die URL festgelegt
                //res	=	curl_easy_setopt(easy_handle,	CURLOPT_URL,	"http://example.com/");
    //curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com/");    // set	URL	to	operate	on
    //
        curl_easy_setopt(m_easy_handle, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/forecast?id=2871039&APPID=77aeb67f561c2e612b99adf135c3b316&mode=xml");    // set	URL	to	operate	on
        /*
        Das Erstellen der einfachen Handle- und Einstellungsoptionen macht keine Übertragung möglich
         und macht in der Regel nicht viel mehr möglich, außer dass libcurl Ihren Wunsch speichert,
          später verwendet zu werden, wenn die Übertragung tatsächlich stattfindet.
        */

    /*
    ------------------------------------------------------
    Viele Operationen innerhalb von libcurl werden mit Callbacks gesteuert.
    Ein Callback ist ein Funktionszeiger für libcurl, den libcurl dann zu einem bestimmten Zeitpunkt aufruft,
     um eine bestimmte Aufgabe zu erledigen.
     ------------------------------------------------------
    */
        curl_easy_setopt(m_easy_handle, CURLOPT_WRITEFUNCTION, WriteCallback); // The	write callback: CURLOPT_WRITEFUNCTION
        // Der Benutzerzeiger, der an den Rückruf im Argument userdata übergeben wird, wird mit CURLOPT_WRITEDATA festgelegt:
        curl_easy_setopt(m_easy_handle, CURLOPT_WRITEDATA, &m_readBuffer);

        m_res = curl_easy_perform(m_easy_handle); // nur eine Übertragung gleichzeitig durchführen kann und dass es die gesamte Übertragung in einem einzigen Funktionsaufruf durchführt

        /*	Check	for	errors	*/
        if(m_res	!=	CURLE_OK)
            fprintf(stderr,	"curl_easy_perform()	failed:	%s\n", curl_easy_strerror(m_res));
    }
}

// print buffer with weather-data
void WeatherData::PrintBuffer(void)
{
    //std::cout << m_readBuffer << std::endl;
    cout << m_readBuffer << endl;
}

// liefertder buffer zurück
std::string WeatherData::GetBuffer(void)
{
    return m_readBuffer;
}
