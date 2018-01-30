/*!
 * \file display.h
 * \brief Definitionen für display.c
 */
 
/**
 * \fn void display_average(void);
 * Zeigt die durchschnittlichen Cps auf der LED anzeige
 */
void display_average(void);

/**
 * \fn void display_absolute(void);
 * Zeigt nacheinader für alle Termine der Liste die Nummer und die Cps(-1, wenn kein Student eingetragen ist)
 */
void display_absolute(void);
