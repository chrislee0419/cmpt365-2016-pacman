/*
//	for CMPT 365 Term Project
//	by Chris Lee - cla235
*/

#pragma once

#include <iostream>
#include <stdexcept>
#include <map>

#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"
#include "..\..\depend\freetype\ft2build.h"
#include FT_FREETYPE_H

#include "..\..\shaders\Shader.h"
#include "..\..\depend\glm\vec2.hpp"
#include "..\..\depend\glm\vec4.hpp"

struct Character
{
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class Text
{
private:
	static Shader _shader;
	GLuint _vao;
	GLuint _vbo;
	std::map<char, Character> _characters;
	std::string _text;
	glm::vec4 _colour;
	int _xpos;
	int _ypos;
	int _size;
	int _font;
	bool _ready;

	void _Init(int font, int size, std::string text, int xpos, int ypos, glm::vec4 colour);
	bool _Assert();
	void _CreateGLObjects();
	bool _PrepareFT();

public:
	Text();
	Text(std::string text, int xpos, int ypos);
	Text(int font, int size, std::string text, int xpos, int ypos);
	Text(std::string text, int xpos, int ypos, glm::vec4 colour);
	Text(int font, int size, std::string text, int xpos, int ypos, glm::vec4 colour);
	~Text();

	void SetFont(int font);
	void SetSize(int size);
	void SetText(std::string text);
	void SetColour(glm::vec4 colour);
	void SetXPosition(int xpos);
	void SetYPosition(int ypos);
	void SetPosition(int xpos, int ypos);
	static void SetShader(const Shader shader);

	void Draw(int x_translate, int y_translate);

};
