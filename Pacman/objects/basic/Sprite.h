
#pragma once

#include "..\..\depend\SOIL\SOIL.h"
#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"
#include "..\..\shaders\Shader.h"

class Sprite
{
private:
	static Shader _shader;
	GLuint _vao;
	GLuint _vbo;

public:
	Sprite();
	~Sprite();

	void LoadTexture(std::string sprite);
};