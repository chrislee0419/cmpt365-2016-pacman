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
	FT_Library ft;
	FT_Face face;
	std::map<char, Character> _characters;
	std::string _text;
	int _xpos;
	int _ypos;
	int _size;
	int _font;

	void _Init(int font, int size, std::string text, int xpos, int ypos);
	bool _Assert();
	bool _PrepareFT();
	void _DestroyFT();

public:
	Text();
	Text(std::string text, int xpos, int ypos);
	Text(int font, int size, std::string text, int xpos, int ypos);
	~Text();

	void SetFont(int font);
	void SetSize(int size);
	void SetText(std::string text);
	void SetXPosition(int xpos);
	void SetYPosition(int ypos);
	void SetPosition(int xpos, int ypos);
	static void SetShader(const Shader shader);

	void Draw(int x_translate, int y_translate);

};
