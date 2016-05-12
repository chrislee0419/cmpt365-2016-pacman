
#include <iostream>
#include <stdexcept>

#include "Text.h"
#include "..\test.h"
#include "..\_util.h"

#if DEBUG
#define UBUNTU_PATH "depend/fonts/Ubuntu.ttf"
#define ROBOTO_PATH "depend/fonts/Roboto.ttf"
#define EMULOGIC_PATH "depend/fonts/emulogic.ttf"
#else
#define UBUNTU_PATH "fonts/Ubuntu.ttf"
#define ROBOTO_PATH "fonts/Roboto.ttf"
#define EMULOGIC_PATH "fonts/emulogic.ttf"
#endif

using namespace std;

// Globals
Shader Text::_shader = Shader();
map<char, Character> Text::_roboto;
map<char, Character> Text::_ubuntu;
map<char, Character> Text::_emulogic;
GLuint Text::_vao = 0;
GLuint Text::_vbo = 0;
bool Text::_ready = false;

// Constructors
Text::Text()
{
	_Init(EMULOGIC, 2, "Text", 0, 0, WHITE);
}

Text::Text(string text)
{
	_Init(EMULOGIC, 2, text, 0, 0, WHITE);
}

Text::Text(string text, glm::vec4 colour)
{
	_Init(EMULOGIC, 2, text, 0, 0, colour);
}

