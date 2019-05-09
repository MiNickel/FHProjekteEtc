#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/transform.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"
#include "glm/gtx/string_cast.hpp"

// Standard window width
const int WINDOW_WIDTH = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

float radius = 0.5f;

float eyeY = 3.0f;

float xdegree = 0.0f;
float ydegree = 0.0f;
float zdegree = 0.0f;

int rotateMode = 0;

/*
Struct to hold data for object rendering.
*/
class Object
{
public:
	inline Object()
		: vao(0),
		positionBuffer(0),
		colorBuffer(0),
		indexBuffer(0)
	{}

	inline ~Object() { // GL context must exist on destruction
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteBuffers(1, &colorBuffer);
		glDeleteBuffers(1, &positionBuffer);
	}

	GLuint vao;        // vertex-array-object ID

	GLuint positionBuffer; // ID of vertex-buffer: position
	GLuint colorBuffer;    // ID of vertex-buffer: color

	GLuint indexBuffer;    // ID of index-buffer

	glm::mat4x4 model; // model matrix
};

Object triangle;
Object quad;
Object cube;
Object octahedon;
Object axis;


void renderAxis() {
	// Create mvp.
	glm::mat4x4 mvp = projection * view * axis.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(axis.vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderTriangle()
{
	
	//triangle.model = glm::rotate(triangle.model, degree, glm::vec3(0, 1, 0));
	// Create mvp.
	glm::mat4x4 mvp = projection * view * triangle.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(triangle.vao);
	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderQuad()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * quad.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(quad.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderCube() {
	glm::mat4x4 mvp = projection * view * cube.model;

	program.use();
	program.setUniform("mvp", mvp);

	glBindVertexArray(cube.vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderOctahedon() {
	glm::mat4x4 mvp = projection * view * octahedon.model;

	program.use();
	program.setUniform("mvp", mvp);

	glBindVertexArray(octahedon.vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void initAxis() {

	const std::vector<glm::vec3> vertices = { { 0, -4, 0 }, { 0, 4, 0 }, {4, 0, 0}, {-4, 0, 0 }, {0, 0, -4}, {0, 0, 4} };

	const std::vector<glm::vec3> colors = { { 1, 0, 0 },{ 1, 0, 0 }, { 1, 0, 0 },{ 1, 0, 0 } };

	const std::vector<GLushort> indices = { 0, 1, 2, 3, 4, 5 };

	GLuint programId = program.getHandle();
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
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &axis.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axis.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	axis.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

void initTriangle1()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	std::vector<glm::vec3> vertices = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) };
	std::vector<glm::vec3> colors = { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) };
	std::vector<GLushort>  indices = { };

	glm::vec3 vertex1 = vertices.at(0);
	glm::vec3 vertex2 = vertices.at(1);
	glm::vec3 vertex3 = vertices.at(2);

	glm::vec3 vertex4 = 0.5f * vertex1 + 0.5f * vertex2;
	glm::vec3 vertex5 = 0.5f * vertex1 + 0.5f * vertex3;
	glm::vec3 vertex6 = 0.5f * vertex2 + 0.5f * vertex3;

	vertices.push_back(vertex4);
	colors.push_back({ 1.0f, 1.0f, 1.0f });
	vertices.push_back(vertex5);
	colors.push_back({ 1.0f, 1.0f, 1.0f });
	vertices.push_back(vertex6);
	colors.push_back({ 1.0f, 1.0f, 1.0f });

	indices = { 0, 3, 4, 3, 1, 5, 4, 5, 2, 3, 4, 5 };

	GLuint programId = program.getHandle();
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
	triangle.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

void initTriangle2(glm::vec3 x, glm::vec3 y, glm::vec3 z)
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	std::vector<glm::vec3> vertices = { x, y, z };
	std::vector<glm::vec3> colors = { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) };
	std::vector<GLushort>  indices = { };

	glm::vec3 vertex0 = vertices.at(0);
	glm::vec3 vertex1 = vertices.at(1);
	glm::vec3 vertex2 = vertices.at(2);

	glm::vec3 vertex3 = (2.0f/3.0f) * vertex0 + (1.0f / 3.0f) * vertex1;
	glm::vec3 vertex4 = (1.0f/3.0f) * vertex0 + (2.0f / 3.0f) * vertex1;
	glm::vec3 vertex5 = (2.0f/3.0f) * vertex0 + (1.0f / 3.0f) * vertex2;
	glm::vec3 vertex6 = (1.0f/3.0f) * vertex0 + (2.0f / 3.0f) * vertex2;
	glm::vec3 vertex7 = (2.0f/3.0f) * vertex1 + (1.0f / 3.0f) * vertex2;
	glm::vec3 vertex8 = (1.0f/3.0f) * vertex1 + (2.0f / 3.0f) * vertex2;
	glm::vec3 vertex9 = 0.5f * vertex4 + 0.5f * vertex6;

	vertices = { x, y, z, vertex3, vertex4, vertex5, vertex6, vertex7, vertex8, vertex9 };

	for (int i = 0; i < 7; i++) {
		colors.push_back({ 1.0f, 1.0f, 1.0f });
	}
	indices = { 0, 3, 5, 3, 4, 9, 9, 5, 6, 3, 5, 9, 4, 1, 7, 4, 9, 7, 7, 9, 8, 8, 6, 2, 8, 6, 9 };

	GLuint programId = program.getHandle();
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
	triangle.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	//triangle.model = glm::rotate(triangle.model, degree, glm::vec3(0, 1, 0));
}
void initQuad()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { -1.0f, 1.0f, 0.0f }, { -1.0, -1.0, 0.0 }, { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } };
	const std::vector<GLushort>  indices = { 0, 1, 2, 0, 2, 3 };

	GLuint programId = program.getHandle();
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

void initCube() {
	const std::vector<glm::vec3> vertices = { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f } };
	const std::vector<glm::vec3> colors{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } };
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3, 1, 5, 6, 1, 6, 2, 5, 4, 7, 5, 7, 6, 0, 4, 7, 0, 7, 3, 3, 7, 6, 3, 6, 2, 0, 4, 5, 0, 5, 1 };


	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &cube.vao);
	glBindVertexArray(cube.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &cube.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cube.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &cube.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cube.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &cube.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	cube.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

void initOctahedon() {
	//const int index[24] = { 0, 1, 3, 0, 1, 4, 0, 2, 3, 0, 2, 4, 5, 1, 3, 5, 1, 4, 5, 2, 3, 5, 2, 4 };

	const std::vector<glm::vec3> vertices = { {0.0f, 0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}, {-0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.5f}, {0.0f, 0.0f, -0.5f}, {0.0f, -0.5f, 0.0f} };
	const std::vector<glm::vec3> colors = { {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f} };
	const std::vector<GLushort> indices = { 0, 1, 3, 0, 1, 4, 0, 2, 3, 0, 2, 4, 5, 1, 3, 5, 1, 4, 5, 2, 3, 5, 2, 4 };

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &octahedon.vao);
	glBindVertexArray(octahedon.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &octahedon.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, octahedon.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &octahedon.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, octahedon.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &octahedon.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, octahedon.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	octahedon.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	octahedon.model = glm::rotate(octahedon.model, xdegree, glm::vec3(1, 0, 0));
    octahedon.model = glm::rotate(octahedon.model, ydegree, glm::vec3(0, 1, 0));
	octahedon.model = glm::rotate(octahedon.model, zdegree, glm::vec3(0, 0, 1));
	
	
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, eyeY);
	glm::vec3 center(0.0f, 0.0f, 1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);

	// Create a shader program and set light direction.
	if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX)) {
		std::cerr << program.log();
		return false;
	}

	if (!program.compileShaderFromFile("shader/simple.frag", cg::GLSLShader::FRAGMENT)) {
		std::cerr << program.log();
		return false;
	}

	if (!program.link()) {
		std::cerr << program.log();
		return false;
	}

	// Create all objects.
	initAxis();
	//initTriangle2(glm::vec3(0.0f, radius, 0.0f), glm::vec3(-radius, 0.0f, 0.5f), glm::vec3(radius, 0.0f, 0.5f));
	//initTriangle2(glm::vec3(0.0f, radius, 0.0f), glm::vec3(-radius, 0.0f, 0.5f), glm::vec3(radius, 0.0f, -0.5f));
	// initQuad();
	 initOctahedon();

	return true;
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderAxis();
	//renderTriangle();
	//renderQuad();
	renderOctahedon();
}

