#ifndef MOVEABILITY_H
#define MOVEABILITY_H

#include "RTS-Components/Ability.h"
#include "Utilities\Util.h"

class Map;

class MoveAbility : public Ability
{
public:

	MoveAbility();
	MoveAbility(Map* gameMap);

	void Execute(Entity* caster, SDL_FPoint target);

protected:
};

#endif