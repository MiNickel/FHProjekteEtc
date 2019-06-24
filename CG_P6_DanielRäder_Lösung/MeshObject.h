//
// Created by danielr on 02.07.18.
//

#ifndef BLATT01_MESHOBJECT_H
#define BLATT01_MESHOBJECT_H


#include <glm/vec3.hpp>
#include <vector>
#include <GL/glew.h>
#include "VertexArrayObject.h"
#include "HalfEdgeList.h"

class MeshObject {
private:
    float inverseScaleFactor = 0;
public:
    MeshObject(int shaderHandle, HalfEdgeList *halfEdgeList);

    glm::vec3 boundsMin;
    glm::vec3 boundsMax;

    VertexArrayObject *meshVao;
    bool showBounds = false;
    VertexArrayObject *boundsVao;
    bool showVn = false;
    VertexArrayObject *vnVao;
    bool showFn = false;
    VertexArrayObject *fnVao;

    float getUniformScaleFactor();

    void render(glm::mat4x4 &projection, glm::mat4x4 &view, glm::mat4x4 &projectionMod,
                void (*shaderCallback)(glm::mat4, glm::mat4, glm::vec3), glm::vec3 &color);
};

#endif //BLATT01_MESHOBJECT_H
