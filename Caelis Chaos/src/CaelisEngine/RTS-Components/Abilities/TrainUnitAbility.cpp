#include "RTS-Components/Abilities/TrainUnitAbility.h"
#include "RTS-Components/Map.h"

TrainUnitAbility::TrainUnitAbility() : Ability() {}

TrainUnitAbility::TrainUnitAbility(Map* gameMap, std::string sUnitType) : Ability(gameMap, "Train" + sUnitType)
{
	m_sUnitType = sUnitType;
}

void TrainUnitAbility::Execute()
{
	m_gameMap->placeUnit("footman", SDLFPoint((float)(rand() % 200 - 100), (float)(rand() % 200 - 100)));
}