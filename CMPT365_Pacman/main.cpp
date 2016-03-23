
#include <iostream>

#include "depend\glew\glew.h"
#include "depend\freeglut\freeglut.h"
#include "shaders\ShaderLoader.h"

#include "depend\glm\vec3.hpp"
#include "depend\glm\vec4.hpp"
#include "depend\glm\mat4x4.hpp"

#include "test\test.h"

using namespace std;

// GLOBAL VARIABLES
bool enable_test = true;
Test *tester_object;

GLuint vao;
GLuint pos_vbo, col_vbo;

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
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform1i(loc_x, window_x);
	glUniform1i(loc_y, window_y);

	if (enable_test)
	{
		//testdisp();
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

void test()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &pos_vbo);
	glGenBuffers(1, &col_vbo);
	glm::vec4 vertices[3] = { glm::vec4(0, 0, 0, 1), glm::vec4(800, 0, 0, 1), glm::vec4(0, 800, 0, 1) };
	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec4), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vertex_position, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertex_position);
	glm::vec4 colours[3] = { glm::vec4(1, 0, 0, 1), glm::vec4(0, 1, 0, 1), glm::vec4(0, 0, 1, 1) };
	glBindBuffer(GL_ARRAY_BUFFER, col_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec4), colours, GL_STATIC_DRAW);
	glVertexAttribPointer(vertex_colour, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertex_colour);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main(int argc, char **argv) {

	// GLUT initialization
	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
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
		//test();
		Test::SetVertexAttributes(vertex_position, vertex_colour);
		tester_object = new Test();
		tester_object->SetupTest();
	}

	// Callback registration
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}