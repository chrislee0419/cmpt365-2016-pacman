#pragma once

#include <iostream>
#include <stdexcept>

#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"
#include "..\..\depend\glm\vec4.hpp"
#include "..\_colours.h"
#include "Box.h"
#include "Text.h"

class Button
{
private:
	Box box;
	// Text text;
	// callback function missing

public:
	Button();
	Button(int xsize, int ysize, int xpos, int ypos, std::string text);
	~Button();

	int GetXSize();
	int GetYSize();
	int GetXPosition();
	int GetYPosition();

	void SetText(std::string text);
	void SetXSize(int x);
	void SetYSize(int y);
	void SetXPosition(int x);
	void SetYPosition(int y);

	void CheckMousePosition(int x, int y);

};

