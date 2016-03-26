
#pragma once

#include <iostream>
#include <stdexcept>

#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"
#include "..\..\depend\freetype\ft2build.h"
#include "..\..\depend\freetype\freetype\freetype.h"
#include "..\..\depend\freetype\freetype\ftglyph.h"

class Text
{
private:
	static FT_Library ft;
	FT_Face face;
	std::string _text;
	int _xpos;
	int _ypos;

public:
	Text();
	Text(std::string text, int xpos, int ypos);
	Text(void *font, std::string text, int xpos, int ypos);
	~Text();

	void SetFont(void *font);
	void SetText(std::string text);
	void SetXPosition(int xpos);
	void SetYPosition(int ypos);
	void SetPosition(int xpos, int ypos);

	void Draw(int x_translate, int y_translate);

	static void PrepareFontLibrary();
};