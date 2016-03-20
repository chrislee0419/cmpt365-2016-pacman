
#include "depend\glew\glew.h"
#include "depend\freeglut\freeglut.h"
#include <iostream>
#include "shaders\ShaderLoader.h"
#include "depend\glm\vec3.hpp"
#include "depend\glm\vec4.hpp"
#include "depend\glm\mat4x4.hpp"

// GLOBAL VARIABLES

GLuint program;

void Initialize() {
	// Prepare shaders
	Core::ShaderLoader shader_loader;
	program = shader_loader.CreateProgram("shaders\\vshader.glsl", "shaders\\fshader.glsl");
	glUseProgram(program);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Display() {


	glutSwapBuffers();
}

int main(int argc, char **argv) {

	// GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Pacman");
	glewInit();

	// Initialization
	Initialize();

	// Callback registration
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}