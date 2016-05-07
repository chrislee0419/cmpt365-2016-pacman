
#include "..\..\depend\SOIL\SOIL.h"

#include "ImageManager.h"

// Globals
GLuint ImageManager::_textures[IMG_LAST_ITEM + 1];

GLuint _Load(char* filename)
{
	GLuint texture;
	int w, h;

	// load texture from file
	unsigned char *image = SOIL_load_image(filename, &w, &h, 0, SOIL_LOAD_RGB);
	if (image == NULL)
	{
		printf("ImageManager [ERROR]: could not load image file \"%s\"\n", filename);
		throw(std::runtime_error("ImageManager failed to load an image."));
		return -1;
	}

	// create opengl texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	_textures[IMG_TEST1] = _Load(IMG_TEST1_PATH);
	_textures[IMG_TEST2] = _Load(IMG_TEST2_PATH);
	_textures[IMG_TEST3] = _Load(IMG_TEST3_PATH);
	/*_textures[IMG_PLAYER] = _Load(IMG_PLAYER_PATH);
	_textures[IMG_GHOST1] = _Load(IMG_GHOST1_PATH);
	_textures[IMG_GHOST2] = _Load(IMG_GHOST2_PATH);
	_textures[IMG_GHOST3] = _Load(IMG_GHOST3_PATH);
	_textures[IMG_GHOST4] = _Load(IMG_GHOST4_PATH);
	_textures[IMG_PELLET] = _Load(IMG_PELLET_PATH);
	_textures[IMG_SPELLET] = _Load(IMG_SPELLET_PATH);
	_textures[IMG_WALL] = _Load(IMG_WALL_PATH);
	_textures[IMG_WALL_N] = _Load(IMG_WALL_N_PATH);
	_textures[IMG_WALL_S] = _Load(IMG_WALL_S_PATH);
	_textures[IMG_WALL_E] = _Load(IMG_WALL_E_PATH);
	_textures[IMG_WALL_W] = _Load(IMG_WALL_W_PATH);
	_textures[IMG_WALL_NE] = _Load(IMG_WALL_NE_PATH);
	_textures[IMG_WALL_NW] = _Load(IMG_WALL_NW_PATH);
	_textures[IMG_WALL_SE] = _Load(IMG_WALL_SE_PATH);
	_textures[IMG_WALL_SW] = _Load(IMG_WALL_SW_PATH);
	_textures[IMG_WALL_NEW] = _Load(IMG_WALL_NEW_PATH);
	_textures[IMG_WALL_SEW] = _Load(IMG_WALL_SEW_PATH);
	_textures[IMG_WALL_NSE] = _Load(IMG_WALL_NSE_PATH);
	_textures[IMG_WALL_NSW] = _Load(IMG_WALL_NSW_PATH);*/
}

GLuint ImageManager::RetrieveTexture(int id)
{
	if (id < 0 || id > IMG_LAST_ITEM)
		return -1;
	return _textures[id];
}
