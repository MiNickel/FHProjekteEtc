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

// Standard window width
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar  = 100.0f;

GLfloat rotateZ = 45;
GLfloat rotateX = 30;
GLfloat rotateY;
GLfloat rotateY2;
GLfloat cameraYPos = 0.0f;
GLfloat cameraZPos = 15.0f;
GLfloat planet1YPos = 0.0f;
GLfloat rotationSpeed = 0.001f;

glm::vec4 lightDirection(0.0, -1.0, 0.0, 0);

char* fragShader = "shader/flatShading.frag";
char* vertShader = "shader/flatShading.vert";

int shaderBool = 0;



glm::vec3 eye;

glm::vec3 material(1.0, 1.0, 0.0);
float shine = 0.5;
glm::vec3 ambienteLight(1.0, 1.0, 1.0);

/*
Struct to hold data for object rendering.
*/
struct Object
{
	inline Object ()
		: vao(0),
		positionBuffer(0),
		colorBuffer(0),
		indexBuffer(0)
	{}

	/* IDs for several buffers. */
	GLuint vao;

	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	/* Model matrix */
	glm::mat4x4 model;
};

Object triangle;
Object quad;
Object axesPlanet1;
Object axesPlanet2;
Object sunAxes;
Object wireSphere; // GLUT geometry
Object sun;
Object planet1;
Object planet2;
Object moonPlanet1;
Object moonPlanet2;




void renderWireSphere ()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * wireSphere.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(wireSphere.vao);

    //glLineWidth(1.0f);
    glutWireSphere(1.0, 10, 10);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderSun()
{
	glm::mat4 model(sun.model);
	// Create mvp.
	glm::mat4x4 mvp = projection * view * sun.model;
	
	glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));
	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);
	program.setUniform("modelMatrix", model);
	program.setUniform("nm", nm);
	program.setUniform("camera", eye);
	program.setUniform("lightDirection", lightDirection);
	program.setUniform("material", material);
	program.setUniform("shine", shine);
	program.setUniform("ambientLight", ambienteLight);
	


	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(sun.vao);
	//glLineWidth(1.0f);
	glutSolidSphere(2.0, 20, 20);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderMoonPlanet1(float x, float y, float z)
{
	glm::mat4x4 model(moonPlanet1.model);
	glm::mat4x4 planetModel(planet1.model);
	glm::mat4 planetAxes1(axesPlanet1.model);
	glm::mat4 sunModel(sun.model);


	
	
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(sunModel, rotateY, glm::vec3(0.0,1.0,0.0)) * glm::rotate(planetAxes1, rotateY, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(0.0f, planet1YPos, 0.0f));
	model = glm::translate(model, glm::vec3(x, y, z));
	
	
	
	
	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));
	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);
	program.setUniform("modelMatrix", model);
	program.setUniform("nm", nm);
	program.setUniform("camera", eye);
	program.setUniform("lightDirection", lightDirection);
	program.setUniform("material", material);
	program.setUniform("shine", shine);
	program.setUniform("ambientLight", ambienteLight);
	

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moonPlanet1.vao);

	//glLineWidth(1.0f);
	glutSolidSphere(0.3, 10, 10);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderMoonPlanet2(float x, float y, float z)
{
	glm::mat4x4 model(moonPlanet2.model);
	glm::mat4x4 planetModel(planet2.model);
	glm::mat4 planetAxes(axesPlanet2.model);
	glm::mat4 sunModel(sun.model);

	
	model = glm::rotate(sunModel, rotateY, glm::vec3(0.0,1.0,0.0))* glm::rotate(planetAxes, rotateY, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, rotateZ, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(x, y, z));
	
	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));
	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);
	program.setUniform("modelMatrix", model);
	program.setUniform("nm", nm);
	program.setUniform("camera", eye);
	program.setUniform("lightDirection", lightDirection);
	program.setUniform("material", material);
	program.setUniform("shine", shine);
	program.setUniform("ambientLight", ambienteLight);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moonPlanet2.vao);

	//glLineWidth(1.0f);
	glutSolidSphere(0.3, 10, 10);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderPlanet2(float x, float y, float z)
{
	glm::mat4x4 model(planet2.model);
	glm::mat4 planetAxes(axesPlanet2.model);
	glm::mat4 sunModel(sun.model);

	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, rotateZ, glm::vec3(0.0, 0.0, 1.0));
	model = glm::rotate(sunModel, rotateY, glm::vec3(0.0, 1.0, 0.0))*glm::rotate(planetAxes, rotateY, glm::vec3(0.0, 1.0, 0.0));
	
	
	
	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));
	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);
	program.setUniform("modelMatrix", model);
	program.setUniform("nm", nm);
	program.setUniform("camera", eye);
	program.setUniform("lightDirection", lightDirection);
	program.setUniform("material", material);
	program.setUniform("shine", shine);
	program.setUniform("ambientLight", ambienteLight);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(planet2.vao);

	//glLineWidth(1.0f);
	glutSolidSphere(0.7, 15, 15);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderPlanet1(float x, float y, float z)
{
	glm::mat4x4 model(planet1.model);
	glm::mat4 sunModel(sun.model);

	model = glm::rotate(sunModel, rotateY, glm::vec3(0.0,1.0,0.0));
	model = glm::translate(model, glm::vec3(x, y, z))* glm::translate(model, glm::vec3(0.0f, planet1YPos, 0.0f));
	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));
	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);
	program.setUniform("modelMatrix", model);
	program.setUniform("nm", nm);
	program.setUniform("camera", eye);
	program.setUniform("lightDirection", lightDirection);
	program.setUniform("material", material);
	program.setUniform("shine", shine);
	program.setUniform("ambientLight", ambienteLight);
	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(planet1.vao);

	//glLineWidth(1.0f);
	glutSolidSphere(0.7, 15, 15);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderSunAxe()
{
	glm::mat4 model(sunAxes.model);

	//model = glm::translate(model, glm::vec3(-2.0, 0.0, 0.0));

	glm::mat4x4 mvp = projection * view * model;

	program.use();
	program.setUniform("mvp", mvp);
//	program.setUniform("lightPosition", lightPosition);

	glBindVertexArray(sunAxes.vao);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderAxesPlanet1(float x, float y, float z)
{
	glm::mat4 model(axesPlanet1.model);
	glm::mat4 sunModel(sun.model);

	
	model = glm::rotate(sunModel, rotateY, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::translate(model, glm::vec3(0.0f, planet1YPos, 0.0f));
	//model = glm::translate(model, glm::vec3(0.0f, planet1YPos, 0.0f));

	glm::mat4x4 mvp = projection * view * model;

	program.use();
	program.setUniform("mvp", mvp);
//	program.setUniform("lightPosition", lightPosition);

	glBindVertexArray(axesPlanet1.vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderAxesPlanet2(float x, float y, float z)
{
	glm::mat4 model(axesPlanet2.model);
	glm::mat4 sunModel(sun.model);

	model = glm::rotate(sunModel, rotateY, glm::vec3(0.0, 1.0, 0.0))* glm::rotate(model, rotateZ, glm::vec3(0.0, 0.0, 1.0));
	
	
	
	
	glm::mat4x4 mvp = projection * view * model;

	program.use();
	program.setUniform("mvp", mvp);
//	program.setUniform("lightPosition", lightPosition);

	glBindVertexArray(axesPlanet2.vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void initWireSphere() 
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &wireSphere.vao);

	// Modify model matrix.
	wireSphere.model = glm::mat4(1.0f);
}

void initSun()
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &sun.vao);

	// Modify model matrix.
	glm::mat4 model(sun.model);

	model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));

	sun.model = model;
}

