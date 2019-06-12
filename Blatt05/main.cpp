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
cg::GLSLProgram programShaded;


glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;


float eyeY = 2.0f;

float xdegree = 0.0f;
float ydegree = 0.0f;
float zdegree = 0.0f;

GLfloat rotateZ = 45.0f;
GLfloat rotateZAxis = 45.0f;
GLfloat rotateX = 30;
GLfloat rotateY;
GLfloat cameraYPos = 0.0f;
GLfloat planet1YPos = 0.0f;
GLfloat rotationSpeed = 0.05f;
GLfloat rotateViewZ = 0.0f;




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
		indexBuffer(0),
		normalBuffer(0)
	{}

	inline ~Object() { // GL context must exist on destruction
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteBuffers(1, &colorBuffer);
		glDeleteBuffers(1, &positionBuffer); 
		glDeleteBuffers(1, &normalBuffer);
	}

	GLuint vao;        // vertex-array-object ID

	GLuint positionBuffer; // ID of vertex-buffer: position
	GLuint colorBuffer;    // ID of vertex-buffer: color

	GLuint indexBuffer;    // ID of index-buffer

	GLuint normalBuffer;

	glm::mat4x4 model; // model matrix
};

Object sunAxis;
Object objNormals;
Object planet1Axis;
Object planet2Axis;
Object planet1;
Object planet2;
Object planet1Moon1;
Object planet1Moon2;
Object planet1Moon3;
Object planet1Moon4;
Object planet2Moon1;
Object planet2Moon2;
Object planet2Moon3;
Object planet2Moon4;



Object sun;


void renderSun()
{
	glm::mat4x4 sunModel(sun.model);

	//sun.model = glm::scale(sun.model, glm::vec3(1.5f));

	glm::mat4 mv = view * sun.model;
	// Create mvp.
	glm::mat4x4 mvp = projection * mv;

	// Create normal matrix (nm) from model matrix.
	glm::mat3 nm = glm::inverseTranspose(glm::mat3(sun.model));

	// Create light vector
	glm::vec4 v = { 2.0f, 1.0f, 5.0f, 1.0f };



	// Bind the shader program and set uniform(s).
	programShaded.use();
	programShaded.setUniform("lightI", float(1.0f));
	programShaded.setUniform("surfKa", glm::vec3(0.1f, 0.1f, 0.1f));
	programShaded.setUniform("surfKd", glm::vec3(0.7f, 0.1f, 0.1f));
	programShaded.setUniform("surfKs", glm::vec3(1, 1, 1));
	programShaded.setUniform("surfShininess", float(8.0f));
	programShaded.setUniform("modelviewMatrix", mv);
	programShaded.setUniform("projectionMatrix", projection);
	programShaded.setUniform("normalMatrix", nm);
	programShaded.setUniform("light", v);
	//programShaded.setUniform("light", glm::vec3(1, 0, 0));
	

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(sun.vao);
	glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	program.use();
	program.setUniform("mvp", mvp);

	glBindVertexArray(objNormals.vao);
	glDrawElements(GL_LINES, 1200, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);	 
}

