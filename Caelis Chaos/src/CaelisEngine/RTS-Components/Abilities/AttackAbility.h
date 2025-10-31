#ifndef ATTACKABILITY_H
#define ATTACKABILITY_H

#include "RTS-Components/Ability.h"

class Map;

class AttackAbility : public Ability
{
public:

	AttackAbility();
	AttackAbility(Map* gameMap);

	void Execute(Entity* caster, Entity* target);

protected:
	
};

#endif
