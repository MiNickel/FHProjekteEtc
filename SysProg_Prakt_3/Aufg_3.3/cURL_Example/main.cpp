#include "WeatherData.hpp"
#include <fstream>  // Textausgabe in eine Datei

#include "xml/pugixml.hpp"
#include <iostream>
#include <sstream>

using namespace std;

int main(void)
{
    std::string  ringBuffer;
    WeatherData *data = new WeatherData();
    data->LoadWeatherData();
    //data->PrintBuffer();
    ringBuffer = data->GetBuffer();
    std::cout << ringBuffer << std::endl;

    // XML in die Datei "weather_minden.xml" schreiben
    fstream file;  // Für die Dateioperationen werden Objekte der Klasse fstream verwendet.
    file.open("resource/weather_minden.xml", ios::out);
    file << ringBuffer << endl;
    file.close();
    //End in eine Datei schreiben

    // xml-Dateien parsen
    pugi::xml_document doc;
    std::string timeTo;

    if (!doc.load_file("resource/weather_minden.xml"))
        return -1;

    pugi::xml_node wdata = doc.child("weatherdata");
    std::cout << std::endl;
    std::cout << wdata.name() << std::endl;

   for (pugi::xml_node set = wdata.first_child(); set; set = set.next_sibling())
    {
        //Now print all elements and attributes of current "time to"
        for (pugi::xml_node child1 = set.first_child(); child1; child1 = child1.next_sibling())
        {
            std::string attrName = child1.name();

            if( !attrName.compare("time"))
            {
                std::cout << child1.name() << std::endl;     // get element name
                               // iterate through all attributes
                for (pugi::xml_attribute attr = child1.first_attribute(); attr; attr = attr.next_attribute())
                {
                    std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
                }
                std::cout << std::endl;

                //Now print all elements and attributes of current "time"
                for (pugi::xml_node child2 = child1.first_child(); child2; child2 = child2.next_sibling())
                {

                    std::cout << child2.name() << std::endl;     // get element name
                    // iterate through all attributes
                    for (pugi::xml_attribute attr = child2.first_attribute(); attr; attr = attr.next_attribute())
                    {
                        std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
                    }
                    std::cout << std::endl;
                }
            }
        }
    }
    std::cout << std::endl;

  return 0;
}
