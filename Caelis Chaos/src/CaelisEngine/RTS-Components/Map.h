#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "Unit.h"
#include "Building.h"
#include "Utilities/Util.h"
#include <vector>
#include <map>


class Map
{
public:

	Map();

    std::vector<Entity*>& getEntities();
    Unit getUnitPrototypeByID(std::string name);
    Building getBuildingPrototypeByID(std::string name);
    SDL_Point getSize();

private:

    std::vector<Entity*> m_entities;
    std::map<std::string, Unit> m_unitPrototypes;
    std::map<std::string, Building> m_buildingPrototypes;
	SDL_Point m_size;

};

#endif

