#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <map>
#include "HalfEdgeList.h"

//Vektor der Kante berechnen
glm::vec3 getVectorForEdge(HE_Edge *edge) {
	return glm::normalize(edge->next->vertex->pos - edge->vertex->pos);
}

bool HalfEdgeList::verify() {

}

//Übers Face itterieren und Normal aus den Edgenormals berechnen
void HalfEdgeList::makeFaceNormals() {
	for (HE_Face *face : this->faceList) {
		glm::vec3 normal = glm::vec3(0.0f);
		HE_Edge* edge = face->edge;
		do { //addieren aller Edge-Normals eines Faces
			normal += edge->normal;
			edge = edge->next;
		}while(edge != face->edge); // face->edge: Start und zugleich Endedge
		face->normal = glm::normalize(normal);
	}
}

//falls Normalen nicht passen
void HalfEdgeList::fixNormals() {
	for (HE_Face *face : this->faceList) {
		glm::vec3 normal = glm::vec3(0.0f);
		HE_Edge* edge = face->edge;
		do {
			normal += glm::cross(getVectorForEdge(edge), getVectorForEdge(edge->next));
			edge = edge->next;
		} while (edge != face->edge);
		face->normal = glm::normalize(normal);
	}

	for (HE_Edge *edge : this->edgeList) {
		glm::vec3 normal = glm::vec3(0.0f);
		HE_Edge* normalEdge1 = edge;
		do {
			HE_Edge* normalEdge2 = normalEdge1->pair->next;
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
	oss << "Vertex" << this->getIndex();
	oss << " [" << this->pos.x << "," << this->pos.y << "," << this->pos.z << " ]";
	return oss.str();
}

unsigned int HE_Edge::getIndex() {
	return this->idx;
}

std::string HE_Edge::toString() {
	std::ostringstream oss;
	oss << "Edge" << this->getIndex();
	oss << " [" << this->vertex->getIndex() << " ,";
	oss << this->next->vertex->getIndex() << " ]";
	return oss.str();
}

unsigned int HE_Face::getIndex() {
	return this->idx;
}

std::string HE_Face::toString() {
	std::ostringstream oss;
	oss << "Face" << this->getIndex() << " {";
	HE_Edge* fEdge = this->edge;
	do {
		oss << fEdge->toString();
		fEdge = fEdge->next;
		if (fEdge != this->edge) {
			oss << ", ";
		} 
	} while (fEdge != this->edge);
	oss << "}";
	return oss.str();
}