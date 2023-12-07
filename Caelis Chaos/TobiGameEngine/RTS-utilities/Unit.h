#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "Building.h"
#include <iostream>

class Building;

class Unit : public Entity
{
public:
	Unit();

	void setHealth(int newHealth);

	void addHealth(int health);

	void setSpeed(int newSpeed);

	void setAttack(int newAttack);

	void move(float nX, float nY);

	void setTarget(float nX, float nY);

	void setDefaultTarget(float nX, float nY);

	void setTargetUnit(int index);

	int getTargetUnit();

	void setTargetBuilding(int index);

	int getTargetBuilding();

	std::string attack(Unit* target);

	std::string attack(Building* target);

	void setAttackSpeed(int newSpeed);

	int getLastHitID();

	void setLastHitID(int id);

	int getArmour();

	virtual ~Unit() = default;

public:

	int fDefaultTargetX;
	int fDefaultTargetY;
	int nHealth;
	int nTrainingCost;
	int nAttackCooldown;
	float fAttackRange;
	float fAttackDistance;
	std::string sName;
	std::string sProjectile;

protected:

	float fSpeed;
	int nAttack;
	int nAttackSpeed;
	int nTargetUnit;
	int nTargetBuilding;
	int nDefaultAttackCooldown;
	int lastHitID;
	int nArmour;
	

};

#endif
