
#include "Scoreboard.h"

#include "Test.h"

// constructor
Scoreboard::Scoreboard()
{
	m_scorevalue = 0;
	m_highscorevalue = 0;
	m_livesvalue = 0;

	m_scoretext = Text(EMULOGIC, 0.8f, "Score", 20, 775);
	m_highscoretext = Text(EMULOGIC, 0.8f, "High Score", 610, 775);
	m_score = Text(EMULOGIC, 0.8f, "00000000", 20, 755);
	m_highscore = Text(EMULOGIC, 0.8f, "00000000", 645, 755);

	m_livestext = Text(EMULOGIC, 0.8f, "Lives", 200, 775);
	m_livesnum = Text(EMULOGIC, 0.68f, "", 230, 755);
	m_lives = Sprite(IMG_PLAYER4, 200, 752, 18, 18);

	/*printf("widths: (%f, %f, %f, %f)\n",
		m_scoretext.GetWidth(), m_highscoretext.GetWidth(),
		m_score.GetWidth(), m_highscore.GetWidth());
	printf("heights: (%f, %f, %f, %f)\n",
		m_scoretext.GetHeight(), m_highscoretext.GetHeight(),
		m_score.GetHeight(), m_highscore.GetHeight());*/
}

// destructor
Scoreboard::~Scoreboard() {}

void Scoreboard::AddScore(int score)
{
	m_scorevalue += score;
	if (m_scorevalue > m_highscorevalue)
		m_highscorevalue = m_scorevalue;
}

void Scoreboard::SetScore(int score)
{
	m_scorevalue = score;
	if (m_scorevalue > m_highscorevalue)
		m_highscorevalue = m_scorevalue;
}

void Scoreboard::ResetScore() { m_scorevalue = 0; }

void Scoreboard::AddLives(int lives)
{
	m_livesvalue += lives;
	if (m_livesvalue < 0)
		m_livesvalue = 0;
}

void Scoreboard::SetLives(int lives)
{
	if (lives >= 0)
		m_livesvalue = lives;
}

void Scoreboard::ResetLives() { m_livesvalue = 2; }

void Scoreboard::m_SetScores()
{
	char text[9] = { 0 };

	sprintf_s(text, sizeof(text), "%08d", m_scorevalue % 100000000);
	std::string stringified = std::string(text);
	m_score.SetText(stringified);

	sprintf_s(text, sizeof(text), "%08d", m_highscorevalue % 100000000);
	stringified = std::string(text);
	m_highscore.SetText(stringified);
}

// rendering method
void Scoreboard::Draw()
{
	m_SetScores();

	m_scoretext.Draw();
	m_highscoretext.Draw();
	m_score.Draw();
	m_highscore.Draw();

	m_livestext.Draw();

	if (m_livesvalue < 4)
	{
		for (int i = 0; i < m_livesvalue; i++)
			m_lives.Draw(19 * i, 0);
	}
	else
	{
		m_lives.Draw();

		char text[5] = { 0 };
		sprintf_s(text, sizeof(text), "x %d", m_livesvalue % 100);
		std::string stringified = std::string(text);
		m_livesnum.SetText(stringified);

		m_livesnum.Draw();
	}

}
