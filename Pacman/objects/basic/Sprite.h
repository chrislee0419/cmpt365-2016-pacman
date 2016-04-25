
#pragma once

#include "..\..\depend\SOIL\SOIL.h"
#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"
#include "..\..\shaders\Shader.h"

class Sprite
{
private:
	static Shader _shader;
	static GLuint _vao;
	static GLuint _vbo;
	int _w, _h;
	unsigned char* _tex;

	void _PrepareGLObjects();

public:
	Sprite();
	Sprite(std::string texture);
	~Sprite();

	void LoadTexture(std::string texture);

	void Prepare(Shader shader);

	void Draw(int x_translate, int y_translate);
};