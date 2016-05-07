
#pragma once

#include <iostream>
#include "..\..\depend\glew\glew.h"
#include "..\..\depend\freeglut\freeglut.h"

// texture macros
#define IMG_TEST1 0
#define IMG_TEST1_PATH "images/test1.jpg"
#define IMG_TEST2 1
#define IMG_TEST2_PATH "images/test2.jpg"
#define IMG_TEST3 2
#define IMG_TEST3_PATH "images/test3.png"

#define IMG_PLAYER 3
#define IMG_PLAYER_PATH "images/player.png"
#define IMG_GHOST1 4
#define IMG_GHOST1_PATH "images/ghost1.png"
#define IMG_GHOST2 5
#define IMG_GHOST2_PATH "images/ghost2.png"
#define IMG_GHOST3 6
#define IMG_GHOST3_PATH "images/ghost3.png"
#define IMG_GHOST4 7
#define IMG_GHOST4_PATH "images/ghost4.png"

#define IMG_PELLET 8
#define IMG_PELLET_PATH "images/pellet.png"
#define IMG_SPELLET 9
#define IMG_SPELLET_PATH "images/spellet.png"

#define IMG_WALL 10
#define IMG_WALL_PATH "images/wall.png"
#define IMG_WALL_N 11
#define IMG_WALL_N_PATH "images/wall_n.png"
#define IMG_WALL_S 12
#define IMG_WALL_S_PATH "images/wall_s.png"
#define IMG_WALL_E 13
#define IMG_WALL_E_PATH "images/wall_e.png"
#define IMG_WALL_W 14
#define IMG_WALL_W_PATH "images/wall_w.png"

#define IMG_WALL_EW 15
#define IMG_WALL_EW_PATH "images/wall_ew.png"
#define IMG_WALL_NS 16
#define IMG_WALL_NS_PATH "images/wall_ns.png"

#define IMG_WALL_NW 17
#define IMG_WALL_NW_PATH "images/wall_nw.png"
#define IMG_WALL_NE 18
#define IMG_WALL_NE_PATH "images/wall_ne.png"
#define IMG_WALL_SW 19
#define IMG_WALL_SW_PATH "images/wall_sw.png"
#define IMG_WALL_SE 20
#define IMG_WALL_SE_PATH "images/wall_se.png"

#define IMG_WALL_NEW 21
#define IMG_WALL_NEW_PATH "images/wall_new.png"
#define IMG_WALL_SEW 22
#define IMG_WALL_SEW_PATH "images/wall_sew.png"

#define IMG_WALL_NSE 23
#define IMG_WALL_NSE_PATH "images/wall_nse.png"
#define IMG_WALL_NSW 24
#define IMG_WALL_NSW_PATH "images/wall_nsw.png"

#define IMG_LAST_ITEM 24

class ImageManager
{
private:
	static GLuint _textures[IMG_LAST_ITEM + 1];

public:
	static void Prepare();
	static GLuint RetrieveTexture(int id);

};