
#include "Button.h"

#include <vector>

class Menu
{
private:
	std::vector<Button> m_buttons;
	int m_xsize, m_ysize, m_xpos, m_ypos;

public:
	Menu();
	Menu(int xsize, int ysize, int xpos, int ypos);
	~Menu();

};