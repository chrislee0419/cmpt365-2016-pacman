
#include "GameManager.h"

#include "../objects/Box.h"
#include "../objects/Text.h"
#include "../objects/Sprite.h"
#include "ImageManager.h"

// game state definitions
#define S_PAUSED 0
#define S_GAMEOVER 1
#define S_PLAY 2

// constructor
GameManager::GameManager()
{
	m_score = new Scoreboard();
}

// destructor
GameManager::~GameManager()
{
	delete m_score;
}

// input methods
void GameManager::Keyboard(int key)
{
	switch (key)
	{
	case 'a':
		m_score->AddScore(1);
		break;
	case 's':
		m_score->AddScore(2);
		break;
	case 'd':
		m_score->AddScore(10);
		break;
	case 'f':
		m_score->SetScore(50);
		break;
	case 'g':
		m_score->ResetScore();
		break;
	case 'z':
		m_score->AddLives(1);
		break;
	case 'x':
		m_score->AddLives(3);
		break;
	case 'c':
		m_score->SetLives(10);
		break;
	case 'v':
		m_score->SetLives(0);
		break;
	case 'b':
		m_score->ResetLives();
	}
}

void GameManager::Special(int key)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
	case GLUT_KEY_RIGHT:
	case GLUT_KEY_LEFT:
		;
	}
}

// rendering method
void GameManager::Draw()
{
	m_score->Draw();
}

void GameManager::Prepare(Shader default_shader, Shader text_shader, Shader sprite_shader)
{
	// Provide each class with their respective shader program and prepare objects
	Box::Prepare(default_shader);
	Text::Prepare(text_shader);
	Sprite::Prepare(sprite_shader);
	ImageManager::Prepare();
}
