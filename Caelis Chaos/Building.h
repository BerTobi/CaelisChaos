#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include "Unit.h"
#include <vector>
#include <iostream>

class Unit;

class Building : public Entity
{
public:
	Building();

	void setHealth(int newHealth);
	std::vector<Unit*> spawnWave(std::vector<Unit*>);

	int getHealth();

protected:

	int nHealth;

};

#endif