
#pragma once

#include "Box.h"
#include "Text.h"
#include "Sprite.h"

class Scoreboard
{
private:
	int m_scorevalue, m_highscorevalue, m_livesvalue;
	Text m_scoretext, m_highscoretext, m_score, m_highscore, m_livestext, m_livesnum;
	Sprite m_lives;

	void m_SetScores();

public:
	Scoreboard();
	~Scoreboard();

	void AddScore(int score);
	void SetScore(int score);
	void ResetScore();
	int GetScore();

	void AddLives(int lives);
	void SetLives(int lives);
	void ResetLives();

	void Draw();

};