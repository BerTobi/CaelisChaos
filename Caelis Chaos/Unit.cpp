#include "Unit.h"
#include "Entity.h"
#include "Building.h"

Unit::Unit()
{
	nHealth = 0;
	fSpeed = 0;
	fTargetX = fX;
	fTargetY = fY;
	nAttack = 0;
	nAttackSpeed = 0;
	nAttackCooldown = 0;
	nDefaultAttackCooldown = 0;
	nTargetUnit = -1;
	nTargetBuilding = -1;
	fAttackRange = 0;
	fAttackDistance = 0;
	nTeam = 0;
}

void Unit::setHealth(int newHealth)
{
	nHealth = newHealth;
}

void Unit::setSpeed(int newSpeed)
{
	fSpeed = newSpeed;
}

void Unit::setAttack(int newAttack)
{
	nAttack = newAttack;
}

void Unit::move(float nX, float nY)
{
	Entity::move(nX, nY, fSpeed);
}

void Unit::setTarget(float nX, float nY)
{
	fTargetX = nX;
	fTargetY = nY;
}

void Unit::setTargetUnit(int index)
{
	nTargetUnit = index;
}

int Unit::getTargetUnit()
{
	return nTargetUnit;
}

void Unit::setTargetBuilding(int index)
{
	nTargetBuilding = index;
}

int Unit::getTargetBuilding()
{
	return nTargetBuilding;
}

void Unit::attack(Unit* target)
{
	if (nAttackCooldown <= 0)
	{
		target->setHealth(target->nHealth - nAttack);
		nAttackCooldown = nDefaultAttackCooldown / nAttackSpeed;
	}
	else
		nAttackCooldown -= 1;
}

void Unit::attack(Building* target)
{
	if (nAttackCooldown <= 0)
	{
		target->setHealth(target->getHealth() - nAttack);
		nAttackCooldown = nDefaultAttackCooldown / nAttackSpeed;
	}
	else
		nAttackCooldown -= 1;
}

void Unit::setAttackSpeed(int newSpeed)
{
	nAttackSpeed = newSpeed;
}