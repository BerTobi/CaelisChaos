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

	Button* SelectionBox;
	TextBox* Counter;

	Building();

	int getHealth();
	void setHealth(int newHealth);
	void setMaxHealth(int newMaxHealth);
	void addHealth(int health);

	int getArmour();

	std::vector<Unit*> spawnWave(std::vector<Unit*>);

	void setLevel(int newLevel);

	int getLevel();

	virtual void upgrade(Player* player);

	virtual void select();

	int getLastHitID();

	void setLastHitID(int id);

	void setTargetUnit(int index);

	int getTargetUnit();

	std::string attack(Unit* target);

	virtual ~Building() = default;

protected:

	int nLevel;
	int lastHitID;
	int nArmour;
	int nAttack;
	int nAttackSpeed;
	int nTargetUnit;
	int nDefaultAttackCooldown;
	std::string sProjectile;
	
};

#endif