void initSunAxe()
{
	const std::vector<glm::vec3> vertices = {
	{ 0,-2,0 },{ 0,2,0 }
	};

	const std::vector<glm::vec3> colors = {
		{ 1,1,1 },{ 1,1,1 }
	};

	const std::vector<GLushort> indices = {
		0,1
	};

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &sunAxes.vao);
	glBindVertexArray(sunAxes.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &sunAxes.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, sunAxes.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &sunAxes.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, sunAxes.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &sunAxes.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sunAxes.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix-
	glm::mat4 model(1.0f);
	

	sunAxes.model = model;
}

void initAxesPlanet1()
{
	const std::vector<glm::vec3> vertices = {
		{ -2,0,0 },{ 2,0,0 },
	{ 0,-2,0 },{ 0,2,0 },
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
	glGenVertexArrays(1, &axesPlanet1.vao);
	glBindVertexArray(axesPlanet1.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &axesPlanet1.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, axesPlanet1.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &axesPlanet1.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, axesPlanet1.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &axesPlanet1.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axesPlanet1.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix-
	glm::mat4 model(1.0f);
	
	model = glm::translate(model, glm::vec3(5.0, 0.0, 0.0));
	axesPlanet1.model = model;
}

void initAxesPlanet2()
{
	const std::vector<glm::vec3> vertices = {
		{ -2,0,0 },{ 2,0,0 },
	{ 0,-2,0 },{ 0,2,0 },
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
	glGenVertexArrays(1, &axesPlanet2.vao);
	glBindVertexArray(axesPlanet2.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &axesPlanet2.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, axesPlanet2.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &axesPlanet2.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, axesPlanet2.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &axesPlanet2.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axesPlanet2.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix-
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(-10.0, 0.0, 0.0));
	axesPlanet2.model = model;
}

void initPlanet2()
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &planet2.vao);

	// Modify model matrix.
	planet2.model = glm::mat4(1.0f);
	
}

void initPlanet1()
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &planet1.vao);

	// Modify model matrix.
	glm::mat4 model(1.0f);

	//model = glm::translate(model, glm::vec3(7.0, 0.0, 0.0));

	planet1.model = model;
}

