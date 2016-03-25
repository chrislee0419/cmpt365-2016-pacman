
#pragma once

#include <iostream>
#include <stdexcept>

#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"

class Text
{
private:
	std::string _text;
	void *_font;

public:
	Text();
	Text(std::string text);
	Text(void *font, std::string text);
	void SetFont(void *font);
	void SetText(std::string text);
	void Draw(int x_translate, int y_translate);
};