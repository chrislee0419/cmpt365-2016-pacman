/*
//	for CMPT 365 Term Project
//	by Chris Lee - cla235
*/

#pragma once

#include <iostream>
#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"
#include "..\..\depend\glm\vec4.hpp"
#include "..\_colours.h"

class Box
{
private:
	int _xsize, _ysize, _xpos, _ypos;
	glm::vec4 _outer_colour, _inner_colour;
	GLuint vao;
	GLuint position_vbo, colour_vbo;
	static GLuint _vertex_position, _vertex_colour;

	void _Init();
	bool _Assert();
	void _SetValues(int xsize, int ysize, int xpos, int ypos);
	void _SetColours(glm::vec4 outer_colour, glm::vec4 inner_colour);
	glm::vec4* _CreateVerticesArray();
	void _CreateGLObjects();
	void _PushVerticesToBuffer();
	void _PushColoursToBuffer();
	void _Draw();

public:
	Box();
	Box(int xsize, int ysize, int xpos, int ypos);
	Box(int xsize, int ysize, int xpos, int ypos, glm::vec4 outer_colour, glm::vec4 inner_colour);
	Box(const Box &old_box);
	~Box();

	int GetXSize();
	int GetYSize();
	int GetXPosition();
	int GetYPosition();

	void SetXSize(int x);
	void SetYSize(int y);
	void SetXPosition(int x);
	void SetYPosition(int y);
	void Translate(int x, int y);
	void SetOuterColour(glm::vec4 colour);
	void SetInnerColour(glm::vec4 colour);
	static void SetVertexAttributes(GLuint vertex_position, GLuint vertex_colour);

	void Draw(int x_translate, int y_translate);

	static Box* CreateTestBox(GLuint vertex_position, GLuint vertex_colour);
	static void DisplayTestBox(Box* box_objects);
};
