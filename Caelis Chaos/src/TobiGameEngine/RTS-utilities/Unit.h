#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "Building.h"
#include <unordered_map>
#include <iostream>

class Building;

class Unit : public Entity
{
public:
	Unit();

	void setSpeed(int newSpeed);

	void setAttack(int newAttack);

	void setDefaultTarget(Point nCoordinate);

	void setDefaultTarget(float nX, float nY);

	void setTargetUnit(int index);

	int getTargetUnit();

	void setTargetBuilding(int index);

	int getTargetBuilding();

	std::string attack(Entity* target, std::unordered_map<int, Entity*> &entityList);

	void setAttackSpeed(int newSpeed);

	virtual ~Unit() = default;

public:

	Point mDefaultTargetPosition;

	int nTrainingCost;
	int nAttackCooldown;
	float fAttackRange;
	float fAttackDistance;
	std::string sProjectile;

protected:

	int nTargetUnit;
	int nTargetBuilding;
	int nDefaultAttackCooldown;
	

};

#endif
