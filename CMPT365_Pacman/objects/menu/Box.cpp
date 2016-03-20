/*
//	for CMPT 365 Term Project
//	by Chris Lee - cla235
*/

#include "Box.h"
#include "..\_colours.h"

// Constructors
Box::Box()
{
	_Init();
	_SetValues(40, 20, 0, 0);
	_SetColours(WHITE, BLACK);
	_CreateGLObjects();
}

Box::Box(int xsize, int ysize, int xpos, int ypos)
{
	_Init();
	_SetValues(xsize, ysize, xpos, ypos);
	_Assert();
	_SetColours(WHITE, BLACK);
	_CreateGLObjects();
}

Box::Box(int xsize, int ysize, int xpos, int ypos, glm::vec4 outer_colour, glm::vec4 inner_colour)
{
	_Init();
	_SetValues(xsize, ysize, xpos, ypos);
	_Assert();
	_SetColours(outer_colour, inner_colour);
	_CreateGLObjects();
}

// Deconstructor
Box::~Box()
{
	if ( glIsBuffer(position_vbo) == GL_TRUE )
		glDeleteBuffers(1, &position_vbo);
	if ( glIsBuffer(colour_vbo) == GL_TRUE )
		glDeleteBuffers(1, &colour_vbo);
	if (glIsVertexArray(vao) == GL_TRUE)
		glDeleteVertexArrays(1, &vao);
}

// Getter methods
int Box::GetXSize()
{
	return _xsize;
}

int Box::GetYSize()
{
	return _ysize;
}

int Box::GetXPosition()
{
	return _xpos;
}

int Box::GetYPosition()
{
	return _ypos;
}

// Setter methods
void Box::SetXSize(int x)
{
	_xsize = x;
	_Assert();
}

void Box::SetYSize(int y)
{
	_ysize = y;
	_Assert();
}

void Box::SetXPosition(int x)
{
	_xpos = x;
	_Assert();
}

void Box::SetYPosition(int y)
{
	_ypos = y;
	_Assert();
}

void Box::SetOuterColour(glm::vec4 colour)
{
	_outer_colour = colour;
	_PushColoursToBuffer();
}

void Box::SetInnerColour(glm::vec4 colour)
{
	_inner_colour = colour;
	_PushColoursToBuffer();
}

// static - should only be set once
void Box::SetVertexAttributes(GLuint vertex_position, GLuint vertex_colour)
{
	_vertex_position = vertex_position;
	_vertex_colour = vertex_colour;
}

// Rendering method
void Box::Draw(int x_translate, int y_translate)
{
	int old_xpos, old_ypos;
	if (x_translate != 0 || y_translate != 0)
	{
		old_xpos = _xpos;
		old_ypos = _ypos;

		_SetValues(_xsize, _ysize, _xpos + x_translate, _ypos + y_translate);
		_Assert();
	}

	_Draw();
	
	if (x_translate != 0 || y_translate != 0)
	{
		_SetValues(_xsize, _ysize, old_xpos, old_ypos);
	}
}

// Private helper methods
void Box::_Init()
{
	vao = 0;
	position_vbo = 0;
	colour_vbo = 0;
	_vertex_position = 0;
	_vertex_colour = 0;
}

void Box::_Assert()
{
	assert(_xsize > 4 && "Box has invalid xsize");
	assert(_ysize > 4 && "Box has invalid ysize");
	assert(_xpos >= 0 && _xpos <= 800 && "Box has invalid xpos");
	assert(_ypos >= 0 && _ypos <= 800 && "Box has invalid ypos");
}

void Box::_SetValues(int xsize, int ysize, int xpos, int ypos)
{
	_xsize = xsize;
	_ysize = ysize;
	_xpos = xpos;
	_ypos = ypos;
}

void Box::_SetColours(glm::vec4 outer_colour, glm::vec4 inner_colour)
{
	_outer_colour = outer_colour;
	_inner_colour = inner_colour;
}

