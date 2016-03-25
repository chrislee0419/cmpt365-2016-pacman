
#include "test.h"

// Globals
GLuint Test::_vertex_position;
GLuint Test::_vertex_colour;
GLuint Test::_vao;
GLuint Test::_pos_vbo;
GLuint Test::_col_vbo;

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

void Test::StaticTest()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(1, &_pos_vbo);
	glGenBuffers(1, &_col_vbo);
	glm::vec4 vertices[3] = { glm::vec4(0, 0, 0, 1), glm::vec4(800, 0, 0, 1), glm::vec4(0, 800, 0, 1) };
	glBindBuffer(GL_ARRAY_BUFFER, _pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec4), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(_vertex_position, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_vertex_position);
	glm::vec4 colours[3] = { glm::vec4(1, 0, 0, 1), glm::vec4(0, 1, 0, 1), glm::vec4(0, 0, 1, 1) };
	glBindBuffer(GL_ARRAY_BUFFER, _col_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec4), colours, GL_STATIC_DRAW);
	glVertexAttribPointer(_vertex_colour, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_vertex_colour);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Test::StaticTestDisplay()
{
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}