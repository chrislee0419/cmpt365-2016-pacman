#include "Button.h"

// Constructors
Button::Button()
{
	box = Box();
	// test = Test();
}

Button::Button(int xsize, int ysize, int xpos, int ypos, std::string text)
{
	box = Box(xsize, ysize, xpos, ypos);
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
	return box.GetYSize;
}

int Button::GetXPosition()
{
	return box.GetXPosition;
}

int Button::GetYPosition()
{
	return box.GetYPosition;
}

//Setter methods
void Button::SetXSize(int x)
{
	box.SetXSize = x;
}

void Button::SetYSize(int y)
{
	box.SetYSize = y;
}

void Button::SetXPosition(int x)
{
	box.SetXPosition = x;
}

void Button::SetYPosition(int y)
{
	box.SetYPosition = y;
}

void Button::SetText(std::string text)
{
	// do something with text class
}

// checks mouse to see if over a button
void Button::CheckMousePosition(int x, int y)
{
	if ((x < GetXPosition() + GetXSize() && x > GetXPosition())
		&& (y < GetYPosition() + GetYSize() && y > GetYPosition()))
		box.SetColour(BLACK, WHITE);
}