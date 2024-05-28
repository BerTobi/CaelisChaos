#ifndef UPGRADE_H
#define UPGRADE_H

#include "Entity.h"
#include <set>
#include <string>
#include <vector>
#include <functional>

class Upgrade
{

public:

	Upgrade();

	std::string sName;
	std::string sRace;
	int nPrice;
	bool bResearched;

	void addEffect(std::function<void(Entity* entity)> func);

	void activateEffects(Entity* entity);

	std::set<std::string> EntitiesAffected;

	std::vector<std::function<void(Entity* entity)>> effects;
};
	

#endif
