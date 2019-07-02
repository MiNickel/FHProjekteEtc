//
// Created by danielr on 02.07.18.
//

#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject(int _drawMode) : drawMode(_drawMode) {}

void VertexArrayObject::render(glm::mat4x4 projection, glm::mat4x4 view, glm::mat4x4 projectionMod,
                               void (*shaderCallback)(glm::mat4, glm::mat4, glm::vec3), glm::vec3 color) {
    glm::mat4x4 modifiedModel = this->model * projectionMod;
    glm::mat4x4 mvp = projection * view * modifiedModel;

    shaderCallback(mvp, modifiedModel, color);

    // GLUT: bind vertex-array-object
    // this vertex-array-object must be bound before the glutWireSphere call
    glBindVertexArray(this->vao);

    glDrawElements(this->drawMode, this->indexCount, GL_UNSIGNED_INT, 0);
    // GLUT: unbind vertex-array-object
    glBindVertexArray(0);
}

void VAOBuilder::addVertex(glm::vec3 vertex) {
    this->vertices.push_back(vertex);
}

void VAOBuilder::addNormal(glm::vec3 normal) {
    this->normals.push_back(normal);
}

void VAOBuilder::addNormalFromVert() {
    this->normals.push_back(glm::normalize(this->vertices.back()));
}

void VAOBuilder::addCurrentIndex() {
    this->indices.push_back((GLuint) (this->vertices.size() - 1));
}

void VAOBuilder::addIndex(int idx) {
    this->indices.push_back((GLuint) idx);
}

void VAOBuilder::addIndices(std::vector<int> indices) {
    for (int idx : indices)
        this->indices.push_back((GLuint) idx);
}

void VAOBuilder::build(int shaderHandle, VertexArrayObject *vertexArrayObject) {
    GLuint pos;
    // Step 0: Create vertex array object.
    glGenVertexArrays(1, &vertexArrayObject->vao);
    glBindVertexArray(vertexArrayObject->vao);

    // Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
    glGenBuffers(1, &vertexArrayObject->positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject->positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(shaderHandle, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 2: Create vertex buffer object for normal attribute and bind it to...
    glGenBuffers(1, &vertexArrayObject->normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject->normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

    // Bind it to normal.
    pos = glGetAttribLocation(shaderHandle, "normal");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 3: Create vertex buffer object for indices. No binding needed here.
    glGenBuffers(1, &vertexArrayObject->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayObject->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Unbind vertex array object (back to default).
    glBindVertexArray(0);

    vertexArrayObject->indexCount = (int)indices.size();

    vertexArrayObject->model = glm::mat4(1.0f);
}
