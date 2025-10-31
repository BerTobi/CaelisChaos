#include "RTS-Components/Abilities/AttackAbility.h"
#include "RTS-Components/Map.h"
#include "RTS-Components/Entity.h"

AttackAbility::AttackAbility() : Ability() {}

AttackAbility::AttackAbility(Map* gameMap) : Ability(gameMap, "Attack")
{

}

void AttackAbility::Execute(Entity* caster, Entity* target)
{
	target->takeDamage(caster->m_fBaseAttack);
}