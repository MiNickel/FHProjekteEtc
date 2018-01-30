/*!
 * \file xmlParser.cpp
 * \brief Klasse zum parsen der XML
 */
#include "wetter/xmlParser.h"

XmlParser::XmlParser() {
	doc = NULL;
}

XmlParser::~XmlParser(){
	xmlFreeDoc(doc);
}

XmlParser::XmlParser(const XmlParser &x){
	doc = x.doc;
}
		
XmlParser &XmlParser::operator=(const XmlParser &x){
	doc = x.doc;
	return *this;
}

xmlDocPtr XmlParser::getDoc() {
	return doc;
}
		
xmlDocPtr XmlParser::parseString(const string &text) {
	if (doc != NULL) {
		xmlFreeDoc(doc);
	}
	doc = xmlReadMemory(text.c_str(), text.size(), 0, 0, 0);
	return doc;
}

string XmlParser::getOutsideTemp() {
	if (doc == NULL) {
		return "";
	}
	
	xmlNodePtr cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		return "";
	}
	
	xmlChar *temp = NULL;
	cur = cur->xmlChildrenNode;
	while(cur != NULL) {
		if (!xmlStrcmp(cur->name, (const xmlChar *)"temperature")) {
			temp = xmlGetProp(cur, (xmlChar *)"value");
		}
		cur = cur->next;
	}
	if(temp == NULL) {
		if(cur != NULL) {
			xmlFree(cur);
		}
		return "";
	}
	string retString((char *)temp);
	xmlFree(temp);
	return retString;
}
