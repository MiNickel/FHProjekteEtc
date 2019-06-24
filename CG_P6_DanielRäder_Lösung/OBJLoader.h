//
// Created by danielr on 02.07.18.
//

#ifndef BLATT01_OBJLOADER_H
#define BLATT01_OBJLOADER_H

#include "HalfEdgeList.h"
#include <string>

void handleLine(int lineCount, std::string line, HalfEdgeList *halfEdgeList);

void tryMakePair(HE_Edge *edge, HalfEdgeList *halfEdgeList);

HalfEdgeList *loadIntoHEL(std::string filename);

#endif //BLATT01_OBJLOADER_H
