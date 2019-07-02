#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"
#include "OBJLoader.h"
#include "MeshObject.h"

//A///////////////////////////////////////
#include "AbstractSphere.h"
#include "Sphere.h"
#include <time.h>
////////////////////////////////////////
#pragma warning(disable:4996)

// Standard window width
const int WINDOW_WIDTH = 980;
// Standard window height
const int WINDOW_HEIGHT = 650;

//A
//cg::Sphere* sphereSun = nullptr;
cg::Sphere* PlanetSlope = nullptr;
cg::Sphere* PlanetStraight = nullptr;

bool bShutDown = true, bStartTime = true;
clock_t start, end_, end_measure;

unsigned  lightIndex = 0;
glm::vec4 lights[2] = {
	{ 0.0f, 1.0f, 0.0f, 0.5f },
	{ -0.01f,  0.0f, 0.0f, 1.0f }
};

double X_VIEW = 0.0f, Y_VIEW = 0.0f, Z_VIEW = 10.0f; //view Matrix

bool bGouroud = true, bIsWireFrame = false;
float iVelocity = -0.1f;
GLfloat rotateViewZ = 0.0f;

std::ostringstream os;
//A

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
/*struct Object 
{
    inline Object()
            : vao(0),
              positionBuffer(0),
              colorBuffer(0),
              indexBuffer(0),
              yAxis(0) {}

    // IDs for several buffers. 
    GLuint vao;

    GLuint positionBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;

    GLuint yAxis;

    // Model matrix  
    glm::mat4x4 model;
};

//Object triangle;
Object quad; 
Object wiresphere; // GLUT geometry
Object axis; // GLUT geometry*/

MeshObject *meshObjectSun;
MeshObject *meshObjectShip;
glm::vec3 eye = glm::vec3(0.0f, 0.0f, 8.0f);
glm::mat4x4 projectionMod = glm::mat4(1.0f);
unsigned int lightsource = 0;

void setShaderUniforms(glm::mat4 mvp, glm::mat4 modifiedModel, glm::vec3 color)
{
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

/*void renderAxis(glm::vec3 color) 
{
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
}*/

void renderMeshObject(MeshObject *object, glm::vec3 color) {
    object->render(projection, view, projectionMod, &setShaderUniforms, color);
}
/*
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
*/
void setView() 
{
	// Construct view matrix.
	glm::vec3 eye(X_VIEW, Y_VIEW, Z_VIEW);
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

    // GLUT: create vertex-array-object for glut geometry, the "default"
    // must be bound before the glutWireSphere call
	
    HalfEdgeList *halfEdgeList = loadIntoHEL("objs/bigguy.obj");	//testcubeBigKopie
    halfEdgeList->fixNormals();
    meshObjectSun = new MeshObject(shader->getHandle(), halfEdgeList);
 
    halfEdgeList = loadIntoHEL("objs/gunship.obj");
	halfEdgeList->fixNormals();
    meshObjectShip = new MeshObject(shader->getHandle(), halfEdgeList);
 /*
    initWireSphere(&wiresphere);
    initAxis();*/
	//A
	// "WIRE-FRAME" Modus aktivieren
	if (bIsWireFrame)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Face: GL_FRONT_AND_BACK ---- Modi: GL_POINT, GL_LINE, GL_FILL;
												   //glEnable(GL_CULL_FACE); // abschalten: glDisable () und demselben Argument
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Bei Bedarf Anzeigemodus mit Flächen zurücksetzen!
													//glDisable(GL_CULL_FACE); // abschalten: glDisable () und demselben Argument
	}

	glCullFace(GL_FRONT);	// GL_FRONT, GL_BACK oder GL_FRONT_AND_BACK

	if (bShutDown)
	{
		// Create cube objects.
		try
		{
			//sphereSun = new cg::Sphere(glm::vec3(1.0f, 1.0f, 0.0f), 1.4, &shader_phong, &shader_noLight, bGouroud); // cg::GLSLProgram *shader;
			PlanetSlope = new cg::Sphere(glm::vec3(0.0f, 1.0f, 0.0f), 0.8, &shader_phong, &shader_noLight, bGouroud);
			PlanetStraight = new cg::Sphere(glm::vec3(0.0f, 0.0f, 1.0f), 0.6, &shader_phong, &shader_noLight, bGouroud);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}

		// Manipulate models.

		PlanetSlope->model = glm::translate(PlanetSlope->getModel(), glm::vec3(4.5, 0.0f, 0.0f)); //#1 translate
		PlanetSlope->model = glm::rotate(PlanetSlope->getModel(), glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0)); // #1 kippen um 45°
		PlanetStraight->model = glm::translate(PlanetStraight->getModel(), glm::vec3(-2.5, 0.0f, 0.0f));

		//-A
		// Set light (only an example).
		//sphereSun->setLightVector(lights[lightIndex]);
		PlanetStraight->setLightVector(lights[lightIndex]);
		PlanetSlope->setLightVector(lights[lightIndex]);
	}
	//A

    return true;
}

