#ifndef BUILDING_H
#define BUILDING_H

#include "GUI/TextBox.h"
#include "Entity.h"
#include "Unit.h"
#include "Player.h"
#include "Upgrade.h"
#include <vector>
#include <iostream>

class Player;
class Unit;
class Upgrade;

class Building : public Entity
{
public:
	int nAttackCooldown;
	float fAttackRange;
	float fVisionRange;
	bool bSelected;
	int abilityCooldown[3] = { 0,0,0 };
	Player* Owner;

	std::string sProjectile;
	std::string sUpgradesTo;

	std::unordered_map<std::string, Upgrade> upgrades;

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

	void researchUpgrade(std::string upgrade);

	virtual ~Building() = default;

protected:

	int nLevel;
	int nTargetUnit;
	
};

#endif