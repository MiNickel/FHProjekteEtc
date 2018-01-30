/*!
 * \file datenbank.h
 * \brief Die Schnittstelle zur Datenbank
 */
#include "wetter/datenbank.h"

Database::Database() {
	
}
	
Database::Database(const Database &w) {
	
}
	
Database &Database::operator=(const Database &w) {
	return *this;
}
	
Database::~Database() {
	
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
