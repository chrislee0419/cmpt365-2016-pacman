
#include "Text.h"
#include "..\..\test\test.h"
#include "..\..\test\_util.h"

using std::string;

// Globals
FT_Library Text::ft;

// Constructors
Text::Text() {}

// Destructor
Text::~Text() {}

// Setter methods
void Text::SetFont(int font)
{
	_SetFont(font);
}

void Text::SetText(string text)
{

}

// Prepare Freetype library
bool Text::PrepareLibrary()
{
	if ( FT_Init_FreeType(&ft) )
		return false;
	return true;
}

// Rendering method
void Text::Draw(int x_translate, int y_translate)
{

}

// Private helper methods

void Text::_SetFont(int font)
{

}