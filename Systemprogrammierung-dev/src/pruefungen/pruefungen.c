#include "pruefungen/pruefungen.h"
#include <stdlib.h>
/*!
 * \file pruefungen.c
 * \brief Verwalten der Termin Liste.
 */
 
 /**
  * \var student *exams[NUM_EXAMS]
  * Termin Liste
  */
student *exams[NUM_EXAMS];

int register_student(student *s, int nr) {
	int pos = nr;
	int run = 1;
	if(!s || contains(s) != -1 || !s->name[0] || nr < 0 || nr > 9) {
		return -1;
	}
	while (exams[pos] && run) {
		pos++;
		if (pos >= NUM_EXAMS) {
			pos = 0;
		}
		if (pos == nr) {
			return -1;
		}
	}
	exams[pos] = s;
	return pos;
}

int remove_student(student *s) {
	int pos;
	if(!s) {
		return -1;
	}
	pos = contains(s);
	if(pos >= 0) {
		exams[pos] = NULL;
	}
	return pos;
}

float calculate_average(void) {
	unsigned int numStudents = 0;
	unsigned int cps = 0;
	int i;
	for (i = 0; i < NUM_EXAMS; i++) {
		if(exams[i]){
			numStudents++;
			cps += exams[i]->cps;
		}
	}
	if (!numStudents) {
		return 0;
	}
	return  (((float) cps / (float) numStudents) / MAXIMUM_POINTS) * 100;
}

int contains(student *s) {
	if(s){
		int nr;
		for (nr = 0; nr < NUM_EXAMS; nr++) {
			if (s == exams[nr]) {
				return nr;
			}
		}
	}
	return -1;
}
