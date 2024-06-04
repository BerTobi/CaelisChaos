#ifndef UPGRADE_H
#define UPGRADE_H

#include "Entity.h"
#include "Player.h"
#include <set>
#include <string>
#include <vector>
#include <functional>

class Player;

class Upgrade
{

public:

	Upgrade();

	std::string sName;
	std::string sRace;
	std::string sClass;
	std::string sType;

	int nPrice;
	bool bResearched;

	void addEffect(std::function<void(Entity* entity, Player* player)> func);

	void addEffect(std::function<void(Player* player)> func);

	void activateEntityEffects(Entity* entity, Player* player);

	void activatePlayerEffects(Player* player);

	std::set<std::string> EntitiesAffected;

	std::vector<std::function<void(Entity* entity, Player* player)>> EntityEffects;
	std::vector<std::function<void(Player* player)>> PlayerEffects;
};
	

#endif
