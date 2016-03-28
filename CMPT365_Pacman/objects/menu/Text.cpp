/*
//	for CMPT 365 Term Project
//	by Chris Lee - cla235
*/

#include "Text.h"
#include "..\..\test\test.h"
#include "..\..\test\_util.h"

using std::string;

// Globals
Shader Text::_shader;

// Constructors
Text::Text()
{
	_Init(0, 12, "Text", 0, 0, WHITE);
}

Text::Text(string text, int xpos, int ypos)
{
	_Init(0, 12, text, xpos, ypos, WHITE);
	if (!_Assert())
		throw std::invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

Text::Text(int font, int size, string text, int xpos, int ypos)
{
	_Init(font, size, text, xpos, ypos, WHITE);
	if (!_Assert())
		throw std::invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

Text::Text(string text, int xpos, int ypos, glm::vec4 colour)
{
	_Init(0, 12, text, xpos, ypos, colour);
	if (!_Assert())
		throw std::invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

Text::Text(int font, int size, string text, int xpos, int ypos, glm::vec4 colour)
{
	_Init(font, size, text, xpos, ypos, colour);
	if (!_Assert())
		throw std::invalid_argument("Text [WARNING]: constructor recieved an invalid input.");
}

// Destructor
Text::~Text() {}

// Setter methods
void Text::SetFont(int font)
{
	if (_font == font)
		return;
	else
	{
		_font = font;
		if (!_PrepareFT())
			throw std::runtime_error("Text [WARNING]: _PrepareFT encountered an error.");
	}
}

void Text::SetSize(int size)
{
	_size = size;
}

void Text::SetText(string text)
{
	_text = text;
}

void Text::SetColour(glm::vec4 colour)
{
	_colour = colour;
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

	if (!_ready)
		_CreateGLObjects();

	glUniform3f(glGetUniformLocation(_shader.GetProgram(), "textColour"),
		_colour.x, _colour.y, _colour.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	int original_xpos = _xpos;

	std::string::const_iterator c;
	for (c = _text.begin(); c != _text.end(); c++)
	{
		Character ch = _characters[*c];
		GLfloat x_position = _xpos + x_translate + ch.Bearing.x * _size;
		GLfloat y_position = _ypos + y_translate - (ch.Size.y - ch.Bearing.y) * _size;
		GLfloat w = ch.Size.x * _size;
		GLfloat h = ch.Size.y * _size;

		GLfloat vertices[6][4] = {
			{ x_position,		y_position + h, 0.0, 0.0 },
			{ x_position,		y_position,		0.0, 0.0 },
			{ x_position + w,	y_position,		0.0, 0.0 },

			{ x_position,		y_position + h, 0.0, 0.0 },
			{ x_position + w,	y_position,		0.0, 0.0 },
			{ x_position + w,	y_position + h, 0.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		_xpos += (ch.Advance >> 6) * _size;
	}

	_xpos = original_xpos;

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Private helper methods
void Text::_Init(int font, int size, string text, int xpos, int ypos, glm::vec4 colour)
{
	SetFont(font);
	SetPosition(xpos, ypos);
	SetText(text);
	SetSize(size);
	SetColour(colour);
	_ready = false;
}

bool Text::_Assert()
{
	if ( !(_font == 0 || _font == 1) )
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
	printf("First time drawing for Text object: VAO = %d, VBO = %d\n", _vao, _vbo);
}

// Prepare Freetype library and faces
bool Text::_PrepareFT()
{
	FT_Library ft;
	FT_Face face;

	if (FT_Init_FreeType(&ft))
	{
		printf("Text [ERROR]: could not initialize FT_Library\n");
		return false;
	}
	// Prepares font faces
	if (_font == 1)
	{
		if (FT_New_Face(ft, "depend/fonts/Ubuntu.ttf", 0, &face))
		{
			printf("Text [WARNING]: could not load Ubuntu font\n");
			FT_Done_FreeType(ft);
			return false;
		}
		
	}
	else
	{
		if (FT_New_Face(ft, "depend/fonts/Roboto.ttf", 0, &face))
		{
			printf("Text [WARNING]: could not load Roboto font\n");
			FT_Done_FreeType(ft);
			return false;
		}
	}

	// Creating character map
	FT_Set_Char_Size(face, 256, 256, 96, 96);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			printf("Text [WARNING]: FreeType could not load char \"%c\", skipping\n", c);
			continue;
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
		_characters.insert(std::pair<GLchar, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return true;
}

// Testing methods
void Test::_CreateTextTest()
{
	text_objects = new Text[3];
	text_objects[0] = Text("This is a test.", 25, 25);
	text_objects[1] = Text(0, 2, "Second Test.", 50, 50);
	text_objects[2] = Text(0, 5, "Third Test.", 100, 100, BLACK);

	_text_test = true;
}

void Test::_DisplayTextTest()
{
	if (!_text_test)
		return;

	for (int i = 0; i < 3; i++)
		text_objects[i].Draw(0, 0);

}
