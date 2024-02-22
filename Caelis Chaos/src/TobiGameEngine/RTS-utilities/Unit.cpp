#include "Unit.h"
#include "Entity.h"
#include "Building.h"

Unit::Unit()
{
	nHealth = 0;
	fSpeed = 0;
	fTargetX = fX;
	fTargetY = fY;
	fDefaultTargetX = fX;
	fDefaultTargetY = fY;
	nAttack = 0;
	nAttackSpeed = 0;
	nAttackCooldown = 0;
	nDefaultAttackCooldown = 0;
	nTargetUnit = -1;
	nTargetBuilding = -1;
	fAttackRange = 0;
	fAttackDistance = 0;
	nTeam = 0;
	sName = "NONE";
	sProjectile = "NONE";
	lastHitID = -1;
	nArmour = 0;
	nTrainingCost = 0;
}

void Unit::setHealth(int newHealth)
{
	nHealth = newHealth;
}

void Unit::setMaxHealth(int newMaxHealth)
{
	nMaxHealth = newMaxHealth;
}

void Unit::addHealth(int health)
{
	nHealth += health;
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

void Unit::setDefaultTarget(float nX, float nY)
{
	fDefaultTargetX = nX;
	fDefaultTargetY = nY;
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

std::string Unit::attack(Unit* target)
{
	if (nAttackCooldown <= 0)
	{
		if (target->getLastHitID() == -1 && (target->nHealth - nAttack) <= 0) target->setLastHitID(this->getTeam());
		target->addHealth(0 - (nAttack * (1.0f - (float)target->getArmour() / 100.0f)));
		nAttackCooldown = nDefaultAttackCooldown / nAttackSpeed;
		return sProjectile;
	}
	else
		nAttackCooldown -= 1;
	
	return "NONE";
}

std::string Unit::attack(Building* target)
{
	if (nAttackCooldown <= 0)
	{
		if (target->getLastHitID() == -1 && (target->getHealth() - nAttack) <= 0) target->setLastHitID(this->getTeam());
		target->addHealth(0 - (nAttack * (1.0f - (float)target->getArmour() / 100.0f)));
		nAttackCooldown = nDefaultAttackCooldown / nAttackSpeed;
		return sProjectile;
	}
	else
		nAttackCooldown -= 1;

	return "NONE";
}

void Unit::setAttackSpeed(int newSpeed)
{
	nAttackSpeed = newSpeed;
}

int Unit::getLastHitID()
{
	return lastHitID;
}

void Unit::setLastHitID(int id)
{
	lastHitID = id;
}

int Unit::getArmour() {
	return nArmour;
}