glm::vec4* Box::_CreateVerticesArray()
{
	// 6 vertices for box background
	// 4*6 = 24 vertices for box border
	glm::vec4 *vertices = new glm::vec4[30];

	// Background
	vertices[0] = glm::vec4(_xpos, _ypos, 0.0, 1.0);
	vertices[1] = glm::vec4(_xpos + _xsize, _ypos, 0.0, 1.0);
	vertices[2] = glm::vec4(_xpos + _xsize, _ypos + _ysize, 0.0, 1.0);
	vertices[3] = glm::vec4(_xpos, _ypos, 0.0, 1.0);
	vertices[4] = glm::vec4(_xpos + _xsize, _ypos + _ysize, 0.0, 1.0);
	vertices[5] = glm::vec4(_xpos, _ypos + _ysize, 0.0, 1.0);
	// Bottom border
	vertices[6] = glm::vec4(_xpos, _ypos, 0.0, 1.0);
	vertices[7] = glm::vec4(_xpos + _xsize, _ypos, 0.0, 1.0);
	vertices[8] = glm::vec4(_xpos + _xsize, _ypos + 2, 0.0, 1.0);
	vertices[9] = glm::vec4(_xpos, _ypos, 0.0, 1.0);
	vertices[10] = glm::vec4(_xpos + _xsize, _ypos + 2, 0.0, 1.0);
	vertices[11] = glm::vec4(_xpos, _ypos + 2, 0.0, 1.0);
	// Top border
	vertices[12] = glm::vec4(_xpos, _ypos + _ysize - 2, 0.0, 1.0);
	vertices[13] = glm::vec4(_xpos + _xsize, _ypos + _ysize - 2, 0.0, 1.0);
	vertices[14] = glm::vec4(_xpos + _xsize, _ypos + _ysize, 0.0, 1.0);
	vertices[15] = glm::vec4(_xpos, _ypos + _ysize - 2, 0.0, 1.0);
	vertices[16] = glm::vec4(_xpos + _xsize, _ypos + _ysize, 0.0, 1.0);
	vertices[17] = glm::vec4(_xpos, _ypos + _ysize, 0.0, 1.0);
	// Left border
	vertices[18] = glm::vec4(_xpos, _ypos, 0.0, 1.0);
	vertices[19] = glm::vec4(_xpos + 2, _ypos, 0.0, 1.0);
	vertices[20] = glm::vec4(_xpos + 2, _ypos + _ysize, 0.0, 1.0);
	vertices[21] = glm::vec4(_xpos, _ypos, 0.0, 1.0);
	vertices[22] = glm::vec4(_xpos + 2, _ypos + _ysize, 0.0, 1.0);
	vertices[23] = glm::vec4(_xpos, _ypos + _ysize, 0.0, 1.0);
	// Right border
	vertices[24] = glm::vec4(_xpos + _xsize - 2, _ypos, 0.0, 1.0);
	vertices[25] = glm::vec4(_xpos + _xsize, _ypos, 0.0, 1.0);
	vertices[26] = glm::vec4(_xpos + _xsize, _ypos + _ysize, 0.0, 1.0);
	vertices[27] = glm::vec4(_xpos + _xsize - 2, _ypos, 0.0, 1.0);
	vertices[28] = glm::vec4(_xpos + _xsize, _ypos + _ysize, 0.0, 1.0);
	vertices[29] = glm::vec4(_xpos + _xsize - 2, _ypos + _ysize, 0.0, 1.0);
}

void Box::_CreateGLObjects()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &position_vbo);
	glGenBuffers(1, &colour_vbo);

	glm::vec4 *vertices = _CreateVerticesArray();

	// Store vertices in buffer
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, 30*sizeof(glm::vec4), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(_vertex_position, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_vertex_position);
	delete[] vertices;

	// Store colours in buffer
	glm::vec4 colours[30];
	for (int i = 0; i < 6; i++) colours[i] = _inner_colour;
	for (int i = 6; i < 30; i++) colours[i] = _outer_colour;
	glBindBuffer(GL_ARRAY_BUFFER, colour_vbo);
	glBufferData(GL_ARRAY_BUFFER, 30*sizeof(glm::vec4), colours, GL_STATIC_DRAW);
	glVertexAttribPointer(_vertex_colour, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_vertex_colour);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Box::_PushVerticesToBuffer()
{
	glm::vec4 *vertices = _CreateVerticesArray();

	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 30 * sizeof(glm::vec4), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Box::_PushColoursToBuffer()
{
	glm::vec4 colours[30] = {};
	for (int i = 0; i < 6; i++) colours[i] = _inner_colour;
	for (int i = 6; i < 30; i++) colours[i] = _outer_colour;

	glBindBuffer(GL_ARRAY_BUFFER, colour_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 30 * sizeof(glm::vec4), colours);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Box::_Draw()
{
	_PushVerticesToBuffer();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 30);
	glBindVertexArray(0);
}