void glutDisplay()
{
	render();
	glutSwapBuffers();
}

/*
 Resize callback.
 */
void glutResize(int width, int height)
{
	// Division by zero is bad...
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float)width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
void glutKeyboard(unsigned char keycode, int x, int y)
{
	switch (keycode) {
	case 27: // ESC
		glutDestroyWindow(glutID);
		return;

	case '+':
		// do something
		break;
	case '-':
		// do something
		break;
	case 'x':
		rotateMode = 0;
		xdegree += 0.01f;
		init();
		// do something
		break;
	case 'y':
		rotateMode = 1;
		ydegree += 0.01f;
		init();
		// do something
		break;
	case 'z':
		rotateMode = 2;
		zdegree += 0.01f;
		init();
		// do something
		break;
	case 'a':
		// Zoom in
		if (eyeY > 1.3f)
		eyeY -= 0.1f;
		init();
		break;
	case 's':
		// Zoom out
		if (eyeY < 4.5f)
		eyeY += 0.1f;
		init();
		break;
	}
	glutPostRedisplay();
	
}

int main(int argc, char** argv)
{
	
	// GLUT: Initialize freeglut library (window toolkit).
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);

	// GLUT: Create a window and opengl context (version 4.3 core profile).
	glutInitContextVersion(4, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	

	glutCreateWindow("Aufgabenblatt 01");
	glutID = glutGetWindow();

	// GLEW: Load opengl extensions
	//glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		return -1;
	}
#if _DEBUG
	if (glDebugMessageCallback) {
		std::cout << "Register OpenGL debug callback " << std::endl;
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(cg::glErrorVerboseCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE,
			GL_DONT_CARE,
			GL_DONT_CARE,
			0,
			nullptr,
			true); // get all debug messages
	}
	else {
		std::cout << "glDebugMessageCallback not available" << std::endl;
	}
#endif

	// GLUT: Set callbacks for events.
	glutReshapeFunc(glutResize);
	glutDisplayFunc(glutDisplay);
	//glutIdleFunc   (glutDisplay); // redisplay when idle

	glutKeyboardFunc(glutKeyboard);

	// init vertex-array-objects.
	bool result = init();
	if (!result) {
		return -2;
	}

	// GLUT: Loop until the user closes the window
	// rendering & event handling
	glutMainLoop();

	// Cleanup in destructors:
	// Objects will be released in ~Object
	// Shader program will be released in ~GLSLProgram

	return 0;
}
