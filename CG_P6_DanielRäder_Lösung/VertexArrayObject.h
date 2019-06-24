//
// Created by danielr on 02.07.18.
//

#ifndef BLATT01_VERTEXARRAYOBJECT_H
#define BLATT01_VERTEXARRAYOBJECT_H


#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <vector>

class VertexArrayObject {
public:
    VertexArrayObject(int _drawMode);

    const int drawMode;
    GLuint vao;

    GLuint positionBuffer;
    GLuint normalBuffer;
    GLuint indexBuffer;
    int indexCount;

    /* Model matrix */
    glm::mat4x4 model;

    void render(glm::mat4x4 projection, glm::mat4x4 view, glm::mat4x4 projectionMod,
                void (*shaderCallback)(glm::mat4, glm::mat4, glm::vec3), glm::vec3 color);
};

class VAOBuilder {
public:
    std::vector<glm::vec3> vertices = {};
    std::vector<glm::vec3> normals = {};
    std::vector<GLuint> indices = {};

    void addVertex(glm::vec3 vertex);

    void addNormal(glm::vec3 normal);

    void addNormalFromVert();

    void addCurrentIndex();

    void addIndex(int index);

    void addIndices(std::vector<int> indices);

    void build(int shaderHandle, VertexArrayObject *vertexArrayObject);
};


#endif //BLATT01_VERTEXARRAYOBJECT_H
