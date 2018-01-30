/*!
 * \file speicherverwaltung.h
 * \brief Definitionen für die Speicherverwaltung
 */
#include <stdlib.h>

/**
 * \var MEM_POOL_SIZE
 * Definition der Größe des MEM_POOL
 */
#define MEM_POOL_SIZE 16384

/**
 * \var MAGIC_INT
 * Definition des MAGIC_INT
 */
#define MAGIC_INT 0xacdcacdc

/**
 * \var mempool
 * Der durch ein Byte-Array simulierte Heap
 */
extern char mempool [MEM_POOL_SIZE];

/**
 * \enum CountType {TSM_COUNT, TSM_BYTE}
 * Art des Zählens
 */
typedef enum CountType {TSM_COUNT, TSM_BYTE} CountType;

/**
 * \struct memblock
 * \var size Groesse des memblock
 * \var next naechster memblock
 * Verwaltungsstruktur, mit der nutzbaren Länge des Blocks(size_t)
 * und einem Zeiger auf den nächsten freien Block(evtl. NULL)
 */
typedef struct memblock {
	size_t size;
	struct memblock * next;
} memblock;

/**
 * \var memblock *
 * Der Pointer freemem zeigt immer auf den Anfang der Freispeicherliste
 * NULL, wenn keine freien Blöcke existieren.
 */
extern memblock *freemem;

/**
 * \fn init_heap
 * initialisiert den simulierten Heap und lässt den Pointer freemem auf die Freispeicherliste zeigen.
 * die Funktion initialisiert den heap einmalig und wird keinen neuen heap erstellen, wenn schon einer existiert.
 */
void init_heap(void);

/**
 * \fn cm_malloc
 * \param size Groesse des Speicherbereichs
 * \return Pointer auf Speicherbereich
 * cm_malloc sucht nach dem ersten freien Speicherblock mit der Größe size_t.
 * Falls dieser gefunden wird, wird dieser alloziert, ansonsten wird NULL zurückgegeben.
 */
void *cm_malloc(size_t size);

/**
 * \fn cm_free
 * \param Pointer auf zu löschenden Speicherbereich
 * Der Speicher des ptrs wird freigegeben
 * und der freigegebene Block wird an den Anfang der Freispeicherliste gehängt.
 */
void cm_free(void *ptr);

/**
 * \fn cm_defrag
 * cm_defrag fügt benachbarte freie Blöcke aus der Freispeicherliste zu einem zusammen.
 */
void cm_defrag(void);

/**
 * \fn cm_defrag20
 * cm_defrag20 fügt benachbarte freie Blöcke zu einem zusammen,
 * dabei geht sie blockweise durch das Array mempool.
 */
void cm_defrag20(void);

/**
 * \fn cm_memcpy
 * \param dest Zielspeicherbereich
 * \param src Zu kopierender Speicherbereich
 * \param size Anzahl Byte, die kopiert werden sollen
 * \return Zielspeicherbereich
 * cm_memcpy kopiert n Bytes beginnend ab src in den Speicherbereich beginnend ab dest.
 * gibt den Pointer dest zurück, wenn dest oder src NULL sind, oder nicht mit cm_malloc erstellt wurden
 */
void *cm_memcpy(void *dest, const void *src, size_t n);

/**
 * \fn cm_realloc
 * \param ptr neu zu setzender Pointer
 * \param size neue Speicherbereichgroesse
 * \return Pointer auf neuen Speicherbereich
 * Wenn der ptr NULL ist, dann entspricht die Funktion cm_malloc(size).
 * Wenn die size NULL ist, dann entspricht die Funktion cm_free(ptr).
 * Wenn beide ungleich NULL sind, dann wird mit cm_malloc neuer Speicher bereitgestellt,
 * als nächstes wird der Speicher umkopiert und zum Schluss wird der alte Speicher freigegeben.
 */
void *cm_realloc(void *ptr, size_t size);
