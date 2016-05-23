
#include "..\..\depend\SOIL\SOIL.h"

#include "ImageManager.h"

// Globals
GLuint ImageManager::_textures[IMG_LAST_ITEM + 1];

GLuint _Load(char* filename, GLuint min_filter, GLuint mag_filter)
{
	GLuint texture;
	int w, h;

	// load texture from file
	unsigned char *image = SOIL_load_image(filename, &w, &h, 0, SOIL_LOAD_RGBA);
	if (image == NULL)
	{
		printf("ImageManager [ERROR]: could not load image file \"%s\"\n", filename);
		throw(std::runtime_error("ImageManager failed to load an image."));
		return -1;
	}

	// create opengl texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

	// free resources
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (glIsTexture(texture) == GL_FALSE)
	{
		glDeleteTextures(1, &texture);
		printf("ImageManager [ERROR]: could not generate texture\n");
		throw(std::runtime_error("ImageManager failed to generate texture."));
		return -1;
	}

	return texture;
}

void ImageManager::Prepare()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	
	// load images
	_textures[IMG_TEST1] = _Load(IMG_TEST1_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_TEST2] = _Load(IMG_TEST2_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_TEST3] = _Load(IMG_TEST3_PATH, GL_NEAREST, GL_NEAREST);

	_textures[IMG_PLAYER1] = _Load(IMG_PLAYER1_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_PLAYER2] = _Load(IMG_PLAYER2_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_PLAYER3] = _Load(IMG_PLAYER3_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_PLAYER4] = _Load(IMG_PLAYER4_PATH, GL_NEAREST, GL_NEAREST);

	_textures[IMG_BLINKY_U] = _Load(IMG_BLINKY_U_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_BLINKY_D] = _Load(IMG_BLINKY_D_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_BLINKY_L] = _Load(IMG_BLINKY_L_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_BLINKY_R] = _Load(IMG_BLINKY_R_PATH, GL_NEAREST, GL_NEAREST);

	_textures[IMG_PINKY_U] = _Load(IMG_PINKY_U_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_PINKY_D] = _Load(IMG_PINKY_D_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_PINKY_L] = _Load(IMG_PINKY_L_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_PINKY_R] = _Load(IMG_PINKY_R_PATH, GL_NEAREST, GL_NEAREST);

	_textures[IMG_INKY_U] = _Load(IMG_INKY_U_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_INKY_D] = _Load(IMG_INKY_D_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_INKY_L] = _Load(IMG_INKY_L_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_INKY_R] = _Load(IMG_INKY_R_PATH, GL_NEAREST, GL_NEAREST);

	_textures[IMG_CLYDE_U] = _Load(IMG_CLYDE_U_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_CLYDE_D] = _Load(IMG_CLYDE_D_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_CLYDE_L] = _Load(IMG_CLYDE_L_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_CLYDE_R] = _Load(IMG_CLYDE_R_PATH, GL_NEAREST, GL_NEAREST);

	_textures[IMG_PELLET] = _Load(IMG_PELLET_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_SPELLET] = _Load(IMG_SPELLET_PATH, GL_NEAREST, GL_NEAREST);

	_textures[IMG_WALL] = _Load(IMG_WALL_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_L] = _Load(IMG_WALL_L_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_INV_L] = _Load(IMG_WALL_INV_L_PATH, GL_LINEAR, GL_LINEAR);

	_textures[IMG_WALL_GHOST] = _Load(IMG_WALL_GHOST_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_GHOST_L] = _Load(IMG_WALL_GHOST_L_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_GHOST_END1] = _Load(IMG_WALL_GHOST_END1_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_GHOST_END2] = _Load(IMG_WALL_GHOST_END2_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_DOOR] = _Load(IMG_DOOR_PATH, GL_LINEAR, GL_LINEAR);

	_textures[IMG_WALL_OUTER] = _Load(IMG_WALL_OUTER_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_OUTER_L] = _Load(IMG_WALL_OUTER_L_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_OUTER_INV_L] = _Load(IMG_WALL_OUTER_INV_L_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_OUTER_JUNC1] = _Load(IMG_WALL_OUTER_JUNC1_PATH, GL_LINEAR, GL_LINEAR);
	_textures[IMG_WALL_OUTER_JUNC2] = _Load(IMG_WALL_OUTER_JUNC2_PATH, GL_LINEAR, GL_LINEAR);

	_textures[IMG_GHOST_EYES_U] = _Load(IMG_GHOST_EYES_U_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_GHOST_EYES_D] = _Load(IMG_GHOST_EYES_D_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_GHOST_EYES_L] = _Load(IMG_GHOST_EYES_L_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_GHOST_EYES_R] = _Load(IMG_GHOST_EYES_R_PATH, GL_NEAREST, GL_NEAREST);

	_textures[IMG_SPOOKED1] = _Load(IMG_SPOOKED1_PATH, GL_NEAREST, GL_NEAREST);
	_textures[IMG_SPOOKED2] = _Load(IMG_SPOOKED2_PATH, GL_NEAREST, GL_NEAREST);
}

GLuint ImageManager::RetrieveTexture(int id)
{
	if (id < 0 || id > IMG_LAST_ITEM)
		return -1;
	return _textures[id];
}