void renderSunAxis() {
	// Create mvp.
	glm::mat4x4 mvp = projection * view * sunAxis.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(sunAxis.vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderAxisPlanet1()
{
	glm::mat4 sunModel(sun.model);


	planet1Axis.model = glm::rotate(sunModel, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	planet1Axis.model = glm::translate(planet1Axis.model, glm::vec3(5.0f, planet1YPos, 0.0f));

	glm::mat4x4 mvp = projection * view * planet1Axis.model;

	program.use();
	program.setUniform("mvp", mvp);

	glBindVertexArray(planet1Axis.vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderPlanet1()
{
	//glm::mat4x4 model(planet1.model);
	glm::mat4 sunModel(sun.model);

	planet1.model = glm::rotate(sunModel, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	planet1.model = glm::translate(planet1.model, glm::vec3(5.0f, planet1YPos, 0.0f));
	planet1.model = glm::rotate(planet1.model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::scale(model, glm::vec3(2.9f));
	// Create mvp.
	glm::mat4x4 mvp = projection * view * planet1.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(planet1.vao);

	
	glBindVertexArray(planet1.vao);
	glDrawElements(GL_TRIANGLES, 620, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	glBindVertexArray(objNormals.vao);
	glDrawElements(GL_LINES, 1200, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderMoonPlanet1(float x, float z, Object &object)
{
	glm::mat4x4 model(object.model);

	model = glm::rotate(planet1.model, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(planet1.model, glm::vec3(x, 0.0f, z));
	model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));

	model = glm::scale(model, glm::vec3(0.5f));

	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(object.vao);
	glDrawElements(GL_TRIANGLES, 620, GL_UNSIGNED_SHORT, 0);


	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);

	glBindVertexArray(objNormals.vao);
	glDrawElements(GL_LINES, 1200, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderAxisPlanet2()
{
	glm::mat4 sunModel(sun.model);

	/*planet2Axis.model = glm::rotate(glm::mat4(1.0f), glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));
	planet2Axis.model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f));
	planet2Axis.model = glm::rotate(glm::mat4(1.0f), glm::radians(rotateZAxis), glm::vec3(0.0, 0.0, 1.0));	   */
	
	

	
	planet2Axis.model = glm::rotate(sunModel, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));
	planet2Axis.model = glm::translate(planet2Axis.model, glm::vec3(-10.0f, 0.0f, 0.0f));
	planet2Axis.model = glm::rotate(planet2Axis.model, glm::radians(rotateZ), glm::vec3(0.0, 0.0, 1.0));
	


	glm::mat4x4 mvp = projection * view * planet2Axis.model;

	program.use();
	program.setUniform("mvp", mvp);

	glBindVertexArray(planet2Axis.vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderPlanet2()
{
	//glm::mat4x4 model(planet2.model);
	glm::mat4 planetAxes(planet2Axis.model);
	glm::mat4 sunModel(sun.model);


	planet2.model = glm::rotate(sunModel, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	planet2.model = glm::translate(planet2.model, glm::vec3(-10.0f, 0.0f, 0.0f));
	planet2.model = glm::rotate(planet2.model, glm::radians(rotateZ), glm::vec3(0.0f, 0.0f, 1.0f));
	planet2.model = glm::rotate(planet2.model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	
	//model = glm::rotate(sunModel, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(planetAxes, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));
	//model = glm::rotate(planetAxes, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));
	
	//model = glm::rotate(planetAxes, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));

	// Create mvp.
	glm::mat4x4 mvp = projection * view * planet2.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(planet2.vao);
	glDrawElements(GL_TRIANGLES, 620, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	glBindVertexArray(objNormals.vao);
	glDrawElements(GL_LINES, 1200, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderMoonPlanet2(float x, float y, float z, Object& object)
{
	glm::mat4x4 model(object.model);

	model = glm::rotate(planet2.model, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(planet2.model, glm::vec3(x, y, z));
	model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0, 1.0, 0.0));

	model = glm::scale(model, glm::vec3(0.5f));

	// Create mvp.
	glm::mat4x4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(object.vao);
	glDrawElements(GL_TRIANGLES, 620, GL_UNSIGNED_SHORT, 0);


	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);

	glBindVertexArray(objNormals.vao);
	glDrawElements(GL_LINES, 1200, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void initAxis(Object &axis) {

	const std::vector<glm::vec3> vertices = { { 0, -2, 0 }, { 0, 2, 0 }};

	const std::vector<glm::vec3> colors = { { 1, 1, 0 },{ 1, 1, 0 }};

	const std::vector<GLushort> indices = { 0, 1};

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

void initOctahedron(Object &object) {
	int steps = 0;
	int index[75] = { 0, 3, 7, 3, 4, 20, 7, 3, 20, 7, 20, 8, 4, 5, 18, 20, 4, 18, 20, 18, 19, 8, 20, 19, 8, 19, 9, 5, 6, 15, 5, 15, 18, 18, 15, 16, 19, 18, 16, 19, 16, 17, 19, 17, 9, 9, 17, 10,
		6, 1, 11, 6, 11, 15, 15, 11, 12, 15, 12, 16, 16, 12, 13, 16, 13, 17, 17, 13, 14, 17, 14, 10, 10, 14, 2 };

	std::vector<glm::vec3> vertices = { };
	std::vector<glm::vec3> colors = { };
	std::vector<GLushort>  indices = { };
	std::vector<glm::vec3> normals = { };

	std::vector<glm::vec3> triangle1 = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f) };
	std::vector<glm::vec3> triangle2 = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 1.0f) };
	std::vector<glm::vec3> triangle3 = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, -1.0f) };
	std::vector<glm::vec3> triangle4 = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, -1.0f) };
	std::vector<glm::vec3> triangle5 = { glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 1.0f) };
	std::vector<glm::vec3> triangle6 = { glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, -1.0f) };
	std::vector<glm::vec3> triangle7 = { glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f) };
	std::vector<glm::vec3> triangle8 = { glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f) };	

	std::vector<glm::vec3> triangleList[8] = { triangle1, triangle2, triangle3, triangle4, triangle5, triangle6, triangle7, triangle8 };

	for (int i = 0; i < 8; i++) {
		
		std::vector<glm::vec3> currentTriangle = triangleList[i];
		glm::vec3 vertex0 = currentTriangle[0];
		vertices.push_back(vertex0);
		glm::vec3 vertex1 = currentTriangle[1];
		vertices.push_back(vertex1);
		glm::vec3 vertex2 = currentTriangle[2];
		vertices.push_back(vertex2);
		glm::vec3 vertex6 = (1.0f / 5.0f) * vertex0 + (4.0f / 5.0f) * vertex1;
		glm::vec3 vertex10 = (1.0f / 5.0f) * vertex0 + (4.0f / 5.0f) * vertex2;
		glm::vec3 vertex8 = (3.0f / 5.0f) * vertex0 + (2.0f / 5.0f) * vertex2;
		glm::vec3 vertex9 = (2.0f / 5.0f) * vertex0 + (3.0f / 5.0f) * vertex2;
		glm::vec3 vertex4 = (3.0f / 5.0f) * vertex0 + (2.0f / 5.0f) * vertex1;
		glm::vec3 vertex5 = (2.0f / 5.0f) * vertex0 + (3.0f / 5.0f) * vertex1;

		vertices.push_back((4.0f / 5.0f) * vertex0 + (1.0f / 5.0f) * vertex1);
		vertices.push_back((3.0f / 5.0f) * vertex0 + (2.0f / 5.0f) * vertex1);
		vertices.push_back((2.0f / 5.0f) * vertex0 + (3.0f / 5.0f) * vertex1);
		vertices.push_back((1.0f / 5.0f) * vertex0 + (4.0f / 5.0f) * vertex1);
		vertices.push_back((4.0f / 5.0f) * vertex0 + (1.0f / 5.0f) * vertex2);
		vertices.push_back((3.0f / 5.0f) * vertex0 + (2.0f / 5.0f) * vertex2);
		vertices.push_back((2.0f / 5.0f) * vertex0 + (3.0f / 5.0f) * vertex2);
		vertices.push_back((1.0f / 5.0f) * vertex0 + (4.0f / 5.0f) * vertex2);
		vertices.push_back((4.0f / 5.0f) * vertex1 + (1.0f / 5.0f) * vertex2);
		vertices.push_back((3.0f / 5.0f) * vertex1 + (2.0f / 5.0f) * vertex2);
		vertices.push_back((2.0f / 5.0f) * vertex1 + (3.0f / 5.0f) * vertex2);
		vertices.push_back((1.0f / 5.0f) * vertex1 + (4.0f / 5.0f) * vertex2);
		vertices.push_back((3.0f / 4.0f) * vertex6 + (1.0f / 4.0f) * vertex10);
		vertices.push_back((2.0f / 4.0f) * vertex6 + (2.0f / 4.0f) * vertex10);
		vertices.push_back((1.0f / 4.0f) * vertex6 + (3.0f / 4.0f) * vertex10);
		vertices.push_back((2.0f / 3.0f) * vertex5 + (1.0f / 3.0f) * vertex9);
		vertices.push_back((1.0f / 3.0f) * vertex5 + (2.0f / 3.0f) * vertex9);
		vertices.push_back(0.5f * vertex4 + 0.5f * vertex8);
		
		for (int i = 0; i < 21; i++) {
			colors.push_back({ 0.0f, 1.0f, 1.0f });
		}

		indices.insert(indices.end(), index, index + 75);
		for (int j = 0; j < 75; j++) {
			index[j] += 21;
		}
		
	}


	for (int i = 0; i < vertices.size(); i++) {
		vertices[i] *= 1.0f / sqrt(vertices[i].x * vertices[i].x + vertices[i].y * vertices[i].y + vertices[i].z * vertices[i].z);
	}


	GLushort bla = 0;
	while (bla < indices.size()) {

		auto u = vertices[indices[bla + 2]] - vertices[indices[bla]];
		auto v = vertices[indices[bla + 1]] - vertices[indices[bla]];
		

		normals.push_back(glm::normalize(glm::cross(v, u)));

		bla += 3;

	}
	

	GLuint programId = programShaded.getHandle();
	GLuint pos;											   

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &object.vao);
	glBindVertexArray(object.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &object.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, object.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &object.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, object.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for normal lines
	glGenBuffers(1, &object.normalBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.normalBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, normals.size() * sizeof(GLushort), normals.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "normal");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 4: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &object.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	object.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	//Build the normals

	programId = program.getHandle();

	std::vector<glm::vec3> positions2;
	std::vector<glm::vec3> colors2;
	std::vector<GLushort> indices2;

	const glm::vec3 colorNormal(1.0f, 1.0f, 1.0f);
	

	GLushort k = 0;
	GLushort h = 0;
	GLushort count = 0;
	for (GLushort i = 0; i < indices.size() - 1; i++) {
				
		positions2.push_back(vertices[indices[i]]);
		positions2.push_back(vertices[indices[i]] + normals[h] * 0.5f);
		
		count++;
		if (count == 3) {
			h++;
			count = 0;
		}
		
		colors2.push_back(colorNormal);
		colors2.push_back(colorNormal);

		indices2.push_back(k);
		indices2.push_back(++k);
		++k;
	}


	// Vertex array object.
	glGenVertexArrays(1, &objNormals.vao);
	glBindVertexArray(objNormals.vao);

	// Position buffer.
	glGenBuffers(1, &objNormals.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objNormals.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, positions2.size() * sizeof(glm::vec3), positions2.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Color buffer.
	glGenBuffers(1, &objNormals.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objNormals.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors2.size() * sizeof(glm::vec3), colors2.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.

	glGenBuffers(1, &objNormals.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objNormals.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(GLushort), indices2.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */

bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, 5.0f);
	glm::vec3 center(0.0f, 0.0f, 1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);
	view = glm::rotate(view, glm::radians(rotateViewZ), glm::vec3(0.0f, 0.0f, 1.0f));

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

	if (!programShaded.compileShaderFromFile("shader/shaded.vert", cg::GLSLShader::VERTEX)) {
		std::cerr << programShaded.log();
		return false;
	}

	if (!programShaded.compileShaderFromFile("shader/shaded.frag", cg::GLSLShader::FRAGMENT)) {
		std::cerr << programShaded.log();
		return false;
	}

	if (!programShaded.link()) {
		std::cerr << programShaded.log();
		return false;
	}




	// Create all objects.
	//initAxis(sunAxis);
	//initAxis(planet1Axis);
	//initAxis(planet2Axis);
	initOctahedron(sun);
	/*initOctahedron(planet1);
	initOctahedron(planet2);
	initOctahedron(planet1Moon1);
	initOctahedron(planet1Moon2);
	initOctahedron(planet1Moon3);
	initOctahedron(planet1Moon4);
	initOctahedron(planet2Moon1);
	initOctahedron(planet2Moon2);
	initOctahedron(planet2Moon3);
	initOctahedron(planet2Moon4);*/

	return true;
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//renderSunAxis();
	//renderAxisPlanet1();
	//renderAxisPlanet2();
	renderSun();
	/*renderPlanet1();
	renderPlanet2();
	renderMoonPlanet1(1.5f, 1.5f, planet1Moon1);
	renderMoonPlanet1(-1.5f, 1.5f, planet1Moon2);
	renderMoonPlanet1(1.5f, -1.5f, planet1Moon3);
	renderMoonPlanet1(-1.5f, -1.5f, planet1Moon4);
	renderMoonPlanet2(0.0f, 2.0f, 1.5f, planet2Moon1);
	renderMoonPlanet2(0.0f, 2.0f, -1.5f, planet2Moon2);
	renderMoonPlanet2(1.5f, -2.0f, 0.0f, planet2Moon3);
	renderMoonPlanet2(-1.5f, -2.0f, 0.0f, planet2Moon4);	*/


	rotateY += rotationSpeed;

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
	//projection = glm::ortho(-5.0f*(float)width/height, 5.0f*(float)width/height, -5.0f, 5.0f, zNear, zFar);
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
	case 'q':
		if (rotateViewZ < 360.0f) {
			rotateViewZ += 5.0f;
		}
		init();
		break;
	case 'w':
		if (rotateViewZ > 0.0f) {
			rotateViewZ -= 5.0f;
		}
		init();
		break;
	case 'd':
		if (rotationSpeed > 0.3f) {
			rotationSpeed -= 0.2f;
		}
		break;
	case 'f':
		if (rotationSpeed < 5.0f) {
			rotationSpeed += 0.2f;
		}
		break;
	case 'i':
		planet1YPos -= 0.5f;
		break;
	case 'u':
		planet1YPos += 0.5f;
		break;
	case 'o':
		if (rotateZ > 0.0f) {
			rotateZ -= 2.0f;
		}
		break;
	case 'p':
		if (rotateZ < 360.0f) {
			rotateZ += 2.0f;
		}
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
	glutIdleFunc   (glutDisplay); // redisplay when idle

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
