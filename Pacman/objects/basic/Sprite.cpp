#include "Sprite.h"
#include "..\test.h"
#include "..\_util.h"

using namespace std;

// Globals
Shader Sprite::_shader;
GLuint Sprite::_vao;
GLuint Sprite::_vbo;

// Constructor
Sprite::Sprite()
{

}

// Destructor
Sprite::~Sprite()
{

}

void Sprite::LoadTexture(std::string sprite)
{

}

void Sprite::Prepare(Shader shader)
{
	_shader = shader;
	_shader.UseShader();
	_PrepareGLObjects();
}

void Sprite::_PrepareGLObjects()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 6 * 4, NULL, GL_DYNAMIC_DRAW);
	GLuint attrib = glGetAttribLocation(_shader.GetProgram(), "vertex");
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(attrib);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	printf("Prepared OpenGL objects for Sprite objects: VAO = %d, VBO = %d\n", _vao, _vbo);
}

// Testing methods
//void Test::_DisplaySpriteTest()
//{
//
//}