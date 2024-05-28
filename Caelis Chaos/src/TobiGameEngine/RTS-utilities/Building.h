#ifndef BUILDING_H
#define BUILDING_H

#include "GUI/TextBox.h"
#include "Entity.h"
#include "Unit.h"
#include "Player.h"
#include <vector>
#include <iostream>

class Player;
class Unit;

class Building : public Entity
{
public:
	int nAttackCooldown;
	float fAttackRange;
	float fVisionRange;
	bool bSelected;
	int abilityCooldown[3] = { 0,0,0 };

	std::string sProjectile;

	TextBox* Counter;

	Building();

	Building(Building* prototype);

	std::vector<Unit*> spawnWave(std::vector<Unit*>);

	void setLevel(int newLevel);

	int getLevel();

	virtual void upgrade(Player* player);

	virtual void select();

	void setTargetUnit(int index);

	int getTargetUnit();

	std::string attack(Entity* target);

	virtual ~Building() = default;

protected:

	int nLevel;
	int nTargetUnit;
	
};

#endif