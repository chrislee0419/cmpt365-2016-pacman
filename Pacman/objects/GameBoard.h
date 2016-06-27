
#pragma once

#include "Sprite.h"

/*
	28 tiles wide
	31 tiles tall
	= 868 max tiles

	(max of 800 x 740)

	tile size of 20
	= 560 x 620 pixels
		120 pixels on left and right sides
		65 pixels on top and bottom sides

	240 tiles for pellets
	480 tiles for walls + doors

	player size of 40
*/

#define BOARD_WIDTH 28
#define BOARD_HEIGHT 31

#define NUM_OF_WALLS 480
#define NUM_OF_PELLET 240

class GameBoard
{
private:
	bool m_walls[BOARD_WIDTH][BOARD_HEIGHT];
	Sprite *m_wallsprites;

	int **m_pelletmap;
	bool m_pellets[NUM_OF_PELLET];
	Sprite *m_pelletsprites;

	void m_CreateWallSprites();
	void m_CreatePelletSprites();

public:
	GameBoard();
	~GameBoard();

	bool PelletCheck();
	bool SuperPelletCheck();
	bool GhostCheck();

	void UpdatePositions();

	void Draw();
};
