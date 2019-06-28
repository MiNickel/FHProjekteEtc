#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "HalfEdgeList.h"
#include <string>

void handleLine(int lineCount, std::string line, HalfEdgeList *halfedgelist);

void tryMakePair(HE_Edge *edge, HalfEdgeList *halfedgelist);

HalfEdgeList* loadIntoHEL(std::string filename);

#endif // !OBJLOADER_H

