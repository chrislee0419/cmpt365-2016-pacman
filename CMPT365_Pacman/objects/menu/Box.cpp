/*
//	for CMPT 365 Term Project
//	by Chris Lee - cla235
*/

#include "Box.h"
#include "..\..\test\test.h"

// Globals
GLuint Box::_vertex_position;
GLuint Box::_vertex_colour;

// Constructors
Box::Box()
{
	_Init();
	_SetValues(40, 20, 0, 0);
	_SetColours(WHITE, BLACK);
}

Box::Box(int xsize, int ysize, int xpos, int ypos)
{
	_Init();
	_SetValues(xsize, ysize, xpos, ypos);
	_Assert();
	_SetColours(WHITE, BLACK);
}

Box::Box(int xsize, int ysize, int xpos, int ypos, glm::vec4 outer_colour, glm::vec4 inner_colour)
{
	_Init();
	_SetValues(xsize, ysize, xpos, ypos);
	_Assert();
	_SetColours(outer_colour, inner_colour);
}

Box::Box(const Box &old_box)
{
	_Init();
	_SetValues(old_box._xsize, old_box._ysize, old_box._xpos, old_box._ypos);
	_Assert();
	_SetColours(old_box._outer_colour, old_box._inner_colour);
	_CreateGLObjects();
}

// Destructor
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

void Box::Translate(int x, int y)
{
	_SetValues(_xsize, _ysize, _xpos + x, _xpos + y);
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
	if (!_ready)
		_CreateGLObjects();

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
	_ready = false;
}

bool Box::_Assert()
{
	if (_xsize < 5)
	{
		printf("Box (_Assert): invalid _xsize (%d).\n", _xsize);
		return false;
	}
	if (_ysize < 5)
	{
		printf("Box (_Assert): invalid _ysize (%d).\n", _ysize);
		return false;
	}

	return true;
		
	// assert(_xsize > 4 && "Box has invalid xsize");
	// assert(_ysize > 4 && "Box has invalid ysize");
	// assert(_xpos >= 0 && _xpos <= 800 && "Box has invalid xpos");
	// assert(_ypos >= 0 && _ypos <= 800 && "Box has invalid ypos");
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
	// object origin at bottom left corner
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

	return vertices;
}

void Box::_CreateGLObjects()
{
	if (!_Assert())
	{
		printf("Box (_CreateGLObjects): failed _Assert, did not create objects.\n");
		return;
	}

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

	_ready = true;
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

// Testing methods
void Test::_CreateBoxTest()
{
	Box::SetVertexAttributes(_vertex_position, _vertex_colour);
	box_objects = new Box[10];
	box_objects[0] = Box();
	box_objects[1] = Box(100, 200, 0, 600);
	box_objects[2] = Box(100, 100, 100, 700, CYAN, RED);
	box_objects[3] = Box(box_objects[2]);
	box_objects[3].SetXPosition(200);
	box_objects[4] = Box(box_objects[2]);
	box_objects[4].SetYPosition(600);
	box_objects[5] = Box(10, 10, 700, 0, LIGHTBLUE, WHITE);
	box_objects[5].SetXSize(100);
	box_objects[6] = Box(box_objects[5]);
	box_objects[6].SetYSize(100);
	box_objects[7] = Box(150, 150, 400, 400, PINK, YELLOW);
	box_objects[7].Translate(250, 250);
	box_objects[8] = Box(150, 150, 300, 300);
	box_objects[8].SetInnerColour(ORANGE);
	box_objects[8].SetOuterColour(GOLD);
	box_objects[9] = Box();
}

void Test::_DisplayBoxTest()
{
	for (int i = 0; i < 9; i++)
		box_objects[i].Draw(0, 0);
	box_objects[9].Draw(20, 20);
}