#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Map;

class Ability
{
public:
	
	Ability(Map* gameMap, std::string sName);

	virtual ~Ability() = default;

	virtual void Execute() = 0;

protected:
	std::string m_sName;
	Map* m_gameMap;
};

#endif