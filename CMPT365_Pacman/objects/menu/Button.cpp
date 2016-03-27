#include "Button.h"

// Constructors
Button::Button()
{
	box = Box();
	_SetDefaultColours();
	// text = Text();
}

Button::Button(int xsize, int ysize, int xpos, int ypos, std::string text)
{
	box = Box(xsize, ysize, xpos, ypos);
	_SetDefaultColours();
	// change text when Text class finished
}

// Destructor
Button::~Button()
{
}

// Getter methods
int Button::GetXSize()
{
	return box.GetXSize();
}

int Button::GetYSize()
{
	return box.GetYSize();
}

int Button::GetXPosition()
{
	return box.GetXPosition();
}

int Button::GetYPosition()
{
	return box.GetYPosition();
}

//Setter methods
void Button::SetXSize(int x)
{
	box.SetXSize(x);
}

void Button::SetYSize(int y)
{
	box.SetYSize(y);
}

void Button::SetXPosition(int x)
{
	box.SetXPosition(x);
}

void Button::SetYPosition(int y)
{
	box.SetYPosition(y);
}

void Button::SetText(std::string text)
{
	// do something with text class
}

void Button::SetColours(glm::vec4 inner_colour, glm::vec4 outer_colour)
{
	// to change the non-highlighted colours
	_SetColours(inner_colour, outer_colour);
}

void Button::SetHoverColours(glm::vec4 inner_colour_hover, glm::vec4 outer_colour_hover)
{
	// to change the highlighted colours
	_SetHoverColours(inner_colour_hover, outer_colour_hover);
}

// Private helper methods
void Button::_SetDefaultColours()
{
	// white = highlighted
	_outer_colour = BLACK;
	_inner_colour = DARKBLUE;
	// dark blue = not highlighted
	_outer_colour_hover = BLACK;
	_inner_colour_hover = WHITE;
}

void Button::_SetColours()
{
	// changes to the current non-highlighted colours
	box.SetColour(_outer_colour, _inner_colour);
}

void Button::_SetColours(glm::vec4 outer_colour, glm::vec4 inner_colour)
{
	// helper function to change non-highlighted colours
	_outer_colour = outer_colour;
	_inner_colour = inner_colour;
}

void Button::_SetHoverColours()
{
	// changes to the current highlighted colours
	box.SetColour(_outer_colour_hover, _inner_colour_hover);
}

void Button::_SetHoverColours(glm::vec4 outer_colour_hover, glm::vec4 inner_colour_hover)
{
	// helper function to change highlighted colours
	_outer_colour_hover = outer_colour_hover;
	_inner_colour_hover = inner_colour_hover;
}

void Button::Translate(int x, int y)
{
	box.Translate(x, y);
}

void Button::CheckMousePosition(int x, int y)
{
	if ((x < GetXPosition() + GetXSize() && x > GetXPosition())
		&& (y < GetYPosition() + GetYSize() && y > GetYPosition()))
		_SetHoverColours();
	else
		_SetColours();
}

void Button::Draw()
{
	// call Draw functions from Box and Text?
}