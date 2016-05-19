
#pragma once

#include "Box.h"
#include "Text.h"

class Scoreboard
{
private:
	int m_scorevalue, m_highscorevalue;
	Text m_scoretext, m_highscoretext, m_score, m_highscore;

	void m_SetScores();

public:
	Scoreboard();
	~Scoreboard();

	void AddScore(int score);
	void SetScore(int score);
	void ResetScore();

	int GetScore();

	void Draw();

};