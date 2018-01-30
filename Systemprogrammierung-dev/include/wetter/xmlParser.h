/*!
 * \file xmlParser.h
 * \brief Definitionen für den xmlParser.
 */
#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

/**
 * \class XmlParser
 * \brief XmlParser sucht sich die Außentemperatur aus dem xml-file heraus
 */
class XmlParser {
	
	public:
				
		/**
		 * \brief Default Konstruktor
		 * 
		 */
		XmlParser();
							
		/**
		 * \brief Destruktor
		 * 
		 */
		~XmlParser();
						
		/**
		 * \brief Copy-Constructor
		 * 
		 */
		XmlParser(const XmlParser &x);
						
		/**
		 * \brief Zuweisungsoperator
		 * 
		 */
		XmlParser &operator=(const XmlParser &x);
		
		/**
		 * \fn xmlDocPtr getDoc()
		 * \brief getter fuer den doc
		 */
		xmlDocPtr getDoc();
		
		/**
		 * \fn xmlDocPtr parseString(string weather)
		 * \brief parseString wandelt den übergebenen String in ein doc um
		 * \param string weather ist das xml-file als String
		 * \return xmlDocPtr mit dem xml als Inhalt
		 */
		xmlDocPtr parseString(const string &weather);				
		
		/**
		 * \fn string getOutsideTemp()
		 * \brief getOutsideTemp sucht die Aussentemperatur heraus und gibt sie zurueck
		 * \return string mit der aussentemperatur
		 */
		string getOutsideTemp();
		
	private:
					
		/**
		 * \var xmlDocPtr doc ist ein xml-document
		 * 
		 */
		xmlDocPtr doc;
};
