
#include "test.h"

// Globals
GLuint Test::_vertex_position;
GLuint Test::_vertex_colour;

// Constructor
Test::Test() {}

// Destructor
Test::~Test()
{
	//delete[] box_objects;
	free(box_objects);
}

void Test::SetupTest()
{
	_CreateBoxTest();
}

void Test::DisplayTest()
{
	_DisplayBoxTest();
}

void Test::SetVertexAttributes(GLuint vertex_position, GLuint vertex_colour)
{
	_vertex_position = vertex_position;
	_vertex_colour = vertex_colour;
}