Text::Text(int font, float size, string text, glm::vec4 colour)
{
	_Init(font, size, text, 0, 0, colour);
	if (!_Assert())
		throw invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

Text::Text(string text, int xpos, int ypos)
{
	_Init(EMULOGIC, 2, text, xpos, ypos, WHITE);
	if (!_Assert())
		throw invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

Text::Text(int font, float size, string text, int xpos, int ypos)
{
	_Init(font, size, text, xpos, ypos, WHITE);
	if (!_Assert())
		throw invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

Text::Text(string text, int xpos, int ypos, glm::vec4 colour)
{
	_Init(EMULOGIC, 2, text, xpos, ypos, colour);
	if (!_Assert())
		throw invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

Text::Text(int font, float size, string text, int xpos, int ypos, glm::vec4 colour)
{
	_Init(font, size, text, xpos, ypos, colour);
	if (!_Assert())
		throw invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

Text::Text(const Text &copytext)
{
	_Init(copytext._font, copytext._size, copytext._text, copytext._xpos, copytext._ypos, copytext._colour);
	if (!_Assert())
		throw invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

// Destructor
Text::~Text() {}

// Getter methods
float Text::GetHeight()
{
	float max_height = -1.0;
	int iter = 0;
	char c = _text[iter];

	while (c != NULL)
	{
		Character ch;
		if (_font == ROBOTO)
			ch = _roboto[c];
		else if (_font == UBUNTU)
			ch = _ubuntu[c];
		else if (_font == EMULOGIC)
			ch = _emulogic[c];
		else
		{
			max_height = -1.0;
			break;
		}

		float h;
		if (max_height < (h = (ch.Size.y * _size)))
			max_height = h;

		c = _text[++iter];
	}

	if (max_height < 0)
		printf("Text [WARNING]: error occurred in GetHeight().\n");

	return max_height;
}

float Text::GetWidth()
{
	float width = 0.0f;
	int iter = 0;
	char c = _text[iter];

	while (c != NULL)
	{
		Character ch;
		if (_font == ROBOTO)
			ch = _roboto[c];
		else if (_font == UBUNTU)
			ch = _ubuntu[c];
		else if (_font == EMULOGIC)
			ch = _emulogic[c];
		else
		{
			width = -1.0;
			break;
		}

		width += (ch.Advance >> 6) * _size;

		c = _text[++iter];
	}

	if (width < 0)
		printf("Text [WARNING]: error occurred in GetWidth().\n");

	return width;
}

float Text::GetSize() { return _size; }

// Setter methods
void Text::SetFont(int font)
{
	if (font == ROBOTO || font == UBUNTU || font == EMULOGIC)
		_font = font;
	else
		printf("Text [WARNING]: SetFont recieved an invalid font.\n");
	
}

void Text::SetSize(float size)
{
	if (size > 0)
		_size = size;
	else
		printf("Text [WARNING]: SetSize recieved an invalid size.\n");
}

void Text::SetText(string text)
{
	strncpy_s(_text, text.c_str(), 200);
	_text[200] = '\0';
}

void Text::SetColour(glm::vec4 colour) { _colour = colour; }

void Text::SetXPosition(int xpos) { _xpos = xpos; }

void Text::SetYPosition(int ypos) { _ypos = ypos; }

void Text::SetPosition(int xpos, int ypos) { _xpos = xpos; _ypos = ypos; }

void Text::Translate(int x, int y) { _xpos += x; _ypos += y; }

// Creates FreeType fonts and GL objects, sets shader program
void Text::Prepare(Shader shader)
{
	_shader = shader;
	_shader.UseShader();
	_PrepareFT();
	_CreateGLObjects();
}

// Destroy GL objects
void Text::Cleanup()
{
	if (glIsBuffer(_vbo) == GL_TRUE)
		glDeleteBuffers(1, &_vbo);
	if (glIsVertexArray(_vao) == GL_TRUE)
		glDeleteVertexArrays(1, &_vao);
	_ready = false;
}

// Rendering method
void Text::Draw() { Draw(0, 0); }
void Text::Draw(int x_translate, int y_translate)
{
	_shader.UseShader();

	if (!_ready)
		_CreateGLObjects();

	glUniform4f(glGetUniformLocation(_shader.GetProgram(), "textColour"),
		_colour.x, _colour.y, _colour.z, _colour.w);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	
	float xpos = (float)_xpos;
	float ypos = (float)_ypos;

	int iter = 0;
	char c = _text[iter];
	while (c != NULL)
	{
		Character ch;
		if (_font == ROBOTO)
			ch = _roboto[c];
		else if (_font == UBUNTU)
			ch = _ubuntu[c];
		else if (_font == EMULOGIC)
			ch = _emulogic[c];
		else
			return;

		GLfloat x_position = xpos + x_translate + ch.Bearing.x * _size;
		GLfloat y_position = ypos + y_translate - (ch.Size.y - ch.Bearing.y) * _size;
		GLfloat w = ch.Size.x * _size;
		GLfloat h = ch.Size.y * _size;

		GLfloat vertices[6][4] = {
			{ x_position,		y_position + h, 0.0, 0.0 },
			{ x_position,		y_position,		0.0, 1.0 },
			{ x_position + w,	y_position,		1.0, 1.0 },

			{ x_position,		y_position + h, 0.0, 0.0 },
			{ x_position + w,	y_position,		1.0, 1.0 },
			{ x_position + w,	y_position + h, 1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		xpos += (ch.Advance >> 6) * _size;
		c = _text[++iter];
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Private helper methods
void Text::_Init(int font, float size, string text, int xpos, int ypos, glm::vec4 colour)
{
	_font = font;
	_size = size;
	SetPosition(xpos, ypos);
	SetText(text);
	SetColour(colour);
}

bool Text::_Assert()
{
	if ( !(_font == ROBOTO || _font == UBUNTU || _font == EMULOGIC) )
	{
		printf("Text [WARNING]: _Assert found invalid _font (%d).\n", _font);
		return false;
	}
	if (_size <= 0)
	{
		printf("Text [WARNING]: _Assert found invalid _size (%d).\n", _size);
		return false;
	}

	return true;
}

void Text::_CreateGLObjects()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 6 * 4, NULL, GL_DYNAMIC_DRAW);
	GLuint attrib = glGetAttribLocation(_shader.GetProgram(), "vertex");
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(attrib);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	_ready = true;
	printf("Prepared OpenGL objects for Text objects: VAO = %d, VBO = %d\n", _vao, _vbo);
}

// Prepare Freetype library and faces
void Text::_PrepareFT()
{
	FT_Library ft;
	FT_Face roboto_face, ubuntu_face, emulogic_face;

	if (FT_Init_FreeType(&ft))
		throw runtime_error("Text [ERROR]: could not initialize FT_Library.");

	// Prepares font faces
	if (FT_New_Face(ft, ROBOTO_PATH, 0, &roboto_face))
		throw runtime_error("Text [ERROR]: could not load Roboto font.");
	if (FT_New_Face(ft, UBUNTU_PATH, 0, &ubuntu_face))
		throw runtime_error("Text [ERROR]: could not load Ubuntu font.");
	if (FT_New_Face(ft, EMULOGIC_PATH, 0, &emulogic_face))
		throw runtime_error("Text [ERROR]: could not load Emulogic font.");

	// Creating character map
	FT_Set_Char_Size(roboto_face, 32, 0, 1536, 0);
	FT_Set_Char_Size(ubuntu_face, 32, 0, 1536, 0);
	FT_Set_Char_Size(emulogic_face, 32, 0, 1536, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++)
	{
		_LoadChar(roboto_face, c, ROBOTO);
		_LoadChar(ubuntu_face, c, UBUNTU);
		_LoadChar(emulogic_face, c, EMULOGIC);
	}

	FT_Done_Face(roboto_face);
	FT_Done_Face(ubuntu_face);
	FT_Done_Face(emulogic_face);
	FT_Done_FreeType(ft);
}

void Text::_LoadChar(FT_Face face, GLubyte c, int font)
{
	if (!(font == ROBOTO || font == UBUNTU || font == EMULOGIC))
	{
		printf("Text [WARNING]: _LoadChar recieved an invalid font (%d)\n", font);
		return;
	}

	if (FT_Load_Char(face, c, FT_LOAD_RENDER))
	{
		printf("Text [WARNING]: FreeType could not load char \"%c\" for font Ubuntu, skipping.\n", c);
		return;
	}
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
		face->glyph->bitmap.width, face->glyph->bitmap.rows,
		0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Character character = {
		texture,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		face->glyph->advance.x
	};

	if (font == ROBOTO)
		_roboto.insert(pair<GLchar, Character>(c, character));
	else if (font == UBUNTU)
		_ubuntu.insert(pair<GLchar, Character>(c, character));
	else if (font == EMULOGIC)
		_emulogic.insert(pair<GLchar, Character>(c, character));
}

// Testing methods

#define NUM_OF_TESTS 27

void Test::_CreateTextTest()
{
	text_objects = (Text*)malloc(sizeof(Text) * NUM_OF_TESTS);

	//
	// testing roboto font
	text_objects[0] = Text(ROBOTO, 5.0f, "A quick brown fox jumped over the lazy dog. (5.0)", 0, 0, RED);
	float height = text_objects[0].GetHeight();
	text_objects[0].SetYPosition(800 - (int)height);

	text_objects[1] = Text(ROBOTO, 3.0f, "A quick brown fox jumped over the lazy dog. (3.0)", 0, 0, GREEN);
	height += text_objects[1].GetHeight();
	text_objects[1].SetYPosition(800 - (int)height);

	text_objects[2] = Text(ROBOTO, 2.0f, "A quick brown fox jumped over the lazy dog. (2.0)", 0, 0, BLUE);
	height += text_objects[2].GetHeight();
	text_objects[2].SetYPosition(800 - (int)height);

	text_objects[3] = Text(ROBOTO, 1.0f, "A quick brown fox jumped over the lazy dog. (1.0)", 0, 0, YELLOW);
	height += text_objects[3].GetHeight();
	text_objects[3].SetYPosition(800 - (int)height);

	text_objects[4] = Text(ROBOTO, 0.9f, "A quick brown fox jumped over the lazy dog. (0.9)", 0, 0, MAGENTA);
	height += text_objects[4].GetHeight();
	text_objects[4].SetYPosition(800 - (int)height);

	text_objects[5] = Text(ROBOTO, 0.8f, "A quick brown fox jumped over the lazy dog. (0.8)", 0, 0, CYAN);
	height += text_objects[5].GetHeight();
	text_objects[5].SetYPosition(800 - (int)height);

	text_objects[6] = Text(ROBOTO, 0.7f, "A quick brown fox jumped over the lazy dog. (0.7)", 0, 0, GOLD);
	height += text_objects[6].GetHeight();
	text_objects[6].SetYPosition(800 - (int)height);

	text_objects[7] = Text(ROBOTO, 0.6f, "A quick brown fox jumped over the lazy dog. (0.6)", 0, 0, PINK);
	height += text_objects[7].GetHeight();
	text_objects[7].SetYPosition(800 - (int)height);

	text_objects[8] = Text(ROBOTO, 0.5f, "A quick brown fox jumped over the lazy dog. (0.5)", 0, 0, LIGHTBLUE);
	height += text_objects[8].GetHeight();
	text_objects[8].SetYPosition(800 - (int)height);

	//
	// testing ubuntu font
	text_objects[9] = Text(UBUNTU, 5.0f, "A quick brown fox jumped over the lazy dog. (5.0)", 0, 0, RED);
	height = text_objects[9].GetHeight();
	text_objects[9].SetYPosition(533 - (int)height);

	text_objects[10] = Text(UBUNTU, 3.0f, "A quick brown fox jumped over the lazy dog. (3.0)", 0, 0, GREEN);
	height += text_objects[10].GetHeight();
	text_objects[10].SetYPosition(533 - (int)height);

	text_objects[11] = Text(UBUNTU, 2.0f, "A quick brown fox jumped over the lazy dog. (2.0)", 0, 0, BLUE);
	height += text_objects[11].GetHeight();
	text_objects[11].SetYPosition(533 - (int)height);

	text_objects[12] = Text(UBUNTU, 1.0f, "A quick brown fox jumped over the lazy dog. (1.0)", 0, 0, YELLOW);
	height += text_objects[12].GetHeight();
	text_objects[12].SetYPosition(533 - (int)height);

	text_objects[13] = Text(UBUNTU, 0.9f, "A quick brown fox jumped over the lazy dog. (0.9)", 0, 0, MAGENTA);
	height += text_objects[13].GetHeight();
	text_objects[13].SetYPosition(533 - (int)height);

	text_objects[14] = Text(UBUNTU, 0.8f, "A quick brown fox jumped over the lazy dog. (0.8)", 0, 0, CYAN);
	height += text_objects[14].GetHeight();
	text_objects[14].SetYPosition(533 - (int)height);

	text_objects[15] = Text(UBUNTU, 0.7f, "A quick brown fox jumped over the lazy dog. (0.7)", 0, 0, GOLD);
	height += text_objects[15].GetHeight();
	text_objects[15].SetYPosition(533 - (int)height);

	text_objects[16] = Text(UBUNTU, 0.6f, "A quick brown fox jumped over the lazy dog. (0.6)", 0, 0, PINK);
	height += text_objects[16].GetHeight();
	text_objects[16].SetYPosition(533 - (int)height);

	text_objects[17] = Text(UBUNTU, 0.5f, "A quick brown fox jumped over the lazy dog. (0.5)", 0, 0, LIGHTBLUE);
	height += text_objects[17].GetHeight();
	text_objects[17].SetYPosition(533 - (int)height);

	//
	// testing emulogic font
	text_objects[18] = Text(EMULOGIC, 5.0f, "A quick brown fox jumped over the lazy dog. (5.0)", 0, 0, RED);
	height = text_objects[18].GetHeight();
	text_objects[18].SetYPosition(266 - (int)height);

	text_objects[19] = Text(EMULOGIC, 3.0f, "A quick brown fox jumped over the lazy dog. (3.0)", 0, 0, GREEN);
	height += text_objects[19].GetHeight();
	text_objects[19].SetYPosition(266 - (int)height);

	text_objects[20] = Text(EMULOGIC, 2.0f, "A quick brown fox jumped over the lazy dog. (2.0)", 0, 0, BLUE);
	height += text_objects[20].GetHeight();
	text_objects[20].SetYPosition(266 - (int)height);

	text_objects[21] = Text(EMULOGIC, 1.0f, "A quick brown fox jumped over the lazy dog. (1.0)", 0, 0, YELLOW);
	height += text_objects[21].GetHeight();
	text_objects[21].SetYPosition(266 - (int)height);

	text_objects[22] = Text(EMULOGIC, 0.9f, "A quick brown fox jumped over the lazy dog. (0.9)", 0, 0, MAGENTA);
	height += text_objects[22].GetHeight();
	text_objects[22].SetYPosition(266 - (int)height);

	text_objects[23] = Text(EMULOGIC, 0.8f, "A quick brown fox jumped over the lazy dog. (0.8)", 0, 0, CYAN);
	height += text_objects[23].GetHeight();
	text_objects[23].SetYPosition(266 - (int)height);

	text_objects[24] = Text(EMULOGIC, 0.7f, "A quick brown fox jumped over the lazy dog. (0.7)", 0, 0, GOLD);
	height += text_objects[24].GetHeight();
	text_objects[24].SetYPosition(266 - (int)height);

	text_objects[25] = Text(EMULOGIC, 0.6f, "A quick brown fox jumped over the lazy dog. (0.6)", 0, 0, PINK);
	height += text_objects[25].GetHeight();
	text_objects[25].SetYPosition(266 - (int)height);

	text_objects[26] = Text(EMULOGIC, 0.5f, "A quick brown fox jumped over the lazy dog. (0.5)", 0, 0, LIGHTBLUE);
	height += text_objects[26].GetHeight();
	text_objects[26].SetYPosition(266 - (int)height);

	//text_objects[0] = Text(0, 1.0f, "Test 1. (Size = 1.0)", 25, 25, WHITE);
	//text_objects[1] = Text(0, 2.0f, "Test 2. (Size = 2.0)", 50, 50, YELLOW);
	//text_objects[2] = Text(0, 5.0f, "Test 3. (Size = 5.0)", 100, 100, RED);
	//text_objects[3] = Text(0, 0.5f, "Test 4. (Size = 0.5)", 100, 300, GREEN);
	//text_objects[4] = Text(0, 0.8f, "Test 5. (Size = 0.8)", 100, 200, CYAN);

	_text_test = true;
}

void Test::_DisplayTextTest()
{
	if (!_text_test)
		return;

	for (int i = 0; i < NUM_OF_TESTS; i++)
		text_objects[i].Draw(0, 0);

}
