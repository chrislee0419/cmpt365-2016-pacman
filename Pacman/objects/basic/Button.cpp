
#include "Button.h"

#include "..\_colours.h"

#include <iostream>

// Constructors
Button::Button()
{
	_box = Box();
	// text = Text();
}

Button::Button(int xsize, int ysize, int xpos, int ypos, std::string text)
{
	_box = Box(xsize, ysize, xpos, ypos);
	// change text when Text class finished
}

// Destructor
Button::~Button()
{
}

// Getter methods
int Button::GetXSize() { return _box.GetXSize(); }

int Button::GetYSize() { return _box.GetYSize(); }

int Button::GetXPosition() { return _box.GetXPosition(); }

int Button::GetYPosition() { return _box.GetYPosition(); }

//Setter methods
void Button::SetXSize(int x)
{
	_box.SetXSize(x);
}

void Button::SetYSize(int y)
{
	_box.SetYSize(y);
}

void Button::SetXPosition(int x)
{
	_box.SetXPosition(x);
}

void Button::SetYPosition(int y)
{
	_box.SetYPosition(y);
}

void Button::SetText(std::string text)
{
	_text.SetText(text);
}

void Button::SetDefaultColours(glm::vec4 outer_colour, glm::vec4 inner_colour)
{
	_outer_colour = outer_colour;
	_inner_colour = inner_colour;
}

void Button::SetHoverColours(glm::vec4 outer_colour, glm::vec4 inner_colour)
{
	_outer_colour_hover = outer_colour;
	_inner_colour_hover = inner_colour;
}

void Button::Translate(int x, int y)
{
	_box.Translate(x, y);
	_text.Translate(x, y);
}

void Button::CheckMousePosition(int x, int y)
{
	int xpos = GetXPosition();
	int xsize = GetXSize();
	int ypos = GetYPosition();
	int ysize = GetYSize();

	if ((x < xpos + xsize && x > xpos)
		&& (y < ypos + ysize && y > ypos))
		_box.SetColour(_outer_colour_hover, _inner_colour_hover);
	else
		_box.SetColour(_outer_colour, _inner_colour);
}

// Rendering methods
void Button::Draw() { Draw(0, 0); }
void Button::Draw(int x_translate, int y_translate)
{
	_box.Draw(x_translate, y_translate);
	_text.Draw(x_translate, y_translate);
}
