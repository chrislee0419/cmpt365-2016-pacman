
#include "Button.h"

#include "..\_colours.h"

#include <iostream>

using namespace std;
using glm::vec4;

// Constructors
Button::Button()
{
	_box = Box(200, 50, 0, 0);
	_text = Text("Button");

	_AdjustTextSize();
	_CentreText();

	SetDefaultColours(BLUE, BLACK, WHITE);
	SetHoverColours(BLUE, WHITE, BLACK);
}

Button::Button(int xsize, int ysize, int xpos, int ypos, string text)
{
	_box = Box(xsize, ysize, xpos, ypos);
	_text = Text(text);

	_AdjustTextSize();
	_CentreText();

	SetDefaultColours(BLUE, BLUE, WHITE);
	SetHoverColours(LIGHTBLUE, BLUE, WHITE);
}

Button::Button(	int xsize, int ysize, int xpos, int ypos, string text,
				vec4 outer_colour, vec4 inner_colour,
				vec4 outer_colour_hover, vec4 inner_colour_hover,
				vec4 text_colour, vec4 text_colour_hover)
{
	_box = Box(xsize, ysize, xpos, ypos);
	_text = Text(text);

	_AdjustTextSize();
	_CentreText();

	SetDefaultColours(outer_colour, inner_colour, text_colour);
	SetHoverColours(outer_colour_hover, inner_colour_hover, text_colour_hover);
}

// Destructor
Button::~Button() {}

// Getter methods
int Button::GetXSize() { return _box.GetXSize(); }

int Button::GetYSize() { return _box.GetYSize(); }

int Button::GetXPosition() { return _box.GetXPosition(); }

int Button::GetYPosition() { return _box.GetYPosition(); }

//Setter methods
void Button::SetXSize(int x)
{
	_box.SetXSize(x);
	_AdjustTextSize();
	_CentreText();
}

void Button::SetYSize(int y)
{
	_box.SetYSize(y);
	_AdjustTextSize();
	_CentreText();
}

void Button::SetXPosition(int x)
{
	_box.SetXPosition(x);
	_AdjustTextSize();
	_CentreText();
}

void Button::SetYPosition(int y)
{
	_box.SetYPosition(y);
	_AdjustTextSize();
	_CentreText();
}

void Button::SetText(string text)
{
	_text.SetText(text);
	_AdjustTextSize();
	_CentreText();
}

void Button::SetFont(int font)
{
	_text.SetFont(font);
	_AdjustTextSize();
	_CentreText();
}

void Button::SetDefaultColours(vec4 outer_colour, vec4 inner_colour, vec4 text_colour)
{
	_outer_colour = outer_colour;
	_inner_colour = inner_colour;
	_text_colour = text_colour;
}

void Button::SetHoverColours(vec4 outer_colour, vec4 inner_colour, vec4 text_colour)
{
	_outer_colour_hover = outer_colour;
	_inner_colour_hover = inner_colour;
	_text_colour_hover = text_colour;
}

void Button::Translate(int x, int y)
{
	_box.Translate(x, y);
	_text.Translate(x, y);
}

bool Button::CheckMousePosition(int x, int y)
{
	int xpos = GetXPosition();
	int xsize = GetXSize();
	int ypos = GetYPosition();
	int ysize = GetYSize();

	if ((x < xpos + xsize && x > xpos)
		&& (y < ypos + ysize && y > ypos))
		return true;
	else
		return false;
}

// Rendering methods
void Button::Draw(bool hover) { Draw(0, 0, hover); }
void Button::Draw(int x_translate, int y_translate, bool hover)
{
	if (hover)
	{
		_box.SetColour(_outer_colour_hover, _inner_colour_hover);
		_text.SetColour(_text_colour_hover);
	}	
	else
	{
		_box.SetColour(_outer_colour, _inner_colour);
		_text.SetColour(_text_colour);
	}

	_box.Draw(x_translate, y_translate);
	_text.Draw(x_translate, y_translate);
}

// private helper methods
void Button::_AdjustTextSize()
{
	int w = (int)_text.GetWidth();
	int h = (int)_text.GetHeight();

	int b = 2 * _box.GetBorderSize();
	int xsize = _box.GetXSize() - b;
	int ysize = _box.GetYSize() - b;

	// enlarge until out-of-bounds
	while (w < xsize || h < ysize)
	{
		_text.SetSize(_text.GetSize() + 0.1f);

		w = (int)_text.GetWidth();
		h = (int)_text.GetHeight();
	}
	// shrink until in-bounds
	while (w > xsize || h > ysize)
	{
		float size = _text.GetSize();
		if ((size -= 0.1f) < 0.0f)
			return;
		_text.SetSize(size);

		w = (int)_text.GetWidth();
		h = (int)_text.GetHeight();
	}
}

void Button::_CentreText()
{
	int w = (int)_text.GetWidth();
	int h = (int)_text.GetHeight();

	int xsize = _box.GetXSize();
	int ysize = _box.GetYSize();
	int xpos = _box.GetXPosition();
	int ypos = _box.GetYPosition();

	_text.SetPosition(xpos + (xsize/2) - (w/2), ypos + (ysize/2) - (h/2));
}
