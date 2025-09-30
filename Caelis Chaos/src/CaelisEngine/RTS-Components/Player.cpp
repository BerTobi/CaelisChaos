#include "Player.h"

Player::Player()
{
	m_nGold = 1000;
	m_nTeam = 0;
	m_Camera = Camera( SDLFPoint(0.0f, 0.0f), SDLFPoint(16.0f, 8.0f) );
}

Player::Player(int nTeam)
{
	m_nGold = 1000;
	m_nTeam = nTeam;
	m_Camera = Camera( SDLFPoint(0.0f, 0.0f), SDLFPoint(16.0f, 8.0f) );
}