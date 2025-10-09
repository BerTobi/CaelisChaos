#include "Ability.h"

Ability::Ability(Match* gameState, std::string sName)
{
	m_gameState = gameState;
	m_sName = sName;
}