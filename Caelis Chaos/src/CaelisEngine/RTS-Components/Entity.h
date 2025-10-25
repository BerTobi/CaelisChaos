#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <string>
#include <Utilities/Util.h>
#include "RTS-Components/Ability.h"
#include <map>

class Entity
{
public:
	Entity(std::string sSubclass, std::string sType, std::string spriteID, SDL_FPoint size);
	Entity(std::string sSubclass, std::string spriteID, SDL_FPoint size);
	Entity(std::string sSubclass, std::string spriteID);
	Entity(Entity* prototype, SDL_FPoint initialCoords, int nTeam);
	Entity(SDL_FPoint initialCoords, int nTeam);
    Entity(SDL_FPoint initialCoords);
    Entity();
	void move();
	void move(SDL_FPoint movementTarget);
	SDL_FPoint m_coords;
	SDL_FPoint m_size;
	std::string m_spriteID;
	std::string m_sType;
	std::string m_sSubclass;
	int m_nTeam;

	SDL_FPoint m_movementTarget;
	float m_fMovementSpeed;

	void executeAbility(std::string sAbilityName);
	void addAbility(std::string sAbilityName, Ability* ability);

protected:

	std::map<std::string, Ability*> m_abilities;
};

#endif

