/*
 * spfree.h
 *
 *                              Vorgabe
 */

#ifndef SPFREE_H
#define SPFREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NODE_ONLY, NODE_AND_STUDENT
} sp_purge;

void sp_free(void *ptr); /* Prototyp hier fuer Tests */

#ifdef __cplusplus
}
#endif

#endif /* SPFREE_H */

