#include "studiverwaltung/studiverwaltung.h"
#include "studiverwaltung/spfree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*!
 * \file studiverwaltung.c
 * \brief Verwaltung der Studenten in doppelt verketteten Listen.
 */

void show_all(node *liste) {
	char subject[5];
	if(liste && liste->stdnt) {
		switch(liste->stdnt->enrolled) {
			case IFM:
				strcpy(subject, "IFM");
				break;
			case ELM:
				strcpy(subject, "ELM");
				break;
			case PFLEGE:
				strcpy(subject, "PFLEGE");
				break;
			default:
				strcpy(subject, "UNBEKANNT");
				break;
		}
		printf("Name: %s\nCreditPoints: %u\nStudiengang: %s \n\n", liste->stdnt->name, liste->stdnt->cps, subject);
		
		show_all(liste->next);
	}
}

node* get_ifm_students(node *liste) {
	node *next = liste;
	node *ifm_liste;
	node *ifm_last;
	unsigned short boolean = 0;
	while(next) {
		if(next->stdnt->enrolled == IFM) {
			node *newNode = (node *) malloc(sizeof(node));
			newNode->stdnt = next->stdnt;
			if(boolean) {
				ifm_last->next = newNode;
				newNode->prev = ifm_last;
				ifm_last = ifm_last->next;
			} else {
				ifm_liste = newNode;
				ifm_last = ifm_liste;
				boolean = 1;
			}
		}
		next = next->next;
	}
	ifm_last->next = NULL;
	
	return ifm_liste;
}

node* append_student(node *liste, student *stdnt) {
	node *maltesListe = liste;
	node *last;
	if(!stdnt) {
		return get_list_origin(maltesListe);
	}
	if(liste) {
		last = maltesListe;
		while(last->next) {
			last = last->next;
		}
		last->next = (node *) malloc(sizeof(node));
		last->next->prev = last;
		last = last->next;
		last->stdnt = stdnt;
		
	} else {
		maltesListe = (node *) malloc(sizeof(node));
		maltesListe->prev = NULL;
		maltesListe->stdnt = stdnt;
		maltesListe->next = NULL;
	}
	return get_list_origin(maltesListe);
}

node* delete_node(node *knoten, sp_purge operation) {
	node *start = get_list_origin(knoten);
	if (knoten->next) {
		knoten->next->prev = knoten->prev;
	}
	if (knoten->prev) {
		knoten->prev->next = knoten->next;
	} else {
		start = knoten->next;
	}
	if(operation == NODE_AND_STUDENT) {
		sp_free(knoten->stdnt);
	}
	sp_free(knoten);
	return start;
}

int delete_list(node *liste) {
	node *currentDelete = liste;
	int count = 0;
	while(currentDelete) {
		currentDelete = delete_node(currentDelete, NODE_AND_STUDENT);
		count++;
	}
	return count;
}

int delete_list_partial(node *liste) {
	node *currentDelete = get_list_origin(liste);
	int count = 0;
	while(currentDelete) {
		currentDelete = delete_node(currentDelete, NODE_ONLY);
		count++;
	}
	return count;
}

node* get_list_origin(node* knoten) {
	node* aktuellerKnoten = knoten;
	if(!knoten) {
		return NULL;
	}
	while(aktuellerKnoten->prev) {
		aktuellerKnoten = aktuellerKnoten->prev;
	}
	return aktuellerKnoten;
}
