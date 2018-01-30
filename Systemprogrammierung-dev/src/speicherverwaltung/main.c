#include "speicherverwaltung/display.h"
#include "speicherverwaltung/speicherverwaltung.h"
#include "ledanzeige/TM1637.h"
#include <stdlib.h>
#include <stdio.h>

/*!
 * \file main.c
 * \brief Klassen mit main-Methode zum Testen des Programms
 */

/**
 * \fn main
 * Main-Methode zum Testen der einzelnen Funktionen des 
 * Speicherverwaltungs-Programm
 */
int main() {
	
	cm_malloc(sizeof(int));
	char *cptr = (char *) cm_malloc(sizeof(char));
	double *freeMe = (double *) cm_malloc(sizeof(double));
	cm_malloc(MEM_POOL_SIZE/2);
	
	display_heap();
	
	cm_free(freeMe);
	
	display_heap();
	
	char *cptr2 = (char *) cm_malloc(sizeof(char));
	cm_memcpy(cptr2, cptr, sizeof(char));
	
	display_heap();
	
	cm_free(cptr);
	cm_defrag();
	
	display_heap();
	
	cm_realloc(cptr2, sizeof(float));
	
	display_heap();
	
	return EXIT_SUCCESS;
}
