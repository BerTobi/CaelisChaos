#ifndef TRAINUNITABILITY_H
#define TRAINUNITABILITY_H

#include "RTS-Components/Ability.h"

class Map;

class TrainUnitAbility : public Ability
{
public:

	TrainUnitAbility();
	TrainUnitAbility(Map* gameMap, std::string sUnitType);

	void Execute(Entity* caster);

protected:
	std::string m_sUnitType;
};

#endif
