
#include "depend\glew\glew.h"
#include "depend\freeglut\freeglut.h"
#include <iostream>

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowSize();
	glutCreateWindow("PACMAN");

	glutMainLoop();

	return 0;
}