
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
	482 tiles for walls + doors

	player size of 40
*/

class GameBoard
{
private:
	bool m_walls;
	Sprite *m_wallsprites;

	bool m_pellets;
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
