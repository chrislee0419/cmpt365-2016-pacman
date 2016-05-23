
#pragma once

#include "..\managers\ImageManager.h"
#include "..\shaders\Shader.h"
#include "..\depend\glm\vec4.hpp"

class Sprite
{
private:
	static Shader _shader;
	static GLuint _vao;
	static GLuint _vbo;
	static bool _ready;
	int _xpos, _ypos, _xsize, _ysize, _rotation;
	glm::vec4 _colour;
	GLuint _tex;

	void _Init(int xpos, int ypos, int xsize, int ysize, int rotation, glm::vec4 colour);
	static void _PrepareGLObjects();
	glm::vec4* _CreateVerticesArray();

public:
	Sprite();
	Sprite(int texture_id);
	Sprite(int xpos, int ypos, int xsize, int ysize);
	Sprite(int texture_id, int xpos, int ypos, int xsize, int ysize);
	Sprite(int texture_id, int xpos, int ypos, int xsize, int ysize, int rotation);
	Sprite(int texture_id, glm::vec4 colour);
	Sprite(int texture_id, int xpos, int ypos, int xsize, int ysize, glm::vec4 colour);
	Sprite(int texture_id, int xpos, int ypos, int xsize, int ysize, int rotation, glm::vec4 colour);
	~Sprite();

	int GetXPosition();
	int GetYPosition();
	int GetXSize();
	int GetYSize();

	void SetXPosition(int xpos);
	void SetYPosition(int ypos);
	void SetPosition(int xpos, int ypos);
	void SetXSize(int xsize);
	void SetYSize(int ysize);
	void SetSize(int xsize, int ysize);
	void SetRotation(int rotation);
	void SetColour(glm::vec4 colour);
	void LoadTexture(int texture_id);

	static void Prepare(Shader shader);

	void Draw();
	void Draw(int x_translate, int y_translate);
};