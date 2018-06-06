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
	
	// Create mvp.
	glm::mat4x4 mvp = projection * view * sun.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(sun.vao);
	
	//glLineWidth(1.0f);
	glutWireSphere(1.0, 20, 20);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderMoonPlanet1(float x, float y, float z)
{
	glm::mat4x4 model(moonPlanet1.model);
	glm::mat4x4 planetModel(planet1.model);

	model = glm::translate(model, glm::vec3(x, y, z));
	//model = glm::rotate(model, rotateX, glm::vec3(1.0f, 0.0f, 0.0f));
	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moonPlanet1.vao);

	//glLineWidth(1.0f);
	glutWireSphere(0.3, 10, 10);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderMoonPlanet2(float x, float y, float z)
{
	glm::mat4x4 model(moonPlanet2.model);
	glm::mat4x4 planetModel(planet1.model);

	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, rotateZ, glm::vec3(0.0f, 0.0f, 1.0f));
	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moonPlanet2.vao);

	//glLineWidth(1.0f);
	glutWireSphere(0.3, 10, 10);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderPlanet2(float x, float y, float z)
{
	glm::mat4x4 model(planet2.model);

	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, rotateZ, glm::vec3(0.0, 0.0, 1.0));
	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(planet2.vao);

	//glLineWidth(1.0f);
	glutWireSphere(0.7, 15, 15);

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderPlanet1(float x, float y, float z)
{
	glm::mat4x4 model(planet1.model);

	model = glm::translate(model, glm::vec3(x, y, z));
	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(planet1.vao);

	//glLineWidth(1.0f);
	glutWireSphere(0.7, 15, 15);

	// GLUT: unbind vertex-array-object
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
	sun.model = glm::mat4(1.0f);
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
	planet1.model = glm::mat4(1.0f);
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
	moonPlanet1.model = glm::mat4(1.0f);
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
	moonPlanet2.model = glm::mat4(1.0f);
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
	glm::vec3 eye(0.0f, 0.0f, 10.0f);
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

	// Create all objects.
	
	// GLUT: create vertex-array-object for glut geometry, the "default"
	// must be bound before the glutWireSphere call
	initWireSphere();
	initSun();
	initPlanet2();
	initPlanet1();
	initMoonPlanet1();
	initMoonPlanet2();

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
	releaseObject(wireSphere);
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderPlanet1(5.0, 0.0, 0.0);
	renderMoonPlanet1(3.5, 0.0, 0.0);
	renderMoonPlanet1(6.5, 0.0, 0.0);
	renderMoonPlanet1(5.0, 0.0, 0.0);

	renderPlanet2(-10.0, 0.0, 0.0);
	renderMoonPlanet2(-10.5, 1.5, 0.0);
	renderMoonPlanet2(-11.5, 1.5, 0.0);
	renderMoonPlanet2(-9.5, 1.5, 0.0);
	renderMoonPlanet2(-8.5, 1.5, 0.0);

	renderMoonPlanet2(-11.5, 0.0, 0.0);
	renderMoonPlanet2(-8.5, 0.0, 0.0);

	renderMoonPlanet2(-10.5, -1.5, 0.0);
	renderMoonPlanet2(-11.5, -1.5, 0.0);
	renderMoonPlanet2(-9.5, -1.5, 0.0);
	renderMoonPlanet2(-8.5, -1.5, 0.0);

	renderSun();
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
	  glutDestroyWindow ( glutID );
	  return;
	  
	case '+':
		// do something
		break;
	case '-':
		// do something
		break;
	case 'x':
		
		break;
	case 'y':
		// do something
		break;
	case 'z':
		// do something
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
	//glutIdleFunc   (glutDisplay); // redisplay when idle

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
