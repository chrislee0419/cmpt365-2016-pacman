
#pragma once

#include "..\depend\glew\glew.h"
#include "..\depend\freeglut\freeglut.h"
#include "..\depend\glm\vec4.hpp"

#include "..\objects\basic\Box.h"
#include "..\objects\basic\Text.h"
#include "..\objects\basic\Sprite.h"
#include "..\objects\basic\Button.h"

#include "..\shaders\Shader.h"
#include "..\objects\_colours.h"

class Test
{
private:
	static Shader _shader;
	GLuint _vao;
	GLuint _pos_vbo, _col_vbo;
	
	Box *box_objects;
	void _CreateBoxTest();
	void _DisplayBoxTest();
	bool _box_test;

	Text *text_objects;
	void _CreateTextTest();
	void _DisplayTextTest();
	bool _text_test;

	Sprite *sprite_objects;
	void _CreateSpriteTest();
	void _DisplaySpriteTest();
	bool _sprite_test;

	Button *button_objects;
	bool *button_hover;
	void _CreateButtonTest();
	void _DisplayButtonTest();
	void _PassiveMotionButtonTest(int x, int y);
	void _MouseButtonTest(int button, int state, int x, int y);
	void _KeyboardButtonTest(unsigned char key, int x, int y);
	bool _button_test;

public:
	Test();
	~Test();

	void SetupTest();
	void DisplayTest();
	void PassiveMotionTest(int x, int y);
	void MouseTest(int button, int state, int x, int y);
	void KeyboardTest(unsigned char key, int x, int y);
	static void SetProgram(const Shader shader);

	void BasicTest();
	void BasicTestDisplay();
};