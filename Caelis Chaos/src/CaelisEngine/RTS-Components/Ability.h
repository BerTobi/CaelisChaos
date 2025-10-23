#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Map;

class Ability
{
public:
	
	Ability();
	Ability(Map* gameMap, std::string sName);

	virtual ~Ability() {};

	virtual void Execute() = 0;

protected:
	std::string m_sName;
	Map* m_gameMap;
};

#endif