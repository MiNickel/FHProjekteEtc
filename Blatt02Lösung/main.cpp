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

#include "math.h"
#include "main.h"



// Standard window width
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;
int steps = 5;
float radius = 1;


cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar  = 100.0f;

/*
Struct to hold data for object rendering.
*/
struct Object
{
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
Object circle;

float MAX(float r, float g, float b) {
	float max;
	if (r >= g && r >= b) {
		max = r;
	}
	else if (g >= r && g >= b) {
		max = g;
	}
	else if (b >= g && b >= r) {
		max = b;
	}
	return max;
}

float MIN(float r, float g, float b) {
	float min;
	if (r <= g && r <= b) {
		min = r;
	}
	else if (g <= r && g <= b) {
		min = g;
	}
	else if (b <= g && b <= r) {
		min = b;
	}
	return min;
}

void RGB_to_HSV(float red, float green, float blue) {
	float hue;
	float saturation;

	std::cout << "Umrechnung in HSV...." << std::endl;
	float min = MIN(red, green, blue);
	float max = MAX(red, green, blue);
	if (min == max) {
		hue = 0.0f;
	}
	else if (red == max && green != max && blue != max) {


		hue = 60.0f * (0.0f + ((green - blue) / (max - min)));
	}
	else if (green == max && red != max && blue != max) {

		hue = 60.0f * (2.0f + ((blue - red) / (max - min)));
	}
	else if (blue == max && red != max && green != max) {

		hue = 60.0f * (4.0f + ((red - green) / (max - min)));
	}
	if (hue < 0) {
		hue += 360.0f;
	}
	if (max == 0) {
		saturation = 0;
	}
	else {
		saturation = (max - min) / max;
	}
	float value = max;

	std::cout << "H: " << hue << " S: " << saturation << " V: " << value << std::endl;
	std::cout << std::endl;
}

void RGB_to_CMY_and_HSV(float red, float green, float blue) {
	
	std::cout << "RGB: " << std::endl;
	std::cout << "R: " << red << " G: " << green << " B: " << blue << std::endl;
	std::cout << "Umrechnung in CMY...." << std::endl;

	float cyan = 1.0f - red;
	float magenta = 1.0f - green;
	float yellow = 1.0f - blue;

	std::cout << "C: " << cyan << " M: " << magenta << " Y: " << yellow << std::endl;

	RGB_to_HSV(red, green, blue);
	
	std::cout << "-------------------------------" << std::endl;

}

void CMY_to_RGB_and_HSV(float c, float m, float y) {
	float cyan = c;
	float magenta = m;
	float yellow = y;

	std::cout << "CMY: " << std::endl;
	std::cout << "C: " << cyan << " M: " << magenta << " Y: " << yellow << std::endl;

	std::cout << "Umrechnung in RGB...." << std::endl;

	float red = 1.0f - cyan;
	float green = 1.0f - magenta;
	float blue = 1.0f - yellow;

	std::cout << "R: " << red << " G: " << green << " B: " << blue << std::endl;

	RGB_to_HSV(red, green, blue);

	std::cout << "-------------------------------" << std::endl;
}

void HSV_to_RGB_and_CMY(float h, float s, float v) {
	float red;
	float green;
	float blue;

	std::cout << "HSV: " << std::endl;
	std::cout << "H: " << h << " S: " << s << " V: " << v << std::endl;

	std::cout << "Umrechnung in RGB...." << std::endl;

	

	int hi = h / 60;
	float f = (h / 60) - hi;
	float p = v * (1 - s);
	float q = v * (1 - s * f);
	float t = v * (1 - s * (1 - f));

	if (hi == 0 || hi == 6) {
		red = v;
		green = t;
		blue = p;
	}
	else if (hi == 1) {
		red = q;
		green = v;
		blue = p;
	}
	else if (hi == 2) {
		red = p;
		green = v;
		blue = t;
	}
	else if (hi == 3) {
		red = p;
		green = q;
		blue = v;
	}
	else if (hi == 4) {
		red = t;
		green = p;
		blue = v;
	}
	else if (hi == 5) {
		red = v;
		green = p;
		blue = q;
	} 

	std::cout << "R: " << red << " G: " << green << " B: " << blue << std::endl;

	std::cout << "Umrechnung in CMY...." << std::endl;

	float cyan = 1.0f - red;
	float magenta = 1.0f - green;
	float yellow = 1.0f - blue;

	std::cout << "C: " << cyan << " M: " << magenta << " Y: " << yellow << std::endl;

	std::cout << std::endl;
	std::cout << "-------------------------------" << std::endl;
}



void renderCircle()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * circle.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(circle.vao);
	glDrawElements(GL_TRIANGLES, steps*3, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

}

void renderTriangle()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * triangle.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(triangle.vao);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
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



void initTriangle()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) };
	const std::vector<glm::vec3> colors = { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
	const std::vector<GLushort> indices = { 0, 1, 2 };

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
	triangle.model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.0f, 0.0f));
}

