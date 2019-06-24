//
// Created by danielr on 02.07.18.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "OBJLoader.h"

static int vCount = 1;


HalfEdgeList *loadIntoHEL(std::string filename) {
    auto *halfEdgeList = new HalfEdgeList();

    std::ifstream input(filename);
    if (!input.good()) {
        std::cerr << "Fehler beim einlesen der Datei " << filename << std::endl;
        return nullptr;
    }
    std::cout << "Beginne Parsing von " << filename << std::endl;

    std::string line;
    int lineCount = 0;
    while (input.good()) {
        try {
            std::getline(input, line);
//            std::cout << "working on line " << line << std::endl;
            handleLine(lineCount++, line, halfEdgeList);
        }
        catch (...) {
            std::exception_ptr p = std::current_exception();
            std::clog << (p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        }
    }
    std::cout << "Parsing fertig, starte verify" << std::endl;

    if (halfEdgeList->verify()) {
        std::cout << "Verify fertig" << std::endl;
        halfEdgeList->makeFaceNormals();
    } else
        std::cerr << "HalfEdgeList konnte nicht verifiziert werden!" << std::endl;
    return halfEdgeList;
}

void handleLine(int lineCount, std::string line, HalfEdgeList *halfEdgeList) {
    if (line.substr(0, 2) == "v ") { //Vertex
        auto *vert = new HE_Vertex();
        sscanf(line.c_str(), "v %f %f %f", &vert->pos.x, &vert->pos.y, &vert->pos.z);
        halfEdgeList->vertexList.push_back(vert);
    } else if (line.substr(0, 3) == "vn ") { //Vertex Normal
        glm::vec3 vn = glm::vec3(0);
        sscanf(line.c_str(), "vn %f %f %f", &vn.x, &vn.y, &vn.z);
        halfEdgeList->helper_vnList.push_back(vn);
    } else if (line.substr(0, 3) == "vt ") { //Vertex Texture
        glm::vec2 vt = glm::vec2(0);
        sscanf(line.c_str(), "vt %f %f", &vt.x, &vt.y);
        halfEdgeList->helper_vtList.push_back(vt);
    } else if (line.substr(0, 2) == "f ") { //Vertex
        auto face = new HE_Face();

        std::stringstream stream(line);
        std::string buffer;
        int count = 0;
        HE_Edge *firstEdge = nullptr;
        HE_Edge *prevEdge = nullptr;
        while (stream >> buffer)
            if (count++ != 0) {//Skip f
                auto edge = new HE_Edge;
                int iV = -1;
                int iVt = -1;
                int iVn = -1;
                if (sscanf(buffer.c_str(), "%d/%d/%d", &iV, &iVt, &iVn) == 3);
                else if (sscanf(buffer.c_str(), "%d//%d", &iV, &iVn) == 2);
                else if (sscanf(buffer.c_str(), "%d/%d", &iV, &iVt) == 2);
                else if (sscanf(buffer.c_str(), "%d", &iV) == 1);
                else
                    std::cerr << "Fehler beim einlesen von Zeile " << lineCount << ": Formatierung der Fläche";

                HE_Vertex *vert = halfEdgeList->vertexList[iV - 1];
                edge->vertex = vert;
                if (iVn >= 0) // Set Normal
                    edge->normal = halfEdgeList->helper_vnList[iVn - 1];
                if (iVt >= 0) // Set Texture
                    edge->texture = halfEdgeList->helper_vtList[iVn - 1];
                vert->edge = edge;
                edge->face = face;
                if (firstEdge == nullptr) {
                    firstEdge = edge;
                    face->edge = edge;
                } else if (prevEdge) {
                    prevEdge->next = edge;
                    tryMakePair(prevEdge, halfEdgeList);
                }
                halfEdgeList->edgeList.push_back(edge);
                prevEdge = edge;
            }
        if (prevEdge && firstEdge) {
            prevEdge->next = firstEdge;
            tryMakePair(prevEdge, halfEdgeList);
        }
        halfEdgeList->faceList.push_back(face);
    }

}

void tryMakePair(HE_Edge *edge, HalfEdgeList *halfEdgeList) {
    if (edge->next != nullptr) {
        IntPair key = std::make_pair(edge->vertex->getIndex(), edge->next->vertex->getIndex());

        EdgePairMap::iterator entry = halfEdgeList->helper_pairMap.find(key);
        if(entry == halfEdgeList->helper_pairMap.end())
        {
            IntPair oppositeKey = std::make_pair(edge->next->vertex->getIndex(),edge->vertex->getIndex());
            halfEdgeList->helper_pairMap.insert(std::make_pair(oppositeKey, edge));
        } else
        {
            entry->second->pair = edge;
            edge->pair = entry->second;
            halfEdgeList->helper_pairMap.erase(entry);
        }
    }
}
