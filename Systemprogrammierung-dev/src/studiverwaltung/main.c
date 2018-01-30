#include "studiverwaltung/studiverwaltung.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


int main() {
	node *node1 = (node *) malloc(sizeof(node));
	node *node2 = (node *) malloc(sizeof(node));
	student *stdnt1 = (student *) malloc(sizeof(student));
	student *stdnt2 = (student *) malloc(sizeof(student));
	student *stdnt3 = (student *) malloc(sizeof(student));
	node *ifm_liste;
	
	if(!node1 && !node2 && !stdnt1 && !stdnt2) {
		printf("Error");
	} else {
		strcpy(stdnt1->name, "Tim Steven Meier");
		strcpy(stdnt2->name, "Malte Riechmann");
		strcpy(stdnt3->name, "Tom Meier");
		
		stdnt1->cps = 10;
		stdnt2->cps = 10000;
		stdnt3->cps = 0;
		
		stdnt1->enrolled = PFLEGE;
		stdnt2->enrolled = IFM;
		stdnt3->enrolled = ELM;
		
		node1->prev = NULL;
		node1->next = node2;
		node1->stdnt = stdnt1;
		
		node2->prev = node1;
		node2->next = NULL;
		node2->stdnt = stdnt2;
		
		ifm_liste = get_ifm_students(node1);
		printf("IFM Liste\n");
		show_all(ifm_liste);
		printf("Nix\n");
		show_all((node *) malloc(sizeof(node)));
		
		printf("Append\n");
		show_all(append_student(node1, stdnt3));
		printf("Delete\n");
		show_all(delete_node(node2, NODE_AND_STUDENT));
		printf("Delete Partial\n");
		delete_list_partial(ifm_liste);
		printf("Normale Liste print\n");
		show_all(node1);
		printf("Delete Main List\n");
		delete_list(node1);
	}
	return EXIT_SUCCESS;
}
