
#pragma once

#include <iostream>
#include <stdexcept>

#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"
#include "..\..\depend\glm\vec4.hpp"
#include "Box.h"
#include "Text.h"

class Button
{
private:
	glm::vec4 _outer_colour, _inner_colour, _outer_colour_hover, _inner_colour_hover;
	glm::vec4 _text_colour, _text_colour_hover;

	Box _box;
	Text _text;

	void _DefaultColours();
	void _HoverColours();

	void _AdjustTextSize();
	void _CentreText();

public:
	Button();
	Button(int xsize, int ysize, int xpos, int ypos, std::string text);
	Button(int xsize, int ysize, int xpos, int ypos, std::string text,
		glm::vec4 outer_colour, glm::vec4 inner_colour, glm::vec4 text_colour,
		glm::vec4 outer_colour_hover, glm::vec4 inner_colour_hover,glm::vec4 text_colour_hover);
	~Button();

	int GetXSize();
	int GetYSize();
	int GetXPosition();
	int GetYPosition();

	void SetText(std::string text);
	void SetFont(int font);
	void SetXSize(int x);
	void SetYSize(int y);
	void SetXPosition(int x);
	void SetYPosition(int y);
	void Select(bool select);
	void SetDefaultColours(glm::vec4 outer_colour, glm::vec4 inner_colour, glm::vec4 text_colour);
	void SetHoverColours(glm::vec4 outer_colour, glm::vec4 inner_colour, glm::vec4 text_colour);
	void Translate(int x, int y);

	bool CheckMousePosition(int x, int y);

	void Draw(bool selected);
	void Draw(int x_translate, int y_translate, bool selected);

};