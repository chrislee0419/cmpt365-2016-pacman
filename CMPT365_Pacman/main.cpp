
#include <iostream>

#include "depend\glew\glew.h"
#include "depend\freeglut\freeglut.h"
#include "shaders\ShaderLoader.h"

#include "depend\glm\vec3.hpp"
#include "depend\glm\vec4.hpp"
#include "depend\glm\mat4x4.hpp"

using namespace std;

// GLOBAL VARIABLES
int window_x = 800;
int window_y = 800;

GLuint loc_x, loc_y;		// used for scaling after resizing windows
GLuint program;				// used to store shader program
GLuint vertex_position, vertex_colour;	// used to store vertex attributes

void Initialize()
{
	// Prepare shaders
	Core::ShaderLoader shader_loader;
	program = shader_loader.CreateProgram("shaders\\vshader.glsl", "shaders\\fshader.glsl");
	glUseProgram(program);

	vertex_position = glGetAttribLocation(program, "vPosition");
	vertex_colour = glGetAttribLocation(program, "vColour");

	loc_x = glGetAttribLocation(program, "xsize");
	loc_y = glGetAttribLocation(program, "ysize");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Display()
{

	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{

}

int main(int argc, char **argv) {

	// GLUT initialization
	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Pacman");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW failed to init");
		return 1;
	}

	// Initialization
	Initialize();

	// Callback registration
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}