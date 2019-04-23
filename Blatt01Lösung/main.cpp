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

float red;
float green;
float blue;

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

void HSV_to_RGB(float h, float s, float v)
{
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
}

void inputColors() {
	int model;
	bool input = false;

	do {
		std::cout << "RGB: 1, CMY: 2, HSV: 3 (mit r,g,b,c,m,y,s,v von 0 bis 1 und h von 0 bis 360)" << std::endl;
		if (!(std::cin >> model)) {
			std::cout << "Bitte geben Sie nur Zahlen ein\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
		} 
		else if ((model != 1) && (model != 2) && (model != 3)) {
			std::cout << "Falsche Eingabe! Versuchen sie es nochmal" << std::endl;
			
		}
		else {
			input = true;
		}
	} while (!input);
	
	if (model == 1) {

		std::cout << "Geben Sie einen Rot-Wert ein: " << std::endl;
		std::cin >> red;
		std::cout << "Geben Sie einen Grün-Wert ein: " << std::endl;
		std::cin >> green;
		std::cout << "Geben Sie einen Blau-Wert ein: " << std::endl;
		std::cin >> blue;
	}
	else if (model == 2) {
		float cyan;
		float magenta;
		float yellow;
		std::cout << "Geben Sie einen Cyan-Wert ein: " << std::endl;
		std::cin >> cyan;
		std::cout << "Geben Sie einen Magenta-Wert ein: " << std::endl;
		std::cin >> magenta;
		std::cout << "Geben Sie einen Gelb-Wert ein: " << std::endl;
		std::cin >> yellow;
		red = 1.0f - cyan;
		green = 1.0f - magenta;
		blue = 1.0f - yellow;
	}
	else if (model == 3) {
		float hue;
		float saturation;
		float value;
		std::cout << "Hue: " << std::endl;
		std::cin >> hue;
		std::cout << "Saturation: " << std::endl;
		std::cin >> saturation;
		std::cout << "Value: " << std::endl;
		std::cin >> value;
		HSV_to_RGB(hue, saturation, value);

	}
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
	const std::vector<GLushort>  indices = { 0, 1, 2 };

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

void initQuad()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { -1.0f, 1.0f, 0.0f }, { -1.0, -1.0, 0.0 }, { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
	const std::vector<glm::vec3> colors = { { red, green, blue }, { red, green, blue }, { red, green, blue }, { red, green, blue } };
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
	quad.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
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
	//initTriangle();
	initQuad();

	return true;
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderTriangle();
	renderQuad();
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
		// do something
		break;
	case 'y':
		// do something
		break;
	case 'z':
		// do something
		inputColors();
		std::cout << "R: " << red << ", G: " << green << " , B: " << blue << std::endl;
		initQuad();
		break;
	}
	glutPostRedisplay();
}

float MAX(float r, float g, float b) {
	float max;
	if (r >= g && r >= b) {
		return max = r;
	}
	else if (g >= r && g >= b) {
		return max = g;
	}
	else if (b >= g && b >= r) {
		return max = b;
	}
}

float MIN(float r, float g, float b) {
	float min;
	if (r <= g && r <= b) {
		return min = r;
	}
	else if (g <= r && g <= b) {
		return min = g;
	}
	else if (b <= g && b <= r) {
		return min = b;
	}
}

void RGB_to_HSV(float red, float green, float blue) {
	float hue = 0.0f;
	float saturation;

	std::cout << "Umrechnung in HSV...." << std::endl;
	float min = MIN(red, green, blue);
	float max = MAX(red, green, blue);
	if (min == max) {
		hue = 0.0f;
	}
	else if (red == max) {
		hue = 60.0f * (0.0f + ((green - blue) / (max - min)));
	}
	else if (green == max) {
		hue = 60.0f * (2.0f + ((blue - red) / (max - min)));
	}
	else if (blue == max) {
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

	std::cout << "H: " << round(hue) << " S: " << saturation << " V: " << value << std::endl;
	std::cout << std::endl;
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



void HSV_to_RGB_and_CMY(float h, float s, float v) {

	std::cout << "HSV: " << std::endl;
	std::cout << "H: " << h << " S: " << s << " V: " << v << std::endl;

	std::cout << "Umrechnung in RGB...." << std::endl;

	HSV_to_RGB(h, s, v);

	std::cout << "R: " << red << " G: " << green << " B: " << blue << std::endl;

	std::cout << "Umrechnung in CMY...." << std::endl;

	float cyan = 1.0f - red;
	float magenta = 1.0f - green;
	float yellow = 1.0f - blue;

	std::cout << "C: " << cyan << " M: " << magenta << " Y: " << yellow << std::endl;

	std::cout << std::endl;
	std::cout << "-------------------------------" << std::endl;
}



int main(int argc, char** argv)
{

	RGB_to_CMY_and_HSV(0.0f, 0.05f, 0.858f);
	HSV_to_RGB_and_CMY(236.0f, 1.0f, 0.85f);
	CMY_to_RGB_and_HSV(0.7f, 0.4f, 0.35f); 

	inputColors();

	std::cout << "R: " << red << ", G: " << green << " , B: " << blue << std::endl;

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
