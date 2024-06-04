#include "Upgrade.h"

Upgrade::Upgrade()
{
	bResearched = false;
	nPrice = 0;
	EntitiesAffected = {};
	sName = "DEFAULT";
	sRace = "NONE";
	sClass = "NONE";
	sType = "NONE";
}

void Upgrade::addEffect(std::function<void(Entity* entity, Player* player)> func)
{
	EntityEffects.push_back(func);
}

void Upgrade::addEffect(std::function<void(Player* player)> func)
{
	PlayerEffects.push_back(func);
}

void Upgrade::activateEntityEffects(Entity* entity, Player* player)
{
	for (int i = 0; i < EntityEffects.size(); i++)
	{
		EntityEffects[i](entity, player);
	}

}

void Upgrade::activatePlayerEffects(Player* player)
{
	for (int i = 0; i < PlayerEffects.size(); i++)
	{
		PlayerEffects[i](player);
	}
}