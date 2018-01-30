/*
 * spfree.c
 *
 *                              Vorgabe
 */

#include <stdlib.h>

#include "studiverwaltung/spfree.h"

/* Wrapper-Funktion um das systemeigene free() mocken zu koennen */
void sp_free(void *pt) {
    free(pt);
}
