#include "Ability.h"

Ability::Ability()
{
	m_gameMap = 0;
	m_sName = "NONE";
}

Ability::Ability(Map* gameMap, std::string sName)
{
	m_gameMap = gameMap;
	m_sName = sName;
}