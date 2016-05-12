
#include "Button.h"

#include "..\_colours.h"
#include "..\test.h"

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

	SetDefaultColours(BLUE, BLUE, WHITE);
	SetHoverColours(LIGHTBLUE, BLUE, WHITE);
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

	if (x < xpos + xsize && x > xpos &&
		y < ypos + ysize && y > ypos)
		return true;
	else
		return false;
}

// Rendering methods
void Button::Draw(bool selected) { Draw(0, 0, selected); }
void Button::Draw(int x_translate, int y_translate, bool selected)
{
	if (selected)
		_HoverColours();
	else
		_DefaultColours();

	_box.Draw(x_translate, y_translate);
	_text.Draw(x_translate, y_translate);
}

// private helper methods
void Button::_DefaultColours()
{
	_box.SetColour(_outer_colour, _inner_colour);
	_text.SetColour(_text_colour);
}

void Button::_HoverColours()
{
	_box.SetColour(_outer_colour_hover, _inner_colour_hover);
	_text.SetColour(_text_colour_hover);
}

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

// Testing methods

#define NUM_OF_TESTS 3

void Test::_CreateButtonTest()
{
	button_objects = (Button*)malloc(sizeof(Button)* NUM_OF_TESTS);
	button_select = (bool*)malloc(sizeof(bool)* NUM_OF_TESTS);

	button_objects[0] = Button();
	button_objects[1] = Button(100, 30, 400, 10, "Button #2");
	button_objects[2] = Button(	250, 150, 10, 400, "Third button",
								DARKGREY, DARKGREY, WHITE,
								WHITE, WHITE, BLACK);

	button_select[0] = true;
	button_select[1] = false;
	button_select[2] = false;

	_button_test = true;
}

void Test::_DisplayButtonTest()
{
	if (!_button_test)
		return;

	for (int i = 0; i < NUM_OF_TESTS; i++)
		button_objects[i].Draw(button_select[i]);
}

void Test::_PassiveMotionButtonTest(int x, int y)
{
	if (!_button_test)
		return;

	bool hit = false;
	bool store[NUM_OF_TESTS] = { false };
	for (int i = 0; i < NUM_OF_TESTS; i++)
		hit = hit || (store[i] = button_objects[i].CheckMousePosition(x, y));

	if (hit) for (int i = 0; i < NUM_OF_TESTS; i++)
		button_select[i] = store[i];
}

void Test::_MouseButtonTest(int button, int state, int x, int y)
{
	if (!_button_test)
		return;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		for (int i = 0; i < NUM_OF_TESTS; i++)
		{
			if (button_objects[i].CheckMousePosition(x, y))
			{
				printf("MouseButtonTest: pressed button #%d\n", i);
				return;
			}
		}
	}
}

void Test::_KeyboardButtonTest(unsigned char key, int x, int y)
{
	if (!_button_test)
		return;

	if (key == '\n' || key == ' ')
	{
		for (int i = 0; i < NUM_OF_TESTS; i++)
		{
			if (button_select[i])
			{
				printf("KeyboardButtonTest: selected button #%d\n", i);
				return;
			}
		}
	}

}

void Test::_SpecialButtonTest(int key, int x, int y)
{
	if (!_button_test)
		return;

	for (int i = 0; i < NUM_OF_TESTS; i++)
	{
		if (button_objects[i].CheckMousePosition(x, y))
			return;
	}
	
	switch (key)
	{
	case GLUT_KEY_UP:
		button_select[0] = false;
		button_select[1] = false;
		button_select[2] = true;
		printf("Pressed \"up\"\n");
		break;

	case GLUT_KEY_DOWN:
		if (button_select[2])
		{
			button_select[0] = true;
			button_select[2] = false;
		}
		printf("Pressed \"down\"\n");
		break;

	case GLUT_KEY_LEFT:
		if (button_select[1])
		{
			button_select[0] = true;
			button_select[1] = false;
		}
		printf("Pressed \"left\"\n");
		break;

	case GLUT_KEY_RIGHT:
		button_select[0] = false;
		button_select[1] = true;
		button_select[2] = false;
		printf("Pressed \"right\"\n");
	}
}
