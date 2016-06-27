
#include "GameBoard.h"

// constructor
GameBoard::GameBoard()
{
	// wall preparation
	m_CreateWallSprites();

	// pellet preparation
	//m_pelletmap = new int*[BOARD_WIDTH];
	//for (int i = 0; i < BOARD_WIDTH; ++i)
	//	m_pelletmap[i] = new int[BOARD_HEIGHT];
	//m_pelletsprites = (Sprite*)malloc(sizeof(Sprite)* NUM_OF_PELLET);
	//m_CreatePelletSprites();

}

// destructor
GameBoard::~GameBoard()
{
	delete[] m_wallsprites;
	free(m_pelletsprites);
	for (int i = 0; i < BOARD_WIDTH; ++i)
		delete[] m_pelletmap[i];
	delete[] m_pelletmap;
}

// helper methods
void GameBoard::m_CreateWallSprites()
{
	// start from bottom left corner (120, 65)
	// created row by row
	// finish at top right corner (660, 665)

	int tilenum = -1;
	//m_wallsprites = (Sprite*)malloc(sizeof(Sprite)* NUM_OF_WALLS);
	m_wallsprites = new Sprite[NUM_OF_WALLS]();

	// row 1 (28)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_INV_L, 120, 65, 20, 20, 270);
	for (int i = 0; i < 26; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 140 + (i * 20), 65, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_INV_L, 660, 65, 20, 20);

	// row 2 (2)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 85, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 85, 20, 20, 180);

	// row 3 (24)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 105, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 105, 20, 20, 270);
	for (int i = 0; i < 8; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 180 + (i * 20), 105, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 340, 105, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 380, 105, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 400, 105, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 440, 105, 20, 20, 270);
	for (int i = 0; i < 8; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 460 + (i * 20), 105, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 105, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 105, 20, 20, 180);

	// row 4 (24)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 125, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 125, 20, 20, 180);
	for (int i = 0; i < 4; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 180 + (i*20), 125, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 260, 125, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 280, 125, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 300, 125, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 320, 125, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 340, 125, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 125, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 125, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 440, 125, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 460, 125, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 480, 125, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 500, 125, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 520, 125, 20, 20, 270);
	for (int i = 0; i < 4; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 540 + (i * 20), 125, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 125, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 125, 20, 20, 180);

	// row 5 (8)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 145, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 145, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 145, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 145, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 145, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 145, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 145, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 145, 20, 20, 180);

	// row 6 (22)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_JUNC1, 120, 165, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 140, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 165, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 200, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 220, 165, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 165, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 165, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 320, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 340, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 360, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 380, 165, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 400, 165, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 420, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 440, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 460, 165, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 165, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 165, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 560, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 580, 165, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 640, 165, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_JUNC2, 660, 165, 20, 20, 180);

	// row 7 (22)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_JUNC2, 120, 185, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 140, 185, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 185, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 200, 185, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 220, 185, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 185, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 280, 185, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 320, 185, 20, 20, 180);
	for (int i = 0; i < 6; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 340 + (i * 20), 185, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 460, 185, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 500, 185, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 185, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 560, 185, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 580, 185, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 185, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 640, 185, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_JUNC1, 660, 185, 20, 20, 180);

	// row 8 (6)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 205, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 200, 205, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 220, 205, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 560, 205, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 580, 205, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 205, 20, 20, 180);

	// row 9 (22)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 225, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 225, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 180, 225, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 200, 225, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 220, 225, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 225, 20, 20, 270);
	for (int i = 0; i < 3; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280 + (i * 20), 225, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 340, 225, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 380, 225, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 400, 225, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 440, 225, 20, 20, 270);
	for (int i = 0; i < 3; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 460 + (i * 20), 225, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 225, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 560, 225, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 580, 225, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 600, 225, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 225, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 225, 20, 20, 180);

	// row 10 (22)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 245, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 245, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 180, 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 200, 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 220, 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 245, 20, 20, 180);
	for (int i = 0; i < 3; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280 + (i * 20), 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 340, 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 245, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 245, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 440, 245, 20, 20, 180);
	for (int i = 0; i < 3; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 460 + (i * 20), 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 560, 245, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 580, 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 600, 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 245, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 245, 20, 20, 180);

	// row 11 (4)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 265, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 265, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 265, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 265, 20, 20, 180);

	// row 12 (24)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_INV_L, 120, 285, 20, 20, 180);
	for (int i = 0; i < 4; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 140 + (i * 20), 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_L, 220, 285, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 280, 285, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 320, 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 340, 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 360, 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 380, 285, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 400, 285, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 420, 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 440, 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 460, 285, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 500, 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 285, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_L, 560, 285, 20, 20, 270);
	for (int i = 0; i < 4; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 580 + (i * 20), 285, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_INV_L, 660, 285, 20, 20, 90);

	// row 13 (14)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 220, 305, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 305, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 305, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 320, 305, 20, 20, 180);
	for (int i = 0; i < 6; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 340 + (i * 20), 305, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 460, 305, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 305, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 305, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 560, 305, 20, 20, 180);

	// row 14 (6)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 220, 325, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 325, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 325, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 325, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 325, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 560, 325, 20, 20, 180);

	// row 15 (14)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 220, 345, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 345, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 345, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST_L, 320, 345, 20, 20, 270);
	for (int i = 0; i < 6; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 340 + (i * 20), 345, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST_L, 460, 345, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 345, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 345, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 560, 345, 20, 20, 180);

	// row 16 (18)
	for (int i = 0; i < 5; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120 + (i * 20), 365, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_L, 220, 365, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 365, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 280, 365, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 320, 365, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 460, 365, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 500, 365, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 365, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_L, 560, 365, 20, 20, 180);
	for (int i = 0; i < 5; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 580 + (i * 20), 365, 20, 20, 90);

	// row 17 (2)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 320, 385, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 460, 385, 20, 20);

	// row 18 (18)
	for (int i = 0; i < 5; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120 + (i * 20), 405, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_L, 220, 405, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 405, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 280, 405, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 320, 405, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 460, 405, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 500, 405, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 405, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_L, 560, 405, 20, 20, 270);
	for (int i = 0; i < 5; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 580 + (i * 20), 405, 20, 20, 270);

	// row 19 (14)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 220, 425, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 425, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 425, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST_L, 320, 425, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 340, 425, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST_END1, 360, 425, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_DOOR, 380, 425, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_DOOR, 400, 425, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST_END2, 420, 425, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST, 440, 425, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_GHOST_L, 460, 425, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 425, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 425, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 560, 425, 20, 20, 180);

	// row 20 (6)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 220, 445, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 445, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 445, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 445, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 445, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 560, 445, 20, 20, 180);

	// row 21 (14)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 220, 465, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 465, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 280, 465, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 300, 465, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 320, 465, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 340, 465, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 380, 465, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 400, 465, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 440, 465, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 460, 465, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 480, 465, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 500, 465, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 465, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 560, 465, 20, 20, 180);

	// row 22 (24)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_INV_L, 120, 485, 20, 20, 270);
	for (int i = 0; i < 4; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 140 + (i * 20), 485, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_L, 220, 485, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 485, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 280, 485, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 300, 485, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 320, 485, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 340, 485, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 485, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 485, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 440, 485, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 460, 485, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 480, 485, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 500, 485, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 485, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_L, 560, 485, 20, 20, 180);
	for (int i = 0; i < 4; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 580 + (i * 20), 485, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_INV_L, 660, 485, 20, 20);

	// row 23 (8)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 505, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 505, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 505, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 505, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 505, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 505, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 505, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 505, 20, 20, 180);

	// row 24 (22)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 525, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 180, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 200, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 220, 525, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 525, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280, 525, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 320, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 340, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 360, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 380, 525, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_INV_L, 400, 525, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 420, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 440, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 460, 525, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 500, 525, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 525, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 560, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 580, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 600, 525, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 525, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 525, 20, 20, 180);

	// row 25 (22)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 545, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 545, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 180, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 200, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 220, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 545, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 280, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 320, 545, 20, 20, 180);
	for (int i = 0; i < 6; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 340 + (i * 20), 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 460, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 500, 545, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 560, 545, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 580, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 600, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 545, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 545, 20, 20, 180);
	
	// row 26 (2)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 565, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 565, 20, 20, 180);

	// row 27 (22)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 585, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 180, 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 200, 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 220, 585, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 585, 20, 20, 270);
	for (int i = 0; i < 3; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280 + (i * 20), 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 340, 585, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 380, 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 400, 585, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 440, 585, 20, 20, 270);
	for (int i = 0; i < 3; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 460 + (i * 20), 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 585, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 560, 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 580, 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 600, 585, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 585, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 585, 20, 20, 180);

	// row 28 (12)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 605, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 160, 605, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 220, 605, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 260, 605, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 340, 605, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 605, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 605, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 440, 605, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 520, 605, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 560, 605, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 620, 605, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 605, 20, 20, 180);

	// row 29 (22)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 625, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 160, 625, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 180, 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 200, 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 220, 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 260, 625, 20, 20, 180);
	for (int i = 0; i < 3; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 280 + (i * 20), 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 340, 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 625, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 625, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 440, 625, 20, 20, 180);
	for (int i = 0; i < 3; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL, 460 + (i * 20), 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 520, 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 560, 625, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 580, 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 600, 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_L, 620, 625, 20, 20, 90);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 625, 20, 20, 180);

	// row 30 (4)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 120, 645, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 380, 645, 20, 20, 180);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL, 400, 645, 20, 20);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 660, 645, 20, 20, 180);

	// row 31 (28)
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_INV_L, 120, 665, 20, 20, 180);
	for (int i = 0; i < 12; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 140 + (i * 20), 665, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_JUNC1, 380, 665, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_JUNC2, 400, 665, 20, 20, 270);
	for (int i = 0; i < 12; ++i)
		m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER, 420 + (i * 20), 665, 20, 20, 270);
	m_wallsprites[++tilenum] = Sprite(IMG_WALL_OUTER_INV_L, 660, 665, 20, 20, 90);

	// 480 total
	//printf("tilenum = %d\n", tilenum);

}

