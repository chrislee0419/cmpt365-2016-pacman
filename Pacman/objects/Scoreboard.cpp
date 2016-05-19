
#include "Scoreboard.h"

#include "Test.h"

// constructor
Scoreboard::Scoreboard()
{
	m_scorevalue = 0;
	m_highscorevalue = 0;

	m_scoretext = Text(EMULOGIC, 0.5f, "Score", 200, 780);
	m_highscoretext = Text(EMULOGIC, 0.5f, "High Score", 400, 780);
	m_score = Text(EMULOGIC, 0.5f, "00000000", 200, 765);
	m_highscore = Text(EMULOGIC, 0.5f, "00000000", 400, 765);

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

void Scoreboard::ResetScore() { SetScore(0); }

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
}
