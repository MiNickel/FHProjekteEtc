#ifndef HALFEDGE_H
#define HALFEDGE_H


#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include <map>


static unsigned int GLOBAL_EDGE_INDEX = 1;
static unsigned int GLOBAL_VERT_INDEX = 1;
static unsigned int GLOBAL_FACE_INDEX = 1;

class HE_Vertex;

class HE_Edge;

class HE_Face;

class HE_Edge {
private:
	const unsigned int idx;
public:
	HE_Edge() : idx(GLOBAL_EDGE_INDEX++) {}

	HE_Vertex *vertex = nullptr; //StartVertex
	HE_Edge* pair = nullptr; //Nachbarkante
	HE_Face* face = nullptr; // Face zu dem die Kante gehört
	HE_Edge* next = nullptr; // Nachfolgerkante
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

	HE_Edge* edge = nullptr; //eine der Kanten die von dem Punkt ausgehen
	glm::vec3 pos;

	unsigned int getIndex();

	std::string toString();
};

class HE_Face {
private:
	const unsigned int idx;
public:
	HE_Face() : idx(GLOBAL_FACE_INDEX++) {}

	HE_Edge* edge = nullptr; // eine der Kanten die zu dem Face gehören
	glm::vec3 normal;

	unsigned int getIndex();

	std::string toString();
};

//Keine Ahnung wozu
typedef std::pair<unsigned int, unsigned int> IntPair;
typedef std::map<IntPair, HE_Edge*> EdgePairMap;

class HalfEdgeList {
public:
	//keine Ahnung wozu
	EdgePairMap helper_pairMap;
	std::vector<glm::vec3> helper_vnList; //Evtl. Normalliste
	std::vector<glm::vec2> helper_vtList; //Evtl TextureVertex Liste

	std::vector<HE_Vertex *> vertexList; 
	std::vector<HE_Edge *> edgeList;
	std::vector<HE_Face *> faceList;

	bool verify();

	void makeFaceNormals();

	void fixNormals();
};

#endif //HALFEDGE_H