void initMoonPlanet1()
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moonPlanet1.vao);

	// Modify model matrix.
	glm::mat4 model(1.0f);
	moonPlanet1.model = model;
}

void initMoonPlanet2()
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moonPlanet2.vao);

	// Modify model matrix.
	glm::mat4 model(moonPlanet2.model);
	moonPlanet2.model = model;
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
	eye = glm::vec3(0.0f, cameraYPos, cameraZPos);
	glm::vec3 center(0.0f, cameraYPos, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);

	// Create a shader program and set light direction.
	if (!program.compileShaderFromFile(vertShader, cg::GLSLShader::VERTEX))
	{
		std::cerr << program.log();
		return false;
	}

	if (!program.compileShaderFromFile(fragShader, cg::GLSLShader::FRAGMENT))
	{
		std::cerr << program.log();
		return false;
	}
	
	if (!program.link())
	{
		std::cerr << program.log();
		return false;
	}

	// Create all objects.
	
	// GLUT: create vertex-array-object for glut geometry, the "default"
	// must be bound before the glutWireSphere call
	//initWireSphere();
	initSun();
	initSunAxe();
	initPlanet2();
	initPlanet1();
	initMoonPlanet1();
	initMoonPlanet2();
	initAxesPlanet1();
	initAxesPlanet2();

	

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

	//releaseObject(triangle);
	//releaseObject(quad);
	//releaseObject(wireSphere);
	releaseObject(sun);
	releaseObject(planet1);
	releaseObject(moonPlanet1);
	releaseObject(planet1);
	releaseObject(moonPlanet2);
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderSun();
	
	renderSunAxe();

	renderPlanet1(5.0, 0.0, 0.0);
	renderAxesPlanet1(5.0, 0.0, 0.0);
	renderMoonPlanet1(1.7, 0.0, -0.7);
	renderMoonPlanet1(-1.7, 0.0, -0.7);
	renderMoonPlanet1(0.0, 0.0, 1.7);

	renderPlanet2(-10.0, 0.0, 0.0);
	renderAxesPlanet2(-10.0, 0.0, 0.0);
	renderMoonPlanet2(-1.0, 1.5, -1.0);
	renderMoonPlanet2(-1.0, 1.5, 1.0);
	renderMoonPlanet2(1.0, 1.5, 1.0);
	renderMoonPlanet2(1.0, 1.5, -1.0);

	renderMoonPlanet2(1.5, 0.0, 0.0);
	renderMoonPlanet2(-1.5, 0.0, 0.0);

	renderMoonPlanet2(-1.0, -1.5, -1.0);
	renderMoonPlanet2(-1.0, -1.5, 1.0);
	renderMoonPlanet2(1.0, -1.5, 1.0);
	renderMoonPlanet2(1.0, -1.5, -1.0);
	
	rotateY += rotationSpeed;
}

void glutDisplay ()
{
   GLCODE(render());
   glutSwapBuffers();
}

/*
 Resize callback.
 */
void glutResize (int width, int height)
{
	// Division by zero is bad...
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
void glutKeyboard (unsigned char keycode, int x, int y)
{
	switch (keycode)
	{
	case 27: // ESC
		glutDestroyWindow(glutID);
		return;

	case 'w':
		if (rotationSpeed > 0.001f) {
			rotationSpeed -= 0.001f;
		}
		break;
	case 'W':
		if (rotationSpeed < 0.01f) {
			rotationSpeed += 0.001f;
		}
		break;
	case 't':
		cameraYPos -= 0.5f;
		init();
		break;
	case 'T':
		cameraYPos += 0.5f;
		init();
		break;
	case 'l':
		planet1YPos -= 0.5f;
		break;
	case 'L':
		planet1YPos += 0.5f;
		break;
	case 'p':
		if (rotateZ>0) {
			rotateZ -= 0.5;
		}
		break;
	case 'P':
		if (rotateZ<360) {
			rotateZ += 0.5;
		}
		break;
	case '1':
		if (shaderBool == 0) {
			lightDirection = glm::vec4(0.0, -1.0, 0.0, 0.0);
			shaderBool = 1;
		}
		else if (shaderBool == 1) {
			lightDirection = glm::vec4(0.0, cameraYPos, cameraZPos, 1.0);
			shaderBool = 0;
		}
		break;
	case '+':
		cameraZPos -= 0.3;
		init();
		break;
	case '-':
		cameraZPos += 0.3;
		init();
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// GLUT: Initialize freeglut library (window toolkit).
    glutInitWindowSize    (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40,40);
	glutInit(&argc, argv);

	// GLUT: Create a window and opengl context (version 4.3 core profile).
	glutInitContextVersion(4, 3);
	glutInitContextFlags  (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitDisplayMode   (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

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
	glutIdleFunc   (glutDisplay); // redisplay when idle
	

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
	glutMainLoop ();

	// Cleanup everything on termination.
	release();

	return 0;
}
