#pragma once

#include <iostream>

class Button
{
private:
	int _xsize, _ysize, _xpos, _ypos;

public:
	Button();
	Button(int xsize, int ysize, int xpos, int ypos, std::string text);
	~Button();
};

