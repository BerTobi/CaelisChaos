#include "Unit.h"
#include "Entity.h"
#include "Building.h"

Unit::Unit()
{
	nHealth = 0;
	mTargetPosition = mPosition;
	mDefaultTargetPosition = mPosition;
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
	sClass = "UNIT";
	lastHitID = -1;
	nArmour = 0;
	nTrainingCost = 0;
	isCollidable = true;
}

void Unit::setSpeed(int newSpeed)
{
	fMovementSpeed = newSpeed;
}

void Unit::setAttack(int newAttack)
{
	nAttack = newAttack;
}

void Unit::setDefaultTarget(Point nPosition)
{
	mDefaultTargetPosition = nPosition;
}

void Unit::setDefaultTarget(float nX, float nY)
{
	mDefaultTargetPosition = { nX, nY };
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

std::string Unit::attack(Entity* target, std::unordered_map<int, Entity*> &entityList)
{
	if (nAttackCooldown <= 0)
	{
		if (target->getLastHitID() == -1 && (target->nHealth - nAttack) <= 0) target->setLastHitID(this->getTeam());
		if (sProjectile == "NONE")
		{
			if (fSplashArea > 0.0f)
			{
				for (auto& entityInArea : entityList)
				{
					if (entityInArea.second->sClass == "BUILDING" || entityInArea.second->sClass == "UNIT")
					{
						if (cDistance(entityInArea.second->mPosition, target->mPosition) <= fSplashArea && entityInArea.second->getTeam() != getTeam())
						{
							if (entityInArea.second->getLastHitID() == -1 && (entityInArea.second->nHealth - nAttack) <= 0) entityInArea.second->setLastHitID(getTeam());
							entityInArea.second->addHealth(0 - (nAttack * (1.0f - (float)entityInArea.second->getArmour() / 100.0f)));
						}
					}

				}
			}
			else target->addHealth(0 - (nAttack * (1.0f - (float)target->getArmour() / 100.0f)));

		}
			
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


