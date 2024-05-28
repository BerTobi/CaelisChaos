#include "Upgrade.h"

Upgrade::Upgrade()
{
	bResearched = false;
	nPrice = 0;
	EntitiesAffected = {};
	sName = "DEFAULT";
	sRace = "NONE";
}

void Upgrade::addEffect(std::function<void(Entity* entity)> func)
{
	effects.push_back(func);
}

void Upgrade::activateEffects(Entity* entity)
{
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i](entity);
	}
}