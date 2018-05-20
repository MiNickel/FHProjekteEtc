#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
int glutID = 0;
cg::GLSLProgram program;
glm::mat4x4 view;
glm::mat4x4 projection;
float zNear = 0.1f;
float zFar = 100.0f;

struct Object
{
	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;
	glm::mat4x4 model;
};

Object cube;
Object axes;

GLfloat rotateX;
GLfloat rotateY;
GLfloat rotateZ;
GLfloat scaleX = 1.0f;
GLfloat scaleY = 1.0f;
GLfloat scaleZ = 1.0f;

void renderCube()
{
	// Create mvp.
	glm::mat4 model(cube.model);

	model = glm::rotate(model, rotateX, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotateY, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotateZ, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	glm::mat4x4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(cube.vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderAxes()
{
	glm::mat4 model(axes.model);

	/*
	model = glm::rotate(model, rotateX, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotateY, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotateZ, glm::vec3(0.0f, 0.0f, 1.0f));
	*/
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	glm::mat4x4 mvp = projection * view * model;

	program.use();
	program.setUniform("mvp", mvp);

	glBindVertexArray(axes.vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void initAxes()
{
	const std::vector<glm::vec3> vertices = {
		{ 0,-2,0 },{ 0,2,0 },
	{ -2,0,0 },{ 2,0,0 },
	{ 0,0,-2 },{ 0,0,2 }
	};

	const std::vector<glm::vec3> colors = {
		{ 1,1,1 },{ 1,1,1 },
	{ 1,1,1 },{ 1,1,1 },
	{ 1,1,1 },{ 1,1,1 }
	};

	const std::vector<GLushort> indices = {
		0,1,2,3,4,5
	};

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &axes.vao);
	glBindVertexArray(axes.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &axes.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, axes.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &axes.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, axes.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &axes.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axes.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix-
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(1.25f, 0.0f, 0.0f));

	axes.model = model;
}

void initCube()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = {
		//{ -1.0f, 1.0f, 0.0f }, { -1.0, -1.0, 0.0 }, { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }
		{ 1,1,1 },{ -1,1,1 },{ -1,-1,1 },{ 1,-1,1 },
	{ 1,1,1 },{ 1,-1,1 },{ 1,-1,-1 },{ 1,1,-1 },
	{ 1,1,1 },{ 1,1,-1 },{ -1,1,-1 },{ -1,1,1 },
	{ -1,-1,-1 },{ -1,1,-1 },{ 1,1,-1 },{ 1,-1,-1 },
	{ -1,-1,-1 },{ -1,-1,1 },{ -1,1,1 },{ -1,1,-1 },
	{ -1,-1,-1 },{ 1,-1,-1 },{ 1,-1,1 },{ -1,-1,1 }
	};
	const std::vector<glm::vec3> colors = {
		//{ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }
		{ 1,0,0 },{ 1,0,0 },{ 1,0,0 },{ 1,0,0 },
	{ 0,1,0 },{ 0,1,0 },{ 0,1,0 },{ 0,1,0 },
	{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },
	{ 1,1,0 },{ 1,1,0 },{ 1,1,0 },{ 1,1,0 },
	{ 1,0,1 },{ 1,0,1 },{ 1,0,1 },{ 1,0,1 },
	{ 0,1,1 },{ 0,1,1 },{ 0,1,1 },{ 0,1,1 }
	};
	//const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };
	const std::vector<GLushort> indices = {
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23
	};
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

	// Modify model matrix-
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(1.25f, 0.0f, 0.0f));

	cube.model = model;
}

/*
Initialization. Should return true if everything is ok and false if something went wrong.
*/
bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, 4.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);

	// Create a shader program and set light direction.
	if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX))
	{
		std::cerr << program.log();
		return false;
	}

	if (!program.compileShaderFromFile("shader/simple.frag", cg::GLSLShader::FRAGMENT))
	{
		std::cerr << program.log();
		return false;
	}

	if (!program.link())
	{
		std::cerr << program.log();
		return false;
	}

	// Create objects.
	initCube();
	initAxes();

	return true;
}

/*
Release object resources.
*/
void releaseObject(Object& obj)
{
	glDeleteVertexArrays(1, &obj.vao);
	glDeleteBuffers(1, &obj.indexBuffer);
	glDeleteBuffers(1, &obj.colorBuffer);
	glDeleteBuffers(1, &obj.positionBuffer);
}

/*
Release resources on termination.
*/
void release()
{
	// Shader program will be released upon program termination.
	releaseObject(cube);
}

/*
Rendering.
*/
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderCube();
	renderAxes();
}

void glutDisplay()
{
	GLCODE(render());
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
	switch (keycode)
	{
	case 27: // ESC
		glutDestroyWindow(glutID);
		return;

	case 'a':
		scaleX += 0.01;
		scaleY += 0.01;
		scaleZ += 0.01;
		break;
	case 's':
		scaleX -= 0.01;
		scaleY -= 0.01;
		scaleZ -= 0.01;

		if (scaleX < 0) {
			scaleX = 0;
		}

		if (scaleY < 0) {
			scaleY = 0;
		}

		if (scaleZ < 0) {
			scaleZ = 0;
		}

		break;
	case 'x':
		rotateX += 0.1;
		break;
	case 'y':
		rotateY += 0.1;
		break;
	case 'z':
		rotateZ += 0.1;
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
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();

	if (result != GLEW_OK) {
		return -1;
	}

	// GLUT: Set callbacks for events.
	glutReshapeFunc(glutResize);
	glutDisplayFunc(glutDisplay);
	//glutIdleFunc   (glutDisplay); // redisplay when idle

	glutKeyboardFunc(glutKeyboard);

	// Init VAO.
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

	// Clean up everything on termination.
	release();

	return 0;
}