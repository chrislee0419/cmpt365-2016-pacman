#include "Sprite.h"

#include "..\test.h"
#include "..\_util.h"
#include "..\_colours.h"

using namespace std;
using glm::vec4;

// Globals
Shader Sprite::_shader;
GLuint Sprite::_vao;
GLuint Sprite::_vbo;
bool Sprite::_ready = false;

// Constructor
Sprite::Sprite()
{
	_Init(0, 0, 400, 400, WHITE);
	LoadTexture(IMG_TEST1);
}

Sprite::Sprite(int texture_id)
{
	_Init(400, 400, 200, 200, WHITE);
	LoadTexture(texture_id);
}

Sprite::Sprite(int xpos, int ypos, int xsize, int ysize)
{
	_Init(xpos, ypos, xsize, ysize, WHITE);
	LoadTexture(IMG_TEST1);
}

Sprite::Sprite(int texture_id, int xpos, int ypos, int xsize, int ysize)
{
	_Init(xpos, ypos, xsize, ysize, WHITE);
	LoadTexture(texture_id);
}

Sprite::Sprite(int texture_id, vec4 colour)
{
	_Init(400, 400, 200, 200, colour);
	LoadTexture(texture_id);
}

Sprite::Sprite(int texture_id, int xpos, int ypos, int xsize, int ysize, vec4 colour)
{
	_Init(xpos, ypos, xsize, ysize, colour);
	LoadTexture(texture_id);
}

// Destructor
Sprite::~Sprite() {}

// public methods
void Sprite::SetXPosition(int xpos) { _xpos = xpos; }
void Sprite::SetYPosition(int ypos) { _ypos = ypos; }
void Sprite::SetPosition(int xpos, int ypos) { _xpos = xpos; _ypos = ypos; }

void Sprite::SetXSize(int xsize) { _xsize = xsize; }
void Sprite::SetYSize(int ysize) { _ysize = ysize; }
void Sprite::SetSize(int xsize, int ysize) { _xsize = xsize; _ysize = ysize; }

void Sprite::SetColour(vec4 colour) { _colour = colour; }

void Sprite::LoadTexture(int texture_id)
{
	_tex = ImageManager::RetrieveTexture(texture_id);
}

void Sprite::Prepare(Shader shader)
{
	_shader = shader;
	_shader.UseShader();
	_PrepareGLObjects();
	_ready = true;
}

// private helper methods
void Sprite::_Init(int xpos, int ypos, int xsize, int ysize, vec4 colour)
{
	_xpos = xpos;
	_ypos = ypos;
	_xsize = xsize;
	_ysize = ysize;
	_colour = colour;
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

glm::vec4* Sprite::_CreateVerticesArray()
{
	vec4 *vertices = (vec4*)malloc(sizeof(vec4)* 6);

	vertices[0] = vec4(_xpos,			_ypos,			0.0f, 1.0f);
	vertices[1] = vec4(_xpos + _xsize,	_ypos,			1.0f, 1.0f);
	vertices[2] = vec4(_xpos,			_ypos + _ysize, 0.0f, 0.0f);
	vertices[3] = vec4(_xpos,			_ypos + _ysize,	0.0f, 0.0f);
	vertices[4] = vec4(_xpos + _xsize,	_ypos,			1.0f, 1.0f);
	vertices[5] = vec4(_xpos + _xsize,	_ypos + _ysize,	1.0f, 0.0f);

	return vertices;
}

// Rendering method
void Sprite::Draw(int x_translate, int y_translate)
{
	if (glIsTexture(_tex) == GL_FALSE)
	{
		printf("Sprite [WARNING]: attempted to Draw with an invalid texture (%d)\n", _tex);
		return;
	}
	else if (!_ready)
	{
		printf("Sprite [WARNING]: Sprite class is not ready\n");
		return;
	}

	int old_xpos = _xpos;
	int old_ypos = _ypos;
	if (x_translate != 0 || y_translate != 0)
	{
		_xpos += x_translate;
		_ypos += y_translate;
	}

	glUniform4f(glGetUniformLocation(_shader.GetProgram(), "spriteColour"),
		_colour.x, _colour.y, _colour.z, _colour.w);

	// push vertices to buffer
	vec4 *vertices = _CreateVerticesArray();
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(vec4), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	free(vertices);

	// draw
	_shader.UseShader();
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);
	glBindTexture(GL_TEXTURE_2D, _tex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	_xpos = old_xpos;
	_ypos = old_ypos;
}

// Testing methods

#define NUM_OF_TESTS 34

void Test::_CreateSpriteTest()
{
	sprite_objects = (Sprite*)malloc(sizeof(Sprite)* NUM_OF_TESTS);

	sprite_objects[0] = Sprite();
	sprite_objects[1] = Sprite(IMG_TEST2, 500, 500, 100, 100);
	sprite_objects[2] = Sprite(IMG_TEST3, 0, 400, 400, 400, CYAN);

	for (int i = 0; i < 31; i++)
		sprite_objects[i+3] = Sprite(i+3, 400 + 40 * (i % 10), 40 * (i / 10), 40, 40);

	_sprite_test = true;
}

void Test::_DisplaySpriteTest()
{
	if (!_sprite_test)
		return;

	for (int i = 0; i < NUM_OF_TESTS; i++)
		sprite_objects[i].Draw(0, 0);
}
