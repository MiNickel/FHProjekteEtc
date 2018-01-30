#include <gtest/gtest.h>
#include "wetter/xmlParser.h"
#include <string>

using namespace std;

XmlParser parser = XmlParser();

/*
 * Testet ob parseString bei uebergabe von leerem String NULL zurueck gibt.
 */
TEST(xmlparser, test_parse_empty_string) {
	xmlDocPtr doc = parser.parseString("");
	ASSERT_EQ(NULL, (int)doc);
}

/*
 * Testet ob parseString bei uebergabe von falschem String NULL zurueck gibt.
 */
TEST(xmlparser, test_parse_wrong_string) {
	xmlDocPtr doc = parser.parseString("Dieser String sollte nicht klappen");
	ASSERT_EQ(NULL, (int)doc);
}

/*
 * Testet ob parseString bei uebergabe von invaliedem XML NULL zurueck gibt.
 */
TEST(xmlparser, test_parse_not_valid_xml) {
	xmlDocPtr doc = parser.parseString("<context>");
	ASSERT_EQ(NULL, (int)doc);
}

/*
 * Testet ob parseString bei uebergabe von XML mit sonstigem text NULL zurueck gibt.
 */
TEST(xmlparser, test_parse_not_valid_xml_secound) {
	xmlDocPtr doc = parser.parseString("<context><time /><context>Sollte failen");
	ASSERT_EQ(NULL, (int)doc);
}

/*
 * Testet ob parseString bei uebergabe von valiedem XML funktioniert
 */
TEST(xmlparser, test_parse_positive) {
	xmlDocPtr doc = parser.parseString("<context><time /></context>");
	ASSERT_EQ(parser.getDoc(), doc);
}

/*
 * Testet ob getOutsideTemp bei einem falschem XML-Dokument einen leeren String zuruek gibt.
 */
TEST(xmlparser, test_get_temp_wrong_xml_document) {
	parser.parseString("<context><time /></context>");
	ASSERT_EQ("", parser.getOutsideTemp());
}

/*
 * Testet ob getOutsideTemp bei einem NULL-Dokument einen leeren String zuruek gibt.
 */
TEST(xmlparser, test_get_temp_null_document) {
	parser.parseString("");
	ASSERT_EQ("", parser.getOutsideTemp());
}

/*
 * Testet ob getOutsideTemp bei einem richtigen XML-Dokument einen richtigen String zuruek gibt.
 */
TEST(xmlparser, test_get_temp_positiv) {
	parser.parseString("<current><temperature value=\"3\" /></current>");
	ASSERT_EQ("3", parser.getOutsideTemp());
}

/*
 * Testet ob getOutsideTemp bei einem falschem XML-Dokument einen leeren String zuruek gibt.
 */
TEST(xmlparser, test_get_temp_without_value) {
	parser.parseString("<current><temperature /></current>");
	ASSERT_EQ("", parser.getOutsideTemp());
}
