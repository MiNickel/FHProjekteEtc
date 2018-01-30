#include "studiverwaltung/studiverwaltung.h" 
/*!
 * \file pruefungen.h
 * \brief Definitionen pruefungen.c
 */
 
/**
 * \var int NUM_EXAMS
 * Maximale Anzahl an Prüfungen
 */
#ifndef NUM_EXAMS
#define NUM_EXAMS 10
#endif

/**
 * \var float MAXIMUM_POINTS
 * Maximal erreichbare Cps
 */
#ifndef MAXIMUM_POINTS
#define MAXIMUM_POINTS 320.0f
#endif

/**
 * \fn int register_student(student *s, int nr);
 * \param s Student der eingetragen werden soll
 * \param nr Termin, für die der Student eingetragen werden soll
 * \return Termin an dem eingefügt wird, bei Fehler -1
 * Trägt den Studenten an dem Termin ein. Wenn dieser blegegt ist wird der nächst mögliche genommen. 
 */
int register_student(student *s, int nr);

/**
 * \fn int remove_student(student *s);
 * \param s Zu löschender Student
 * \return Position des gelöschten Student. -1 bei Fehler.
 * Löscht den Studenten.
 */
int remove_student(student *s);

/**
 * \fn float calculate_average(void); 
 * Berechnt die Durchschnittlichen Cps aller eingetragen Studenten.
 */
float calculate_average(void); 

/**
 * \fn int  contains (student *s);
 * \param s Student, der geprüft werden soll
 * \return Position des Studenten oder -1 wenn nicht enthalten
 */
int  contains (student *s);
