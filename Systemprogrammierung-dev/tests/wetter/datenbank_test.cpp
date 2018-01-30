#include <gtest/gtest.h>
#include "wetter/datenbank.h"
#include <string>
#include <iostream>

Database database = Database();

/*
 * Testet ob richtige Werte ueber writeDatabase in die Datenbank geschrieben werden koennen
 */
TEST(datenbank, test_datenbank) {
	float fmin = -273.15;
	database.writeDatabase(fmin, fmin);
	sqlite3 *db;
	int ERROR = sqlite3_open("../../datenbanken/temperatur.db",&db);
	if (!ERROR) {
		sqlite3_stmt *stmt;
		std::string befehl = "SELECT innentemperatur, aussentemperatur FROM temperatur ";
		befehl.append("WHERE innentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(" AND aussentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(";");
		
		sqlite3_prepare(db, befehl.c_str(), befehl.length(), &stmt, NULL);
		sqlite3_step(stmt);
		double in = sqlite3_column_double(stmt,0);
		double out = sqlite3_column_double(stmt,1);
		sqlite3_finalize(stmt);
		
		befehl = "DELETE FROM temperatur ";
		befehl.append("WHERE innentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(" AND aussentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(";");
		
		sqlite3_prepare(db, befehl.c_str(), befehl.length(), &stmt, NULL);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		
		ASSERT_EQ(fmin, (float)in);
		ASSERT_EQ(fmin, (float)out);
	}
}

/*
 * Testet ob zwei falsche Werte ueber writeDatabase nicht in die Datenbank geschrieben werden koennen
 */
TEST(datenbank, test_datenbank_to_low_temp) {
	float fmin = -273.16;
	database.writeDatabase(fmin, fmin);
	sqlite3 *db;
	int ERROR = sqlite3_open("../../datenbanken/temperatur.db",&db);
	if (!ERROR) {
		sqlite3_stmt *stmt;
		std::string befehl = "SELECT innentemperatur, aussentemperatur FROM temperatur ";
		befehl.append("WHERE innentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(" AND aussentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(";");
		
		sqlite3_prepare(db, befehl.c_str(), befehl.length(), &stmt, NULL);
		sqlite3_step(stmt);
		double in = sqlite3_column_double(stmt,0);
		double out = sqlite3_column_double(stmt,1);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		
		ASSERT_EQ(0, (float)in);
		ASSERT_EQ(0, (float)out);
	}
}

/*
 * Testet ob ein falscher Wert bei innentemperatur ueber writeDatabase nicht in die Datenbank geschrieben werden koennen
 */
TEST(datenbank, test_datenbank_to_low_innen_temp) {
	float fToMin = -273.16;
	float fmin = -273.15;
	database.writeDatabase(fToMin, fmin);
	sqlite3 *db;
	int ERROR = sqlite3_open("../../datenbanken/temperatur.db",&db);
	if (!ERROR) {
		sqlite3_stmt *stmt;
		std::string befehl = "SELECT innentemperatur, aussentemperatur FROM temperatur ";
		befehl.append("WHERE innentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(" AND aussentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(";");
		
		sqlite3_prepare(db, befehl.c_str(), befehl.length(), &stmt, NULL);
		sqlite3_step(stmt);
		double in = sqlite3_column_double(stmt,0);
		double out = sqlite3_column_double(stmt,1);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		
		ASSERT_EQ(0, (float)in);
		ASSERT_EQ(0, (float)out);
	}
}

/*
 * Testet ob ein falscher Wert bei aussentemperatur ueber writeDatabase nicht in die Datenbank geschrieben werden koennen
 */
TEST(datenbank, test_datenbank_to_low_aussen_temp) {
	float fmin = -273.15;
	float fToMin = -273.16;
	database.writeDatabase(fmin, fToMin);
	sqlite3 *db;
	int ERROR = sqlite3_open("../../datenbanken/temperatur.db",&db);
	if (!ERROR) {
		sqlite3_stmt *stmt;
		std::string befehl = "SELECT innentemperatur, aussentemperatur FROM temperatur ";
		befehl.append("WHERE innentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(" AND aussentemperatur = ");
		befehl.append(std::to_string(fmin));
		befehl.append(";");
		
		sqlite3_prepare(db, befehl.c_str(), befehl.length(), &stmt, NULL);
		sqlite3_step(stmt);
		double in = sqlite3_column_double(stmt,0);
		double out = sqlite3_column_double(stmt,1);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		
		ASSERT_EQ(0, (float)in);
		ASSERT_EQ(0, (float)out);
	}
}
