#ifndef TRAINUNITABILITY_H
#define TRAINUNITABILITY_H

#include "RTS-Components/Ability.h"

class Map;

class TrainUnitAbility : public Ability
{
public:

	TrainUnitAbility(Map* gameMap, std::string sUnitType);

	void Execute();

protected:
	std::string m_sUnitType;
};

#endif
