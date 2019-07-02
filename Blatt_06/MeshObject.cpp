//
// Created by danielr on 02.07.18.
//
#include <algorithm>
#include <iostream>
#include "MeshObject.h"

MeshObject::MeshObject(int shaderHandle, HalfEdgeList *halfEdgeList)
{
    VAOBuilder *meshBuilder = new VAOBuilder();
    VAOBuilder *boundsBuilder = new VAOBuilder();
    VAOBuilder *vnBuilder = new VAOBuilder();
    VAOBuilder *fnBuilder = new VAOBuilder();

    this->boundsMin = glm::vec3(0.0f);
    this->boundsMax = glm::vec3(0.0f);

    for (HE_Face *face : halfEdgeList->faceList) 
	{
        HE_Edge *startingEdge = face->edge;
        HE_Edge *e = startingEdge;
        int idxStart = (int)meshBuilder->vertices.size();
        int idxNext = idxStart;
        do {
            // Vert, Normal & Indices
            meshBuilder->addVertex(e->vertex->pos);
            meshBuilder->addNormal(e->normal);
            if (e->next->next != startingEdge) {
                meshBuilder->addIndex(idxNext);
                meshBuilder->addIndex(idxStart);
                meshBuilder->addIndex(++idxNext);
            }

            // VertNormals
            glm::vec3 normalEnd = e->vertex->pos;
            normalEnd += e->normal;
            vnBuilder->addVertex(e->vertex->pos);
            vnBuilder->addNormal(e->normal);
            vnBuilder->addCurrentIndex();
            vnBuilder->addVertex(normalEnd);
            vnBuilder->addNormal(e->normal);
            vnBuilder->addCurrentIndex();

            // FaceNormals
            normalEnd = e->vertex->pos;
            normalEnd += face->normal;
            fnBuilder->addVertex(e->vertex->pos);
            fnBuilder->addNormal(face->normal);
            fnBuilder->addCurrentIndex();
            fnBuilder->addVertex(normalEnd);
            fnBuilder->addNormal(face->normal);
            fnBuilder->addCurrentIndex();

            // AABB
            this->boundsMin.x = std::min(e->vertex->pos.x, this->boundsMin.x);
            this->boundsMin.y = std::min(e->vertex->pos.y, this->boundsMin.z);
            this->boundsMin.z = std::min(e->vertex->pos.z, this->boundsMin.z);
            this->boundsMax.x = std::max(e->vertex->pos.x, this->boundsMax.x);
            this->boundsMax.y = std::max(e->vertex->pos.y, this->boundsMax.z);
            this->boundsMax.z = std::max(e->vertex->pos.z, this->boundsMax.z);
            e = e->next;
        } while (e != startingEdge);
    }
    this->meshVao = new VertexArrayObject(GL_TRIANGLES);
    meshBuilder->build(shaderHandle, this->meshVao);

    boundsBuilder->addVertex({this->boundsMin.x, this->boundsMin.y, this->boundsMin.z});
    boundsBuilder->addNormalFromVert();
    boundsBuilder->addVertex({this->boundsMax.x, this->boundsMin.y, this->boundsMin.z});
    boundsBuilder->addNormalFromVert();
    boundsBuilder->addVertex({this->boundsMax.x, this->boundsMin.y, this->boundsMax.z});
    boundsBuilder->addNormalFromVert();
    boundsBuilder->addVertex({this->boundsMin.x, this->boundsMin.y, this->boundsMax.z});
    boundsBuilder->addNormalFromVert();
    boundsBuilder->addVertex({this->boundsMin.x, this->boundsMax.y, this->boundsMin.z});
    boundsBuilder->addNormalFromVert();
    boundsBuilder->addVertex({this->boundsMax.x, this->boundsMax.y, this->boundsMin.z});
    boundsBuilder->addNormalFromVert();
    boundsBuilder->addVertex({this->boundsMax.x, this->boundsMax.y, this->boundsMax.z});
    boundsBuilder->addNormalFromVert();
    boundsBuilder->addVertex({this->boundsMin.x, this->boundsMax.y, this->boundsMax.z});
    boundsBuilder->addNormalFromVert();
    boundsBuilder->addIndices({0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7});
    this->boundsVao = new VertexArrayObject(GL_LINES);
    boundsBuilder->build(shaderHandle, this->boundsVao);

    this->vnVao = new VertexArrayObject(GL_LINES);
    vnBuilder->build(shaderHandle, this->vnVao);

    this->fnVao = new VertexArrayObject(GL_LINES);
    fnBuilder->build(shaderHandle, this->fnVao);
}

void MeshObject::render(glm::mat4x4 &projection,
						glm::mat4x4 &view, 
						glm::mat4x4 &projectionMod,
                        void (*shaderCallback)(glm::mat4, glm::mat4, glm::vec3), glm::vec3 &color)
{
    this->meshVao->render(projection, view, projectionMod, shaderCallback, color);

    if (this->showBounds)
        this->boundsVao->render(projection, view, projectionMod, shaderCallback, {1, 1, 1});
    if (this->showVn)
        this->vnVao->render(projection, view, projectionMod, shaderCallback, {0, 1, 0});
    if (this->showFn)
        this->fnVao->render(projection, view, projectionMod, shaderCallback, {0, 1, 1});
}

float MeshObject::getUniformScaleFactor() 
{
    if (inverseScaleFactor == 0) {
        glm::vec3 length = this->boundsMax;
        length -= this->boundsMin;
        // Null Länge
        if (length.x == 0 && length.y == 0 && length.z == 0)
            this->inverseScaleFactor = 1.0f;
        else
            this->inverseScaleFactor = 1.0f / length.length();
    }
    return inverseScaleFactor;
}