void initQuad(float value1, float value2, float value3)
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { -1.0f, 1.0f, 0.0f }, { -1.0, -1.0, 0.0 }, { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
	const std::vector<glm::vec3> colors = { { value1, value2, value3 }, { value1, value2, value3 }, { value1, value2, value3 }, { value1, value2, value3 } };
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };

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
	quad.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

void initQuadModel(float &value1, float &value2, float &value3)
{
	int model;
	std::cout << "RGB: 1, CMY: 2, HSV: 3 " << std::endl;
	std::cin >> model;
	if (model == 1) {
		std::cout << "Geben Sie einen Rot-Wert ein: " << std::endl;
		std::cin >> value1;
		std::cout << "Geben Sie einen Grün-Wert ein: " << std::endl;
		std::cin >> value2;
		std::cout << "Geben Sie einen Blau-Wert ein: " << std::endl;
		std::cin >> value3;
	}
	else if (model == 2) {
		std::cout << "Geben Sie einen Cyan-Wert ein: " << std::endl;
		std::cin >> value1;
		std::cout << "Geben Sie einen Magenta-Wert ein: " << std::endl;
		std::cin >> value2;
		std::cout << "Geben Sie einen Gelb-Wert ein: " << std::endl;
		std::cin >> value3;
		value1 = 1.0f - value1;
		value2 = 1.0f - value2;
		value3 = 1.0f - value3;
	}
	else if (model == 3) {
		std::cout << "Hue: " << std::endl;
		std::cin >> value1;
		std::cout << "Saturation: " << std::endl;
		std::cin >> value2;
		std::cout << "Value: " << std::endl;
		std::cin >> value3;
		HSV_to_RGB(value1, value3, value2);

	}
}

void HSV_to_RGB(float &h, float &s, float &v)
{
	int hi = h / 60;
	float f = (h / 60) - hi;
	float p = s * (1 - v);
	float q = s * (1 - v * f);
	float t = s * (1 - v * (1 - f));

	if (hi == 0 || hi == 6) {
		h = s;
		v = t;
		s = p;
	}
	else if (hi == 1) {
		h = q;
		v = s;
		s = p;
	}
	else if (hi == 2) {
		h = p;
		v = s;
		s = t;
	}
	else if (hi == 3) {
		h = p;
		v = q;
		s = v;
	}
	else if (hi == 4) {
		h = t;
		v = p;
		s = s;
	}
	else if (hi == 5) {
		h = s;
		v = p;
		s = q;
	}
}



