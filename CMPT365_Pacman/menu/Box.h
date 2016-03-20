#pragma once

#include <iostream>
#include "..\depend\freeglut\freeglut.h"
#include "..\depend\glew\glew.h"
#include "..\depend\glm\vec4.hpp"

class Box
{
private:
	int _xsize, _ysize, _xpos, _ypos;
	glm::vec4 _outer_colour, _inner_colour;
	GLuint vao;
	GLuint position_vbo, colour_vbo;
	static GLuint _vertex_position, _vertex_colour;
	glm::vec4 vertices[30];

	void _Init();
	void _Assert();
	void _SetValues(int xsize, int ysize, int xpos, int ypos);
	void _SetColours(glm::vec4 outer_colour, glm::vec4 inner_colour);
	void _CreateVerticesArray(glm::vec4 &vertices);
	void _CreateGLObjects();
	void _PushVerticesToBuffer();
	void _PushColourToBuffer();

public:
	Box();
	Box(int xsize, int ysize, int xpos, int ypos);
	Box(int xsize, int ysize, int xpos, int ypos, glm::vec4 outer_colour, glm::vec4 inner_colour);
	~Box();

	int GetXSize();
	int GetYSize();
	int GetXPosition();
	int GetYPosition();

	void SetXSize(int x);
	void SetYSize(int y);
	void SetXPosition(int x);
	void SetYPosition(int y);
	void SetOuterColour(glm::vec4 colour);
	void SetInnerColour(glm::vec4 colour);
	static void SetVertexAttributes(GLuint vertex_position, GLuint vertex_colour);

	void Draw(int x_translate, int y_translate);
};
