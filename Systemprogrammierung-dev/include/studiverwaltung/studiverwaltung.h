#include "studiverwaltung/spfree.h"
#ifdef __cplusplus
extern "C" {
#endif
/*!
 * \file studiverwaltung.h
 * \brief Definitionen für die Studiverwaltung
 */
 
/**
 * \enum degree_program {IFM, ELM, PFLEGE}
 * Aufzählung der Studiengänge
 */
typedef enum degree_program {IFM, ELM, PFLEGE} degree_program;

/**
 * \var NAME_LENGTH = 32
 * Maximale Länge der Namen der Studenten
 */
#ifndef NAME_LENGTH
#define NAME_LENGTH 32
#endif

/**
 * \struct student
 * Struktur zum Verwalten eines Studenten
 */
typedef struct student {
	char name[NAME_LENGTH];
	unsigned int cps;
	degree_program enrolled;
} student;

/**
 * \struct node
 * Ein Knoten einer verketteten Liste
 */
typedef struct node{
	student *stdnt;
	struct node *prev;
	struct node *next;
} node;

/**
 * \fn void show_all(node *)
 * \param liste Startknoten der Liste
 * Gibt die gesamte Liste aus
 */
void show_all(node*);

/**
 * \fn node* get_ifm_students(node *)
 * \param liste Startknoten der Liste
 * \return Liste mit allen Informatikstudenten
 * Gibt alle Informatik Studenten aus der Liste zurück
 */
node* get_ifm_students(node*);

/**
 * \fn node *append_student(node *, student *);
 * \param liste Hier soll der Student angefügt werden
 * \param stdnt Student, der hinzugefügt werden soll
 * \return Liste mit dem hinzugefügen Studenten
 * Fügt einen neuen Studenten ans Ende der Liste hinzu
 */
node* append_student(node*, student*);

/**
 * \fn node *delete_node(node * knoten, sp_purge operation)
 * \param knoten Knoten, der gelöscht werden soll
 * \param operation Auszuführende Operation
 * \return Liste ohne gelöschten Knoten
 * Löscht einen Knoten aus der Liste und gegebenenfalls auch den Studenten abhängig von der Operation
 */
node* delete_node(node*, sp_purge );

/**
 * \fn int delete_list(node *liste)
 * \param liste zu löschende Liste
 * \return Anzahl der Knoten, die freigegeben wurden
 * Löscht die komplette Liste mit Studenten
 */
int delete_list(node*);

/**
 * \fn int delete_list_partial(node *liste);
 * \param liste zu löschende Liste
 * \return Anzahl der Knoten, die freigegeben wurden
 * Löscht die komplette Liste ohne Studenten
 */
int delete_list_partial(node*);

/**
 * \fn node* get_list_origin(node* knoten);
 * \param knoten Knoten aus Liste dessen Anfang man sucht
 * \return Anfang der Liste
 */
node* get_list_origin(node* );

#ifdef __cplusplus
}
#endif