void initCircle()
{
	std::vector<glm::vec3> circle_vertices = {};
	std::vector<glm::vec3> circle_colours = {};
	std::vector<GLushort> circle_indices = {};

	float red = 0.0f;
	float green = 1.0f;
	float blue = 0.0f;

	double angleStep = 360 / steps;
	double prevAngle = 0;

	for (unsigned short i = 0; i < steps; i++) {
		if (green == 1.0f) {
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
		}
		else if (red == 1.0f) {
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
		}
		else if (blue == 1.0f) {
			red = 0.0f;
			green = 1.0f;
			blue = 0.0f;
		}

		circle_vertices.push_back({ 0,0,0 });
		circle_colours.push_back({ red, green, blue });

		circle_vertices.push_back({ radius * sin(prevAngle), radius*cos(prevAngle), 0 });
		circle_colours.push_back({ red, green, blue });

		double angle = (i + 1)*angleStep * 3.14159265358979323846 / 180.0;
		circle_vertices.push_back({ radius*sin(angle), radius*cos(angle), 0});
		circle_colours.push_back({ red, green, blue });
		prevAngle = angle;

		circle_indices.push_back(i*3);
		circle_indices.push_back(i * 3+1);
		circle_indices.push_back(i * 3+2);


	}

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &circle.vao);
	glBindVertexArray(circle.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &circle.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, circle.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, circle_vertices.size() * sizeof(glm::vec3), circle_vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &circle.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, circle.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, circle_colours.size() * sizeof(glm::vec3), circle_colours.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &circle.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, circle_indices.size() * sizeof(GLushort), circle_indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	circle.model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.0f, 0.0f));

}
void initCircleBlue()
{
	std::vector<glm::vec3> circle_vertices = {};
	std::vector<glm::vec3> circle_colours = {};
	std::vector<GLushort> circle_indices = {};

	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;

	double angleStep = 360 / steps;
	double prevAngle = 0;

	for (unsigned short i = 0; i < steps; i++) {
		

		circle_vertices.push_back({ 0,0,0 });
		circle_colours.push_back({ red, green, blue });

		circle_vertices.push_back({ radius * sin(prevAngle), radius*cos(prevAngle), 0 });
		circle_colours.push_back({ red, green, blue });

		double angle = (i + 1)*angleStep * 3.14159265358979323846 / 180.0;
		circle_vertices.push_back({ radius*sin(angle), radius*cos(angle), 0 });
		circle_colours.push_back({ red, green, blue });
		prevAngle = angle;

		circle_indices.push_back(i * 3);
		circle_indices.push_back(i * 3 + 1);
		circle_indices.push_back(i * 3 + 2);


	}

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &circle.vao);
	glBindVertexArray(circle.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &circle.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, circle.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, circle_vertices.size() * sizeof(glm::vec3), circle_vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &circle.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, circle.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, circle_colours.size() * sizeof(glm::vec3), circle_colours.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &circle.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, circle_indices.size() * sizeof(GLushort), circle_indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	circle.model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.0f, 0.0f));

}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init(float value1, float value2, float value3)
{
	// OpenGL: Set "background" color and enable depth testing.
	//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClearColor(1, 1, 1, 1);

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
	//initTriangle();
	initQuad(value1, value2, value3);
	//initCircle();


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
	releaseObject(quad);
	//releaseObject(circle);
}



/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//renderTriangle();
	renderQuad();
	//renderCircle();
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

	case '+':
		if (steps < 30) {
			steps++;
			initCircle();
		}
		break;
	case '-':
		if (steps > 3) {
			steps--;
			initCircle();
		}
		break;
	case 'q':
		if (radius < 1.5) {
			radius = radius + 0.1f;
			initCircleBlue();
		}
			
		
		break;
	case 'w':
		if (radius > 0.1) {
			radius = radius - 0.1f;
			initCircleBlue();
		}
		
		break;
	case 'z':
		// do something
		break;
	}
	glutPostRedisplay();
}

void display(void) {
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5,
		-1.5, 1.5,
		-1.0, 1.0);

	float value1;
	float value2;
	float value3;
	initQuad(value1, value2, value3);
	
	glutSwapBuffers();
}







int main(int argc, char** argv)
{
	float value1;
	float value2;
	float value3;

	RGB_to_CMY_and_HSV(0.0f, 0.0f, 1.0f);

	CMY_to_RGB_and_HSV(0.7f, 0.25f, 0.75f);

	HSV_to_RGB_and_CMY(345.0f, 1.0f, 1.0f);
	
	initQuadModel(value1, value2, value3);
	// GLUT: Initialize freeglut library (window toolkit).
	glutInitWindowSize    (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40,40);
	glutInit(&argc, argv);

	// GLUT: Create a window and opengl context (version 4.3 core profile).
	glutInitContextVersion(4, 3);
	glutInitContextFlags  (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitDisplayMode   (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

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
	try {
		// Init VAO.
		{
			GLCODE(bool result = init(value1, value2, value3));
			if (!result) {
				release();
				return -2;
			}
		}
		glutMainLoop();
		release();
	}
	catch (const cg::GLException &e) {
		std::cout << e.what();
	}

	return 0;
} 


