//
// Created by danielr on 02.07.18.
//

#ifndef BLATT01_HALFEDGE_H
#define BLATT01_HALFEDGE_H

#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include <map>
#include "VertexArrayObject.h"

static unsigned int GLOBAL_VERT_INDEX = 1;
static unsigned int GLOBAL_EDGE_INDEX = 1;
static unsigned int GLOBAL_FACE_INDEX = 1;

class HE_Vertex;

class HE_Edge;

class HE_Face;

class HE_Edge {
private:
    const unsigned int idx;
public:
    HE_Edge() : idx(GLOBAL_EDGE_INDEX++) {}

    HE_Vertex *vertex = nullptr; //start-vertex of the half-edge
    HE_Edge *pair = nullptr; //oppositely oriented adjacent half-edge
    HE_Face *face = nullptr; //face the half-edge borders
    HE_Edge *next = nullptr; //next half-edge around the face
    glm::vec3 normal;
    glm::vec2 texture;

    unsigned int getIndex();

    std::string toString();
};

class HE_Vertex {
private:
    const unsigned int idx;
public:
    HE_Vertex() : idx(GLOBAL_VERT_INDEX++) {}

    glm::vec3 pos;
    HE_Edge *edge = nullptr; //one of the half-edges emanating from the vertex

    unsigned int getIndex();

    std::string toString();
};


class HE_Face {
private:
    const unsigned int idx;
public:
    HE_Face() : idx(GLOBAL_FACE_INDEX++) {}

    HE_Edge *edge = nullptr;
    glm::vec3 normal;

    unsigned int getIndex();

    std::string toString();
};

typedef std::pair<unsigned int, unsigned int> IntPair;
typedef std::map<IntPair, HE_Edge *> EdgePairMap;

class HalfEdgeList {
public:
    EdgePairMap helper_pairMap;
    std::vector<glm::vec3> helper_vnList;
    std::vector<glm::vec2> helper_vtList;

    std::vector<HE_Vertex *> vertexList;
    std::vector<HE_Edge *> edgeList;
    std::vector<HE_Face *> faceList;

    bool verify();

    void makeFaceNormals();

    void fixNormals();
};


#endif //BLATT01_HALFEDGE_H
