/*
 * studiverwaltung.c
 *
 * Alle Funktionen zur Studi-Verwaltung sind in diesem Source File zu definieren.
 *
 */
#include <studiverwaltung.h>
#include <stdlib.h>
#include <stdio.h>

/* **************************** VORGABEN ********************************** */
/* Wrapper-Funktion um das systemeigene free() mocken zu koennen */
void sp_free(void *pt) {
    free(pt);
}
/* **************************** VORGABEN ********************************** */

void show_all(node *nptr) {
	if(nptr) {
		student * std = nptr->stdnt;
		printf("Name = %s \n",std->name);
		show_all(nptr->next);
	}
	return;
}

static node* get_list_origin(node* nd){
	while(nd->prev) {
		nd = nd->prev;
	}
	return nd;
}

node* append_student(node* nd, student* std) {
	if(!std) {
		return NULL;
	}
	if (nd == NULL) {
		node * root;
		if((root = (struct node *) malloc(sizeof(node))) == NULL) {
			return NULL;
		}
		root->next = NULL;
		root->prev = NULL;
		root->stdnt = std;
		return root;
	}
	while(nd->next){
		nd = nd->next;
	}
	nd->next = (struct node *) malloc(sizeof(node));
	nd->next->prev = nd;
	nd->next->next = NULL;
	nd->next->stdnt = std;
	return get_list_origin(nd);
}

static node* delete_node(node* nd, sp_boolean bool) {

    if(nd->prev == NULL && nd->next != NULL) {
        nd->next->prev = NULL;
    }
    else if (nd->prev != NULL && nd->next == NULL) {
        nd->prev->next == NULL;
    }
    else if (nd->prev != NULL && nd->next != NULL) {
        nd->prev->next = nd->next;
        nd->next->prev = nd->prev;
    }
    if(bool == TRUE) {
		
		sp_free(nd->stdnt);
    }

    if (nd->prev == NULL){
	sp_free(nd);
	return NULL;
    }
    node * nd2 = nd->prev;
    sp_free(nd);
    return get_list_origin(nd2);
}

int delete_list(node* nd) {
	int count = 0;
	while(nd->next) {
		nd = nd->next;
	}
	while(nd->prev) {
		nd = nd->prev;
		delete_node(nd->next,TRUE);
		count++;
	}
	delete_node(nd,TRUE);
	return count+1;
}

int delete_list_partial(node* nd) {
	int count = 0;
	while(nd->next) {
		nd = nd->next;
	}
	while(nd->prev) {
		nd = nd->prev;
		delete_node(nd->next,FALSE);
		count++;
	}
	delete_node(nd,FALSE);
	return count+1;
}

node * get_ifm_students(node * nd) {
	if(nd == NULL) {
		return NULL;
		
	}
	nd = get_list_origin(nd);
	node * new_ifm_list = (node *) malloc(sizeof(node));
	node * nptr;
	int i = 0;
	while(nd) {
		if(nd->stdnt != NULL && nd->stdnt->enrolled == IFM){
			if(new_ifm_list->stdnt == NULL) {
				new_ifm_list->stdnt = nd->stdnt;
				new_ifm_list->next = NULL;
				new_ifm_list->prev = NULL;
				nptr = new_ifm_list;
			}
			else {
				nptr->next = (node *) malloc(sizeof(node));
				nptr->next->prev = nptr;
				nptr->next->stdnt = nd->stdnt;
				nptr = nptr->next;
			}
		}
		nd = nd->next;
	}
	return new_ifm_list;
}
