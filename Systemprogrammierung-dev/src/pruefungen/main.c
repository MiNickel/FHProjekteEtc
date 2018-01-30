#include "pruefungen/pruefungen.h"
#include "pruefungen/display.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
	
	student *stdnt1 = (student *) malloc(sizeof(student));
	student *stdnt2 = (student *) malloc(sizeof(student));
	student *stdnt3 = (student *) malloc(sizeof(student));
	student *stdnt4 = (student *) malloc(sizeof(student));

	strcpy(stdnt1->name, "Tim Steven Meier");
	strcpy(stdnt2->name, "Malte Riechmann");
	strcpy(stdnt3->name, "Tom Meier");
	
	stdnt1->cps = 10;
	stdnt2->cps = 320;
	stdnt3->cps = 0;
	
	stdnt1->enrolled = PFLEGE;
	stdnt2->enrolled = IFM;
	stdnt3->enrolled = ELM;
	
	printf("Stdnt4, 3: %d\n", register_student(stdnt4, 3));
	printf("Stdnt1, 3: %d\n", register_student(stdnt1, 3));
	printf("Stdnt2, 3: %d\n", register_student(stdnt2, 3));
	printf("Stdnt2, 9: %d\n", register_student(stdnt2, 9));
	printf("Stdnt3, 10: %d\n", register_student(stdnt3, 10));
	
	printf("Stdnt2, delete, 4: %d\n", remove_student(stdnt2));
	printf("Stdnt3, delete, -1: %d\n", remove_student(stdnt3));
	
	printf("Average: %f\n", calculate_average());
	
	register_student(stdnt3, 0);
	register_student(stdnt2, 3);
	
	display_average();
	display_absolute();
	return 0;
}
