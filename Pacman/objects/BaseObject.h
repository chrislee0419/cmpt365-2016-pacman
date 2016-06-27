
#pragma once

class BaseObject
{
protected:
	int _xpos, _ypos;

public:
	BaseObject() : _xpos(0), _ypos(0) {}
	~BaseObject() {}

	virtual void Draw() { }
	virtual void Draw(int x, int y) { }
};
