#ifndef BUILDING_H
#define BUILDING_H

#include "GUI/Button.h"
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
	float fAttackDistance;
	bool bSelected;

	std::string sProjectile;

	Button* SelectionBox;
	TextBox* Counter;

	Building();

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
	int nDefaultAttackCooldown;

	
};

#endif