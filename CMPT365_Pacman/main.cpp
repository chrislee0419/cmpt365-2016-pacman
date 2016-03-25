
#include <iostream>

#include "depend\glew\glew.h"
#include "depend\freeglut\freeglut.h"
#include "shaders\ShaderLoader.h"

#include "depend\glm\vec3.hpp"
#include "depend\glm\vec4.hpp"
#include "depend\glm\mat4x4.hpp"

#include "test\test.h"
#include "test\_util.h"

using namespace std;

// GLOBAL VARIABLES
bool enable_test = true;
Test *tester_object;


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

	loc_x = glGetUniformLocation(program, "xsize");
	loc_y = glGetUniformLocation(program, "ysize");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Cleanup()
{
	delete tester_object;
}

void testdisp()
{
	
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform1i(loc_x, window_x);
	glUniform1i(loc_y, window_y);

	if (enable_test)
	{
		//Test::StaticTestDisplay();
		tester_object->DisplayTest();
	}

	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		Cleanup();
		exit(EXIT_SUCCESS);
	}
}

void Reshape(GLsizei w, GLsizei h)
{
	window_x = w;
	window_y = h;
	glViewport(0, 0, w, h);
}

int main(int argc, char **argv) {

	// GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(window_x, window_y);
	glutCreateWindow("Pacman");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW failed to init");
		return 1;
	}

	// Initialization
	Initialize();

	// Testing
	if (enable_test)
	{
		Test::SetVertexAttributes(vertex_position, vertex_colour);
		tester_object = new Test();
		tester_object->SetupTest();
		//Test::StaticTest();
	}

	// Callback registration
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}