
#include "Text.h"
#include "..\..\test\test.h"
#include "..\..\test\_util.h"

using std::string;

// Globals
Shader Text::_shader;

// Constructors
Text::Text()
{
	_Init(0, 12, "Text", 0, 0);
	_PrepareFT();
}

Text::Text(string text, int xpos, int ypos)
{
	_Init(0, 12, text, xpos, ypos);
	if (!_Assert())
		throw std::invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
	_PrepareFT();
}

Text::Text(int font, int size, string text, int xpos, int ypos)
{
	_Init(font, size, text, xpos, ypos);
	if (!_Assert())
		throw std::invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
	_PrepareFT();
}

// Destructor
Text::~Text() {}

// Setter methods
void Text::SetFont(int font)
{
	_font = font;
}

void Text::SetSize(int size)
{

}

void Text::SetText(string text)
{
	_text = text;
}

void Text::SetXPosition(int xpos)
{
	_xpos = xpos;
}

void Text::SetYPosition(int ypos)
{
	_ypos = ypos;
}

void Text::SetPosition(int xpos, int ypos)
{
	_xpos = xpos;
	_ypos = ypos;
}

void Text::SetShader(Shader shader)
{
	_shader = shader;

	_shader.UseShader();
}

// Rendering method
void Text::Draw(int x_translate, int y_translate)
{
	_shader.UseShader();
}

// Private helper methods
void Text::_Init(int font, int size, string text, int xpos, int ypos)
{
	SetFont(font);
	SetPosition(xpos, ypos);
	SetText(text);
	SetSize(size);
}

bool Text::_Assert()
{
	if ( !(_font == 0 || _font == 1) )
	{
		printf("Text [WARNING]: _Assert found invalid _font (%d).\n", _font);
		return false;
	}
	if (_size < 8)
	{
		printf("Text [WARNING]: _Assert found invalid _size (%d).\n", _size);
		return false;
	}

	return true;
}

// Prepare Freetype library and faces
bool Text::_PrepareFT()
{
	if (FT_Init_FreeType(&ft))
	{
		printf("Text [ERROR]: could not initialize FT_Library\n");
		return false;
	}
	// Prepares font faces
	if (_font == 0)
	{
		if (FT_New_Face(ft, "depend/fonts/Roboto.ttf", 0, &face))
		{
			printf("Text [WARNING]: could not load Roboto font\n");
			return false;
		}
	}
	else if (_font == 1)
	{
		if (FT_New_Face(ft, "depend/fonts/Ubuntu.ttf", 0, &face))
		{
			printf("Text [WARNING]: could not load Ubuntu font\n");
			return false;
		}
	}
	return true;
}

void Text::_DestroyFT()
{
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}
