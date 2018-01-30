/*!
 * \file datenbank.h
 * \brief Die Schnittstelle zur Datenbank
 */
#include "wetterd/datenbank.h"

Database::Database() {
	
}
	
Database::Database(const Database &w) {
	
}
	
Database &Database::operator=(const Database &w) {
	return *this;
}
	
Database::~Database() {
	
}
string Database::result = "";

int Database::result_callback(void* unused, int count, char** data, char** columns) {
	result.append("{\"x\":\"");
	result.append(data[0]);
	result.append("\",\"y\":");
	result.append(data[1]);
	result.append(",\"location\":\"outdoor\"},");
	result.append("{\"x\":\"");
	result.append(data[0]);
	result.append("\",\"y\":");
	result.append(data[2]);
	result.append(",\"location\":\"indoor\"},");
	return 0;
}
/*
result.append("{ \"x\": \"");
	result.append(data[0]);
	result.append("\", \"y\": ");
	result.append(data[1]);
	result.append(", \"location\": \"outdoor\" },");
	result.append("{ \"x\": \"");
	result.append(data[0]);
	result.append("\", \"y\": ");
	result.append(data[2]);
	result.append(", \"location\": \"indoor\" },");
	return 0;
*/

string Database::readDatabase() {
	result = "[";
	string zwstring;
	sqlite3 *db;
	int ERROR = sqlite3_open("../../datenbanken/temperatur.db",&db);
	if (!ERROR) {
		const char *befehl = "SELECT Zeit, Aussentemperatur, Innentemperatur FROM temperatur; ";
		sqlite3_exec(db, befehl, result_callback, NULL, NULL);
		sqlite3_close(db);
	}
	zwstring = result.substr(0, result.size()-1);
	zwstring.append("]");
	return zwstring;
}

void Database::writeDatabase(const float &aussentemperatur, const float &innentemperatur) {
	if (innentemperatur >= -273.15 && aussentemperatur >= -273.15) {
		sqlite3 *db;
		int ERROR = sqlite3_open("../../datenbanken/temperatur.db",&db);
		if (!ERROR) {
			sqlite3_stmt *stmt;
			std::string befehl = "INSERT INTO temperatur (Aussentemperatur,Innentemperatur) VALUES (";
			befehl.append(std::to_string(aussentemperatur));
			befehl.append(",");
			befehl.append(std::to_string(innentemperatur));
			befehl.append(");");
			sqlite3_prepare(db, befehl.c_str(), befehl.length(), &stmt, NULL);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			sqlite3_close(db);
		}
	}
}	
