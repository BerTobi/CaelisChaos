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
	// Constructors
	Entity(std::string sSubclass, std::string sType, std::string spriteID, SDL_FPoint size);
	Entity(std::string sSubclass, std::string spriteID, SDL_FPoint size);
	Entity(std::string sSubclass, std::string spriteID);
	Entity(Entity* prototype, SDL_FPoint initialCoords, int nTeam);
	Entity(SDL_FPoint initialCoords, int nTeam);
    Entity(SDL_FPoint initialCoords);
    Entity();

	// Behaviour methods
	void move();
	void move(SDL_FPoint movementTarget);
	void executeAbility(std::string sAbilityName);
	void executeAbility(std::string sAbilityName, Entity* target);
	void addAbility(std::string sAbilityName, Ability* ability);
	void setEntityTarget(Entity* newTarget);

	// Effect methods
	void takeDamage(float fDamageReceived);
	SDL_FPoint m_coords;
	SDL_FPoint m_size;
	std::string m_spriteID;
	std::string m_sType;
	std::string m_sSubclass;
	int m_nTeam;

	Entity* m_entityTarget;
	SDL_FPoint m_movementTarget;
	float m_fMovementSpeed;
	float m_fBaseAttack;
	float m_fAttackRange;
	float m_fBaseHealth;
	float m_fCurrentHealth;
	float m_fVisionRange;


protected:

	std::map<std::string, Ability*> m_abilities;
};

#endif

