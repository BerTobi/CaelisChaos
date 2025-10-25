#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "Unit.h"
#include "Building.h"
#include "Utilities/Util.h"
#include <vector>
#include <map>

#include "Abilities/TrainUnitAbility.h"

//class Ability;
//class TrainUnitAbility;

class Map
{
public:

	Map();

    std::vector<Entity*>& getEntities();
	Entity* getEntityPrototypeByID(std::string name);
    SDL_Point getSize();

    void loadEntities();
	void loadAbilities();
	Entity* placeEntity(std::string sPrototypeName, SDL_FPoint coordinates, int nTeam);

    std::vector<Entity*> m_units;

	int getTeamPopulation(int nTeam);

private:
	
    std::vector<Entity*> m_entities;
    std::map<std::string, Unit> m_unitPrototypes;
    std::map<std::string, Building> m_buildingPrototypes;
	std::map<std::string, Entity> m_entityPrototypes;
    std::map<std::string, Ability*> m_abilityPrototypes;
	SDL_Point m_size;

};

#endif