/*
 Release object resources.
*/
/*void releaseObject(Object &obj)
{

    glDeleteVertexArrays(1, &obj.vao);
    glDeleteBuffers(1, &obj.indexBuffer);
    glDeleteBuffers(1, &obj.colorBuffer);
    glDeleteBuffers(1, &obj.positionBuffer);

    if (&obj.yAxis > 0)
        glDeleteVertexArrays(1, &obj.yAxis);
}*/

/*
 Release resources on termination.
 */
void release() 
{
	delete PlanetSlope;
	delete PlanetStraight;
	//delete sphereSun;

    // Shader program will be released upon program termination.
   /* releaseObject(wiresphere);
    releaseObject(axis);*/
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

    /*float time = (float)glutGet(GLUT_ELAPSED_TIME);
    if ((time - prevTime) > 50.0) {
        systemRotation += 1.5f * systemRotationSpeed;
        prevTime = time;
    }*/

	/////////////////////////
	//sphereSun->render(view, projection);
	PlanetSlope->render(view, projection);
	PlanetStraight->render(view, projection);
	/////////////////////////
   /* */projectionMod = glm::mat4(1.0f);
    projectionMod = glm::translate(projectionMod, {0, yOffset_system, 0});
    //renderWireSphere(&wiresphere, {1, 1, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(sunRotation.z), {0, 0, 1});
    projectionMod = glm::rotate(projectionMod, glm::radians(sunRotation.y), {0, 1, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(sunRotation.x), {1, 0, 0});
	// AAA
    float sunScale = meshObjectSun->getUniformScaleFactor();
    projectionMod = glm::scale(projectionMod, {sunScale, sunScale, sunScale});
    renderMeshObject(meshObjectSun, {1, 1, 0});
    //renderAxis({1, 1, 0});

    projectionMod = glm::mat4(1.0f);
    projectionMod = glm::translate(projectionMod, {0, yOffset_system, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, 1, 0});
    projectionMod = glm::translate(projectionMod, {9, 0, 0});
 
	double shipScale = meshObjectShip->getUniformScaleFactor() * 0.7;
    projectionMod = glm::scale(projectionMod, {shipScale, shipScale, shipScale});
    projectionMod = glm::rotate(projectionMod, glm::radians(180.0f), {0, 1, 0});
    renderMeshObject(meshObjectShip, {0.8, 0.8, 1});
 
   /* projectionMod = glm::mat4(1.0f);
    projectionMod = glm::translate(projectionMod, {0, yOffset_system + yOffset_planet1, 0});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, 1, 0});
    projectionMod = glm::translate(projectionMod, {0, 0, 5});
    projectionMod = glm::scale(projectionMod, {0.5f, 0.5f, 0.5f});
    projectionMod = glm::rotate(projectionMod, glm::radians(systemRotation), {0, 1, 0});
    renderWireSphere(&wiresphere, {0, 0, 1});
    renderAxis({0, 0, 1});

    for (int i = 0; i < 3; i++)
	{
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
	{
		for (int i = 0; i < (j == 0 ? 2 : 4); i++)
		{
			glm::mat4x4 moon_angle = glm::translate(glm::mat4(1.0f), { 0, j * 1.5f, 0 });
			moon_angle = glm::rotate(moon_angle, glm::radians(i * (j == 0 ? 180.0f : 90.0f)), { 0, 1, 0 });
			moon_angle = glm::translate(moon_angle, { 2, 0, 0 });
			moon_angle = glm::scale(moon_angle, { 0.5f, 0.5f, 0.5f });
			projectionMod *= moon_angle;
			renderWireSphere(&wiresphere, { 0.3f, 0.3f, 0.3f });
			projectionMod /= moon_angle;
		}
	}*/
}

void rotatePlanetSystem()
{
	//Rotation des Gesammten Systems
	// Der Planet schief
	PlanetSlope->model = glm::rotate(PlanetSlope->model, glm::radians(0.5f), glm::vec3(-1.0, -1.0, 0.0));	// Rotation den gekippten Planeten um eigene Achse
	PlanetSlope->model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * PlanetSlope->model;

	PlanetStraight->model = glm::rotate(PlanetStraight->model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0));	// #2 Rotation des geraden Planeten um eigene Achse
	PlanetStraight->model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * PlanetStraight->model;

	glutPostRedisplay();
}
void glutDisplay()
{
    render();
    glutSwapBuffers();
	rotatePlanetSystem();
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
    projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

 // Callback for char input.
void glutKeyboard(unsigned char keycode, int x, int y) 
{
    switch (keycode)
	{
        case 27: // ESC
            glutDestroyWindow(glutID);
            return;
		case '-':
			if (Z_VIEW < 20) {
				Z_VIEW += 0.1;
				Y_VIEW += 0.0;
				X_VIEW += 0.0;
			}
			setView();
			break;

		case '+':
			if (Z_VIEW > 3) {
				Z_VIEW -= 0.1;
				Y_VIEW -= 0.0;
				X_VIEW -= 0.0;
			}
			setView();
			break;
		case 'X':
        case 'x':
            sunRotation.x += 5;
            break;
		case 'Y':
        case 'y':
            sunRotation.y += 5;
            break;
		case 'Z':
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

			PlanetSlope->toggleRenderNormals();
			PlanetStraight->toggleRenderNormals();
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

			lightIndex = 1 - lightIndex;
			//sphereSun->setLightVector(lights[lightIndex]);
			PlanetSlope->setLightVector(lights[lightIndex]);
			PlanetStraight->setLightVector(lights[lightIndex]);
			os << "06 - LightVector " << glm::to_string(lights[lightIndex]) << std::flush;
			glutSetWindowTitle(os.str().c_str());

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

		case 'q':
			if (bStartTime)
			{
				start = clock();
				bStartTime = false;
			}

			end_measure = start + 1;
			end_ = clock();

			if (end_measure > end_)
				return;

			bStartTime = true;

			if (rotateViewZ < 360.0f) {
				rotateViewZ += 1.5f;
			}
			bShutDown = false;
			init();
			bShutDown = true;
			break;

		case 'v':
			if (bStartTime)
			{
				start = clock();
				bStartTime = false;
			}

			end_measure = start + 1;
			end_ = clock();

			if (end_measure > end_)
				return;

			bStartTime = true;

			if (rotateViewZ > 0.0f) {
				rotateViewZ -= 1.5f;
			}

			bShutDown = false;
			init();
			bShutDown = true;
			break;

		case 'a':
			if (bStartTime)
			{
				start = clock();
				bStartTime = false;
			}

			end_measure = start + (clock_t)0.3;
			end_ = clock();

			if (end_measure > end_)
				return;

			bStartTime = true;


			if (!bIsWireFrame)
				bIsWireFrame = true;
			else
				bIsWireFrame = false;

			bShutDown = false;
			init();
			bShutDown = true;
			break;
		case '0':
			if (!bGouroud)
				bGouroud = true;
			else
				bGouroud = false;

			init();
			break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
	///  START: erzeuge Fenster
	// Initialisiere "FreeGLUT" - Bibliothek (window toolkit)
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(40, 40);
    glutInit(&argc, argv);

    // GLUT: Create a window and opengl context (version 4.3 core profile).
    glutInitContextVersion(4, 2);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutCreateWindow("Aufgabenblatt 06: OBJ-Loader");
    glutID = glutGetWindow();

	// GLEW: opengl -Erweiterungen laden!
    glewExperimental = GL_TRUE;
	// Um OpenGL 4.0-Funktionen unterstützen zu können, benötigt unser Programm Hilfe von der GLEW-Bibliothek!!!
	GLenum GlewInitResult = glewInit();	// GLEW - Werkzeuge (!) aktivieren

	if (GlewInitResult != GLEW_OK)
	{
		/*Wenn dies nicht der Fall ist, schreiben wir eine Fehlernachricht in die Befehlszeile und
		beenden das Programm. Die Fehlernachricht enthält den tatsächlichen Fehler,
		der von GLEW durch den Funktionsaufruf "glewGetErrorString" zurückgegeben wird.*/
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));

		exit(EXIT_FAILURE);
	}

	// GLUT: Rückruffunktionen: glutResize(), glutDisplay()  (CALLBACS) für folgende Ereignisse:
    glutReshapeFunc(glutResize);	// Verändern der Fenstergröße: Funktion zum Umformen wird jedes Mal aufgerufen, wenn die Größe des Fensters geändert wird
    glutDisplayFunc(glutDisplay);	// Rendern der Szene: Anzeigefunktion wird jedes Mal aufgerufen, wenn die Szene auf den Bildschirm gezeichnet wird.
    glutIdleFunc(glutDisplay); // redisplay when idle

	/*Da wir zu diesem Zeitpunkt einen OpenGL-Kontext haben, ist es sicher, OpenGL-Funktionen aufzurufen.
	Als erstes rufen wir glGetString mit GL_VERSION als Parameter auf,
	um die erstellte Version des OpenGL-Kontexts abzurufen.*/
	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
	///  END Fenster erstellen

	/// ********* Kontext ist gültig und wir sind zum Zeichnen bereit! ********

	// GLUT: Rückruffunktion: glutKeyboardFunc (CALLBAC) für die Tastatur-Ereignisse:
    glutKeyboardFunc(glutKeyboard);

	/* Initialisation von VAO (Vertex Array Object)->Erstellen und Verwenden von Vertex-Pufferobjekten -> Vertex Buffer Objects (VBO)
	Ein Vertex Array Object (oder VAO) ist ein Objekt,
	das beschreibt, wie die Vertex-Attribute in einem Vertex Buffer Objects Vertex-Puffer-Objekt (VBO) gespeichert werden.
	Dies bedeutet, dass der VAO nicht das eigentliche Objekt ist, das die Vertexdaten speichert,
	sondern der Deskriptor der Vertexdaten.
	*/
    // init vertex-array-objects.
    {
        bool result = init();
        if (!result) {
            release();
            return -2;
        }
    }

	// GLUT: Schleife, bis der Benutzer das Fenster schließt
	/*das Herz der Anwendung. Diese Funktion wird ausgeführt, solange das Fenster aktiv ist und
	das Fenster nicht geschlossen wurde.
	Daraufhin werden Zeichenbefehle ausgegeben und Fensteroperationen ausgeführt.*/
	glutMainLoop();	// Rendering und Handhabung des Events

	release();	// Räumen bei Beendigung alles auf.

	return 0;	// Erfolg, oder ->exit(EXIT_SUCCESS);
}
