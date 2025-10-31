#include "RTS-Components/Abilities/TrainUnitAbility.h"
#include "RTS-Components/Map.h"
#include "RTS-Components/Entity.h"

TrainUnitAbility::TrainUnitAbility() : Ability() {}

TrainUnitAbility::TrainUnitAbility(Map* gameMap, std::string sUnitType) : Ability(gameMap, "Train" + sUnitType)
{
	m_sUnitType = sUnitType;
}

void TrainUnitAbility::Execute(Entity* caster, Entity* target)
{
	Entity* trainedUnit = m_gameMap->placeEntity("Footman", SDLFPoint(caster->m_coords), caster->m_nTeam);
}