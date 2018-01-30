/*!
 * \file datenbank.h
 * \brief Definitionen für die Datenbank
 */
#include <sqlite3.h>
#include <string>
using namespace std;
/**
 * \class Database
 * \brief Database definiert die Schnittstelle zur Datenbank
 *
 */
class Database{
	
public:
	/**
	 * \brief Standard Konstruktor
	 * 
	 */
	Database();
			
	/**
	 * \brief Copy Konstruktor
	 * 
	 */
	Database(const Database &w);
			
	/**
	 * \brief Zuweisungsoperator
	 * 
	 */
	Database &operator=(const Database &w);
			
	/**
	 * \brief Destruktor
	 * 
	 */
	~Database();
	
	/**
	 * \fn void writeDatabase(float aussentemperatur, float innentemperatur)
	 * \brief writeDatabase schreibt die Innen und Aussentemperatur in die Datenbank
	 * \param float aussentemperatur gibt die Aussentemperatur an
	 * \param float innentemperatur gibt die Innentemperatur an
	 * 
	 */
	void writeDatabase(const float &aussentemperatur, const float &innentemperatur);
	string readDatabase();
	static int result_callback(void*, int, char**, char**);
	
private:	
	static string result;
};
