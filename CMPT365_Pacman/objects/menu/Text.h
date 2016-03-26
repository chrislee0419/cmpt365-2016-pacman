/*
//	for CMPT 365 Term Project
//	by Chris Lee - cla235
*/

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"
#include "..\..\depend\freetype\ft2build.h"
#include FT_FREETYPE_H

class Text
{
private:
	static FT_Library ft;
	FT_Face face;
	std::string _text;
	int _xpos;
	int _ypos;

	void _Init();
	void _SetFont(int font);

public:
	Text();
	Text(std::string text, int xpos, int ypos);
	Text(int font, std::string text, int xpos, int ypos);
	~Text();

	void SetFont(int font);
	void SetText(std::string text);
	void SetXPosition(int xpos);
	void SetYPosition(int ypos);
	void SetPosition(int xpos, int ypos);
	static bool PrepareLibrary();

	void Draw(int x_translate, int y_translate);

};
