#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"
#include "OBJLoader.h"
#include "MeshObject.h"

// Standard window width
const int WINDOW_WIDTH = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram shader_noLight(false);
cg::GLSLProgram shader_flat(false);
cg::GLSLProgram shader_gouraud(false);
cg::GLSLProgram shader_phong(false);
cg::GLSLProgram *shader;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

/*
Struct to hold data for object rendering.
*/
struct Object {
    inline Object()
            : vao(0),
              positionBuffer(0),
              colorBuffer(0),
              indexBuffer(0),
              yAxis(0) {}

    /* IDs for several buffers. */
    GLuint vao;

    GLuint positionBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;

    GLuint yAxis;

    /* Model matrix */
    glm::mat4x4 model;
};

Object triangle;
Object quad;
Object wiresphere; // GLUT geometry
Object axis; // GLUT geometry
MeshObject *meshObjectSun;
MeshObject *meshObjectShip;
glm::vec3 eye = glm::vec3(0.0f, 0.0f, 8.0f);
glm::mat4x4 projectionMod = glm::mat4(1.0f);
unsigned int lightsource = 0;

void setShaderUniforms(glm::mat4 mvp, glm::mat4 modifiedModel, glm::vec3 color) {
    shader->use();
    shader->setUniform("mvp", mvp);
    if (lightsource == 0)
        shader->setUniform("lightDirection", glm::vec4(0, 1, 0, 0));
    else
        shader->setUniform("lightDirection", glm::vec4(eye, 1));
    shader->setUniform("modelMatrix", modifiedModel);
    shader->setUniform("normalMatrix", glm::inverseTranspose(glm::mat3(modifiedModel)));


    shader->setUniform("eyePos", eye);
    shader->setUniform("light.ld", color);
    shader->setUniform("light.ls", {1.0f, 0.0f, 0.0f});
    shader->setUniform("light.la", {0.0f, 0.0f, 0.2f});

    shader->setUniform("material.kd", 0.65f);
    shader->setUniform("material.ks", 0.35f);
    shader->setUniform("material.ka", 0.0f);
    shader->setUniform("material.shinyness", 200.0f);
}

void renderAxis(glm::vec3 color) {
    // Create mvp.
    glm::mat4x4 mvp = projection * view * axis.model * projectionMod;

    // Bind the shader program and set uniform(s).
    shader_noLight.use();
    shader_noLight.setUniform("mvp", mvp);
    shader_noLight.setUniform("color", color);

    // Bind vertex array object so we can render the axis
    glBindVertexArray(axis.vao);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}

