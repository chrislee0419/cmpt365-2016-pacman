
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

#define IMG_PLAYER1 3
#define IMG_PLAYER1_PATH "images/pacman1.png"
#define IMG_PLAYER2 4
#define IMG_PLAYER2_PATH "images/pacman2.png"
#define IMG_PLAYER3 5
#define IMG_PLAYER3_PATH "images/pacman3.png"
#define IMG_PLAYER4 6
#define IMG_PLAYER4_PATH "images/pacman4.png"

#define IMG_BLINKY_U 7
#define IMG_BLINKY_U_PATH "images/blinky_u.png"
#define IMG_BLINKY_D 8
#define IMG_BLINKY_D_PATH "images/blinky_d.png"
#define IMG_BLINKY_L 9
#define IMG_BLINKY_L_PATH "images/blinky_l.png"
#define IMG_BLINKY_R 10
#define IMG_BLINKY_R_PATH "images/blinky_r.png"

#define IMG_PINKY_U 11
#define IMG_PINKY_U_PATH "images/pinky_u.png"
#define IMG_PINKY_D 12
#define IMG_PINKY_D_PATH "images/pinky_d.png"
#define IMG_PINKY_L 13
#define IMG_PINKY_L_PATH "images/pinky_l.png"
#define IMG_PINKY_R 14
#define IMG_PINKY_R_PATH "images/pinky_r.png"

#define IMG_INKY_U 15
#define IMG_INKY_U_PATH "images/inky_u.png"
#define IMG_INKY_D 16
#define IMG_INKY_D_PATH "images/inky_d.png"
#define IMG_INKY_L 17
#define IMG_INKY_L_PATH "images/inky_l.png"
#define IMG_INKY_R 18
#define IMG_INKY_R_PATH "images/inky_r.png"

#define IMG_CLYDE_U 19
#define IMG_CLYDE_U_PATH "images/clyde_u.png"
#define IMG_CLYDE_D 20
#define IMG_CLYDE_D_PATH "images/clyde_d.png"
#define IMG_CLYDE_L 21
#define IMG_CLYDE_L_PATH "images/clyde_l.png"
#define IMG_CLYDE_R 22
#define IMG_CLYDE_R_PATH "images/clyde_r.png"

#define IMG_PELLET 23
#define IMG_PELLET_PATH "images/pellet.png"
#define IMG_SPELLET 24
#define IMG_SPELLET_PATH "images/spellet.png"

#define IMG_WALL 25
#define IMG_WALL_PATH "images/wall.png"
#define IMG_WALL_L 26
#define IMG_WALL_L_PATH "images/wall_l.png"
#define IMG_WALL_INV_L 27
#define IMG_WALL_INV_L_PATH "images/wall_inv_l.png"

#define IMG_WALL_GHOST 28
#define IMG_WALL_GHOST_PATH "images/wall_ghost.png"
#define IMG_WALL_GHOST_L 29
#define IMG_WALL_GHOST_L_PATH "images/wall_ghost_l.png"
#define IMG_DOOR 30
#define IMG_DOOR_PATH "images/door.png"

#define IMG_WALL_OUTER 31
#define IMG_WALL_OUTER_PATH "images/wall_outer.png"
#define IMG_WALL_OUTER_L 32
#define IMG_WALL_OUTER_L_PATH "images/wall_outer_l.png"
#define IMG_WALL_OUTER_INV_L 33
#define IMG_WALL_OUTER_INV_L_PATH "images/wall_outer_inv_l.png"

#define IMG_GHOST_EYES_U 34
#define IMG_GHOST_EYES_U_PATH "images/ghost_eyes_u.png"
#define IMG_GHOST_EYES_D 35
#define IMG_GHOST_EYES_D_PATH "images/ghost_eyes_d.png"
#define IMG_GHOST_EYES_L 36
#define IMG_GHOST_EYES_L_PATH "images/ghost_eyes_l.png"
#define IMG_GHOST_EYES_R 37
#define IMG_GHOST_EYES_R_PATH "images/ghost_eyes_r.png"

#define IMG_SPOOKED1 38
#define IMG_SPOOKED1_PATH "images/spooked1.png"
#define IMG_SPOOKED2 39
#define IMG_SPOOKED2_PATH "images/spooked2.png"

#define IMG_LAST_ITEM 39

class ImageManager
{
private:
	static GLuint _textures[IMG_LAST_ITEM + 1];

public:
	static void Prepare();
	static GLuint RetrieveTexture(int id);

};