void GameBoard::m_CreatePelletSprites()
{
	int tilenum = -1;

	// starts at bottom left, goes to top right, row by row
	// does not include super pellets

	// 1
	for (int i = 0; i < 26; ++i)
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 140 + (i * 20), 85, 20, 20);

	// 2-3
	for (int i = 0; i < 2; ++i)
	{
		int h = 105 + (i * 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 140, h, 20, 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 360, h, 20, 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 420, h, 20, 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 640, h, 20, 20);
	}

	// 4
	for (int i = 0; i < 6; ++i)
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 140 + (i * 20), 145, 20, 20);
	for (int i = 0; i < 4; ++i)
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 300 + (i * 20), 145, 20, 20);
	for (int i = 0; i < 4; ++i)
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 420 + (i * 20), 145, 20, 20);
	for (int i = 0; i < 6; ++i)
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 540 + (i * 20), 145, 20, 20);

	// 5-6
	for (int i = 0; i < 2; ++i)
	{
		int h = 165 + (i * 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 180, h, 20, 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 240, h, 20, 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 300, h, 20, 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 480, h, 20, 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 540, h, 20, 20);
		m_pelletsprites[++tilenum] = Sprite(IMG_PELLET, 600, h, 20, 20);
	}

	// 7
	m_pelletsprites[++tilenum] = Sprite(IMG_SPELLET, 140, 205, 20, 20);


}

// rendering method
void GameBoard::Draw()
{
	for (int i = 0; i < 480; ++i)
		m_wallsprites[i].Draw();
}