void renderTriangle() {
    // Create mvp.
    glm::mat4x4 mvp = projection * view * triangle.model;

    // Bind the shader program and set uniform(s).
    shader_noLight.use();
    shader_noLight.setUniform("mvp", mvp);

    // Bind vertex array object so we can render the 1 triangle.
    glBindVertexArray(triangle.vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}

void renderQuad() {
    // Create mvp.
    glm::mat4x4 mvp = projection * view * quad.model;

    // Bind the shader program and set uniform(s).
    shader_noLight.use();
    shader_noLight.setUniform("mvp", mvp);

    // Bind vertex array object so we can render the 2 triangles.
    glBindVertexArray(quad.vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}

void renderWireSphere(Object *object, glm::vec3 color) {
    // Create mvp.
    glm::mat4x4 modifiedModel = object->model * projectionMod;
    glm::mat4x4 mvp = projection * view * modifiedModel;


    setShaderUniforms(mvp, modifiedModel, color);

    // GLUT: bind vertex-array-object
    // this vertex-array-object must be bound before the glutWireSphere call
    glBindVertexArray(object->vao);

    glutSolidSphere(1.0, 10, 10);
    //    glutWireSphere(1.0, 10, 10);
    // GLUT: unbind vertex-array-object
    glBindVertexArray(0);
}

void renderMeshObject(MeshObject *object, glm::vec3 color) {
    object->render(projection, view, projectionMod, &setShaderUniforms, color);
}

void initAxis() {
    const std::vector<glm::vec3> vertices = {{-0.1, -2, 0},
                                             {-0.1, 2,  0},
                                             {0.1,  2,  0},
                                             {0.1,  -2, 0},
                                             {0,    -2, -0.1},
                                             {0,    2,  -0.1},
                                             {0,    2,  0.1},
                                             {0,    -2, 0.1}};
    const std::vector<glm::vec3> colors = {{1, 1, 1},
                                           {1, 1, 1},
                                           {1, 1, 1},
                                           {1, 1, 1},
                                           {1, 1, 1},
                                           {1, 1, 1},
                                           {1, 1, 1},
                                           {1, 1, 1}};
    const std::vector<GLushort> indices = {0, 1, 2, 0, 2, 3,
                                           4, 5, 6, 4, 6, 7};

    GLuint programId = shader_noLight.getHandle();
    GLuint pos;

    // Step 0: Create vertex array object.
    glGenVertexArrays(1, &axis.vao);
    glBindVertexArray(axis.vao);

    // Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
    glGenBuffers(1, &axis.positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, axis.positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 2: Create vertex buffer object for color attribute and bind it to...
    glGenBuffers(1, &axis.colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, axis.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
//    pos = glGetAttribLocation(programId, "color");
//    glEnableVertexAttribArray(pos);
//    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 3: Create vertex buffer object for indices. No binding needed here.
    glGenBuffers(1, &axis.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axis.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Unbind vertex array object (back to default).
    glBindVertexArray(0);

    // Modify model matrix.
    axis.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

void initTriangle() {
    // Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
    const std::vector<glm::vec3> vertices = {glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f),
                                             glm::vec3(1.0f, 1.0f, 0.0f)};
    const std::vector<glm::vec3> colors = {glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                                           glm::vec3(0.0f, 0.0f, 1.0f)};
    const std::vector<GLushort> indices = {0, 1, 2};

    GLuint programId = shader_noLight.getHandle();
    GLuint pos;

    // Step 0: Create vertex array object.
    glGenVertexArrays(1, &triangle.vao);
    glBindVertexArray(triangle.vao);

    // Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
    glGenBuffers(1, &triangle.positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangle.positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 2: Create vertex buffer object for color attribute and bind it to...
    glGenBuffers(1, &triangle.colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangle.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 3: Create vertex buffer object for indices. No binding needed here.
    glGenBuffers(1, &triangle.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Unbind vertex array object (back to default).
    glBindVertexArray(0);

    // Modify model matrix.
    triangle.model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.0f, 0.0f));
}

void initQuad() {
    // Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
    const std::vector<glm::vec3> vertices = {{-1.0f, 1.0f,  0.0f},
                                             {-1.0,  -1.0,  0.0},
                                             {1.0f,  -1.0f, 0.0f},
                                             {1.0f,  1.0f,  0.0f}};
    const std::vector<glm::vec3> colors = {{1.0f, 0.0f, 0.0f},
                                           {0.0f, 1.0,  1.0f},
                                           {0.0f, 1.0f, 0.0f},
                                           {0.0f, 0.0f, 1.0f}};
    const std::vector<GLushort> indices = {0, 1, 2, 0, 2, 3};

    GLuint programId = shader_noLight.getHandle();
    GLuint pos;

    // Step 0: Create vertex array object.
    glGenVertexArrays(1, &quad.vao);
    glBindVertexArray(quad.vao);

    // Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
    glGenBuffers(1, &quad.positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad.positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 2: Create vertex buffer object for color attribute and bind it to...
    glGenBuffers(1, &quad.colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 3: Create vertex buffer object for indices. No binding needed here.
    glGenBuffers(1, &quad.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Unbind vertex array object (back to default).
    glBindVertexArray(0);

    // Modify model matrix.
    quad.model = glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, 0.0f, 0.0f));
}

void initWireSphere(Object *wireSphere) {
    // set attribute locations (of shader) for GLUT
    GLuint programId = shader->getHandle();
    // position attribute to variable "position"
    glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
    // normal attribute to variable "color"
    // this creates a colorful sphere :-)
    glutSetVertexAttribNormal(glGetAttribLocation(programId, "normal"));
    // create a vertex-array-object for GLUT geometry
    glGenVertexArrays(1, &wireSphere->vao);

    // Modify model matrix.
    wireSphere->model = glm::mat4(1.0f);
}

void setView() {
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    view = glm::lookAt(eye, center, up);
}

bool initShader(cg::GLSLProgram *shader, const char *path) {
    size_t pathLen = strlen(path);
    char *pathBuffer = new char[pathLen + 5];
    strcpy(pathBuffer, path);
    strcat(pathBuffer, ".vert");
    if (!shader->compileShaderFromFile(pathBuffer, cg::GLSLShader::VERTEX)) {
        std::cerr << shader->log();
        return false;
    }

    pathBuffer = new char[pathLen + 5];
    strcpy(pathBuffer, path);
    strcat(pathBuffer, ".frag");
    if (!shader->compileShaderFromFile(pathBuffer, cg::GLSLShader::FRAGMENT)) {
        std::cerr << shader->log();
        return false;
    }

    if (!shader->link()) {
        std::cerr << shader->log();
        return false;
    }
    return true;
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init() {
    // OpenGL: Set "background" color and enable depth testing.
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Construct view matrix.
//    glm::vec3 eye(0.0f, 8.0f, 8.0f);
//    glm::vec3 center(0.0f, 0.0f, 0.0f);
//    glm::vec3 up(0.0f, 1.0f, 0.0f);
//
//    view = glm::lookAt(eye, center, up);
    setView();

    // Create a shader program and set light direction.
    initShader(&shader_noLight, "shader/simple");
    initShader(&shader_flat, "shader/flat");
    initShader(&shader_phong, "shader/phong");

    shader = &shader_phong;

    // Create all objects.
    //initTriangle();
    //initQuad();
    // GLUT: create vertex-array-object for glut geometry, the "default"
    // must be bound before the glutWireSphere call

    HalfEdgeList *halfEdgeList = loadIntoHEL("objs/stanford_bunny_closed.obj");
    halfEdgeList->fixNormals();
    meshObjectSun = new MeshObject(shader->getHandle(), halfEdgeList);

    halfEdgeList = loadIntoHEL("objs/gunship.obj");
    meshObjectShip = new MeshObject(shader->getHandle(), halfEdgeList);

    initWireSphere(&wiresphere);
    initAxis();

    return true;
}

/*
 Release object resources.
*/
void releaseObject(Object &obj) {
    glDeleteVertexArrays(1, &obj.vao);
    glDeleteBuffers(1, &obj.indexBuffer);
    glDeleteBuffers(1, &obj.colorBuffer);
    glDeleteBuffers(1, &obj.positionBuffer);
    if (&obj.yAxis > 0)
        glDeleteVertexArrays(1, &obj.yAxis);
}

/*
 Release resources on termination.
 */
void release() {
    // Shader program will be released upon program termination.

    //releaseObject(triangle);
    //releaseObject(quad);
    releaseObject(wiresphere);
    releaseObject(axis);
}

/*
 Rendering.
 */
float prevTime = 0;
float systemRotation = 0;
float systemRotationSpeed = 1.0f;
float yOffset_system = 0;
float yOffset_planet1 = 0;
float tilt_planet2 = 45.0f;
glm::vec3 sunRotation = {0, 0, 0};

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float time = glutGet(GLUT_ELAPSED_TIME);
    if ((time - prevTime) > 50.0) {
        systemRotation += 1.5f * systemRotationSpeed;
        prevTime = time;
    }

    projectionMod = glm::mat4(1.0f);
    projectionMod = glm::translate(projectionMod, {0, yOffset_system, 0});
    //renderWireSphere(&wiresphere, {1, 1, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(sunRotation.z), {0, 0, 1});
    projectionMod = glm::rotate(projectionMod, glm::radians(sunRotation.y), {0, 1, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(sunRotation.x), {1, 0, 0});
    float sunScale = meshObjectSun->getUniformScaleFactor();
    projectionMod = glm::scale(projectionMod, {sunScale, sunScale, sunScale});
    renderMeshObject(meshObjectSun, {1, 1, 0});
    renderAxis({1, 1, 0});


    projectionMod = glm::mat4(1.0f);
    projectionMod = glm::translate(projectionMod, {0, yOffset_system, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, 1, 0});
    projectionMod = glm::translate(projectionMod, {9, 0, 0});
    float shipScale = meshObjectShip->getUniformScaleFactor() * 0.7;
    projectionMod = glm::scale(projectionMod, {shipScale, shipScale, shipScale});
    projectionMod = glm::rotate(projectionMod, glm::radians(180.0f), {0, 1, 0});
    renderMeshObject(meshObjectShip, {0.8, 0.8, 1});

    projectionMod = glm::mat4(1.0f);
    projectionMod = glm::translate(projectionMod, {0, yOffset_system + yOffset_planet1, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, 1, 0});
    projectionMod = glm::translate(projectionMod, {0, 0, 5});
    projectionMod = glm::scale(projectionMod, {0.5f, 0.5f, 0.5f});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, 1, 0});
    renderWireSphere(&wiresphere, {0, 0, 1});
    renderAxis({0, 0, 1});

    for (int i = 0; i < 3; i++) {
        glm::mat4x4 moon_angle = glm::rotate(glm::mat4(1.0f), glm::radians(systemRotation + i * 120.0f), {0, 1, 0});
        moon_angle = glm::translate(moon_angle, {2, 0, 0});
        moon_angle = glm::scale(moon_angle, {0.5f, 0.5f, 0.5f});
        projectionMod *= moon_angle;
        renderWireSphere(&wiresphere, {0.3f, 0.3f, 0.3f});
        projectionMod /= moon_angle;
    }


    projectionMod = glm::mat4(1.0f);
    projectionMod = glm::translate(projectionMod, {0, yOffset_system, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, 1, 0});
    projectionMod = glm::translate(projectionMod, {-12, 0, 0});
    projectionMod = glm::scale(projectionMod, {0.5f, 0.5f, 0.5f});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, -1, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(tilt_planet2), {0, 0, 1});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, 1, 0});
    renderWireSphere(&wiresphere, {1, 0, 0});
    renderAxis({1, 0, 0});

    for (int j = -1; j <= 1; j++)
        for (int i = 0; i < (j == 0 ? 2 : 4); i++) {
            glm::mat4x4 moon_angle = glm::translate(glm::mat4(1.0f), {0, j * 1.5f, 0});
            moon_angle = glm::rotate(moon_angle, glm::radians(i * (j == 0 ? 180.0f : 90.0f)), {0, 1, 0});
            moon_angle = glm::translate(moon_angle, {2, 0, 0});
            moon_angle = glm::scale(moon_angle, {0.5f, 0.5f, 0.5f});
            projectionMod *= moon_angle;
            renderWireSphere(&wiresphere, {0.3f, 0.3f, 0.3f});
            projectionMod /= moon_angle;
        }
}

void glutDisplay() {
    GLCODE(render());
    glutSwapBuffers();
}

/*
 Resize callback.
 */
void glutResize(int width, int height) {
    // Division by zero is bad...
    height = height < 1 ? 1 : height;
    glViewport(0, 0, width, height);

    // Construct projection matrix.
    projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
void glutKeyboard(unsigned char keycode, int x, int y) {
    glm::mat4x4 rot;
    switch (keycode) {
        case 27: // ESC
            glutDestroyWindow(glutID);
            return;
        case 'x':
            sunRotation.x += 5;
            break;
        case 'y':
            sunRotation.y += 5;
            break;
        case 'z':
            sunRotation.z += 5;
            break;

        case 'b':
            meshObjectSun->showBounds = !meshObjectSun->showBounds;
            meshObjectShip->showBounds = !meshObjectShip->showBounds;
            break;
        case 'n':
            meshObjectSun->showVn = !meshObjectSun->showVn;
            meshObjectShip->showVn = !meshObjectShip->showVn;
            break;
        case 'h':
            meshObjectSun->showFn = !meshObjectSun->showFn;
            meshObjectShip->showFn = !meshObjectShip->showFn;
            break;

        case 's':
            shader = &shader_flat;
            break;
        case 'S':
            shader = &shader_phong;
            break;


        case 't':
        case 'T':
            yOffset_system += keycode == 't' ? -0.5f : 0.5f;
            break;
        case 'l':
        case 'L':
            yOffset_planet1 += keycode == 'l' ? -0.5f : 0.5f;
            break;
        case 'p':
        case 'P':
            tilt_planet2 += keycode == 'p' ? -5.0f : 5.0f;
            break;
        case 'w':
        case 'W':
            systemRotationSpeed += keycode == 'w' ? -0.25f : 0.25f;
            break;

        case '1': // Change lightsource
            if (lightsource == 0)
                lightsource = 1;
            else
                lightsource = 0;
            break;

        case '8':
        case '2':
        case '9':
        case '3': // Manipulate Camera
            eye.y += keycode == '8' ? 1 : keycode == '2' ? -1 : 0;
            if (eye.y < 0)
                eye.y = 0;
            eye.z += keycode == '9' ? 1 : keycode == '3' ? -1 : 0;
            if (eye.z < 1)
                eye.z = 1;
            setView();
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {

    // GLUT: Initialize freeglut library (window toolkit).
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(40, 40);
    glutInit(&argc, argv);

    // GLUT: Create a window and opengl context (version 4.3 core profile).
    glutInitContextVersion(4, 2);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutCreateWindow("Aufgabenblatt 04");
    glutID = glutGetWindow();

    // GLEW: Load opengl extensions
    glewExperimental = GL_TRUE;
    GLenum result = glewInit();

    if (result != GLEW_OK) {
        return -1;
    }

    // GLUT: Set callbacks for events.
    glutReshapeFunc(glutResize);
    glutDisplayFunc(glutDisplay);
    glutIdleFunc(glutDisplay); // redisplay when idle

    glutKeyboardFunc(glutKeyboard);

    // init vertex-array-objects.
    {
        GLCODE(bool result = init());
        if (!result) {
            release();
            return -2;
        }
    }

    // GLUT: Loop until the user closes the window
    // rendering & event handling
    glutMainLoop();

    // Cleanup everything on termination.
    release();

    return 0;
}
