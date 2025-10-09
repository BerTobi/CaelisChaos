#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include <GameStates/Match.h>

class Ability
{
public:
	
	Ability(Match* gameState, std::string sName);

	virtual ~Ability() = default;

	virtual void Execute() = 0;

protected:
	std::string m_sName;
	Match* m_gameState;
};

#endif