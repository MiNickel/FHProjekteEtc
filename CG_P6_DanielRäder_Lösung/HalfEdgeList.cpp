//
// Created by danielr on 02.07.18.
//

#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <map>
#include "HalfEdgeList.h"
#include "MeshObject.h"

glm::vec3 getVectorForEdge(HE_Edge *edge) {
    return glm::normalize(edge->next->vertex->pos - edge->vertex->pos);
}

bool HalfEdgeList::verify() {
    bool passed = true;

    unsigned int count_vert = 0;
    unsigned int count_edge = 0;
    unsigned int count_face = 0;
    std::map<unsigned int, unsigned int> valence_face;
    std::map<unsigned int, unsigned int> valence_vert;

    for (HE_Face *face : this->faceList) {
        HE_Edge *fEdge = face->edge;
        unsigned int count = 0;
        do {
            if (fEdge->face != face) {
                std::cout << "ERROR: Face " << face->toString() << " has nicht-verknüpfte Kanten!";
                passed = false;
            }
            fEdge = fEdge->next;
            count++;
        } while (fEdge != face->edge);

        if (valence_face.find(count) == valence_face.end())
            valence_face.insert(std::make_pair(count, (unsigned int) 1));
        else
            valence_face[count] += 1;
        count_face++;
    }

    for (HE_Edge *edge : this->edgeList) {
        if (edge->pair == nullptr) {
            std::cout << "ERROR: Edge " << edge->toString() << " hat kein Paar!" << std::endl;
            passed = false;
        } else if (edge->pair->pair != edge) {
            std::cout << "ERROR: Edge " << edge->toString() << " hat ein falsches Paar: "<<edge->pair->toString() << std::endl;
            passed = false;
        }
        count_edge++;
    }

    for (HE_Vertex *vertex : this->vertexList) {

        HE_Edge *vEdge = vertex->edge;
        HE_Edge *nextEdge = vEdge;
        bool hasPartner = true;
        unsigned int count = 0;
        do {
            if (nextEdge->vertex != vertex)
                hasPartner = false;
            count++;
            nextEdge = nextEdge->pair->next;
        } while (vEdge != nextEdge);
        if (!hasPartner) {
            std::cout << "ERROR: Vertex " << vertex->toString() << " enspricht nicht Zielpunkt der Partner-Edge"
                      << std::endl;
            passed = false;
        }

        if (valence_vert.find(count) == valence_vert.end())
            valence_vert.insert(std::make_pair(count, (unsigned int) 1));
        else
            valence_vert[count] += 1;
        count_vert++;
    }

    std::cout << "Model hat " << count_face << " Faces" << std::endl;
    std::map<unsigned int, unsigned int>::iterator it = valence_face.begin();
    while (it != valence_face.end()) {
        std::cout << " Valenz " << it->first << ": " << it->second << " Faces" << std::endl;
        it++;
    }

    std::cout << "Model hat " << count_vert << " Vertices" << std::endl;
    it = valence_vert.begin();
    while (it != valence_vert.end()) {
        std::cout << " Valenz " << it->first << ": " << it->second << " Vertices" << std::endl;
        it++;
    }

    std::cout << "Model hat " << count_edge << " Edges" << std::endl;

    return passed;
}

void HalfEdgeList::makeFaceNormals() {
    for (HE_Face *face : this->faceList) {
        glm::vec3 normal = glm::vec3(0.0f);
        HE_Edge *edge = face->edge;
        do {
            normal += edge->normal;
            edge = edge->next;
        } while (edge != face->edge);
        face->normal = glm::normalize(normal);
    }
}

void HalfEdgeList::fixNormals() {
    for (HE_Face *face : this->faceList) {
        glm::vec3 normal = glm::vec3(0.0f);
        HE_Edge *edge = face->edge;
        do {
            normal += glm::cross(getVectorForEdge(edge), getVectorForEdge(edge->next));
            edge = edge->next;
        } while (edge != face->edge);
        face->normal = glm::normalize(normal);
    }

    int c = 0;
    for (HE_Edge *edge : this->edgeList) {

        glm::vec3 normal = glm::vec3(0.0f);
        HE_Edge *normalEdge1 = edge;

        do {
            HE_Edge *normalEdge2 = normalEdge1->pair->next;
            normal += glm::cross(getVectorForEdge(normalEdge2), getVectorForEdge(normalEdge1));
            normalEdge1 = normalEdge2;
        } while (normalEdge1 != edge);
        edge->normal = glm::normalize(normal);
    }
}


unsigned int HE_Vertex::getIndex() {
    return this->idx;
}

std::string HE_Vertex::toString() {
    std::ostringstream oss;
    oss << "Vertex " << this->getIndex();
    oss << "[" << this->pos.x << "," << this->pos.y << "," << this->pos.z << "]";
    return oss.str();
}

unsigned int HE_Edge::getIndex() {
    return this->idx;
}

std::string HE_Edge::toString() {
    std::ostringstream oss;
    oss << "Edge" << this->getIndex();
    oss << " [" << this->vertex->getIndex() << ",";
    oss << this->next->vertex->getIndex() << "]";
    return oss.str();
}

unsigned int HE_Face::getIndex() {
    return this->idx;
}

std::string HE_Face::toString() {
    std::ostringstream oss;
    oss << "Face" << this->getIndex() << " {";
    HE_Edge *fEdge = this->edge;
    do {
        oss << fEdge->toString();
        fEdge = fEdge->next;
        if (fEdge != this->edge)
            oss << ", ";
    } while (fEdge != this->edge);
    oss << "}";
    return oss.str();
}

