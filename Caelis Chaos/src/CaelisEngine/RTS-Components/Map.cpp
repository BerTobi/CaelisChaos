#include "Map.h"


Map::Map()
{
    m_size = SDLPoint(128, 128);

	loadAbilities();

    //Entity Prototypes
    m_entityPrototypes["Footman"] = Entity("Unit", "Footman"); // Parametros propios de un footman
    m_entityPrototypes["Mage"] = Entity("Unit", "Mage"); //Parametros propios de un mago
    m_entityPrototypes["Fortress"] = Entity("Building", "Fortress", "Fortress", SDLFPoint(3.0f, 3.0f));
	m_entityPrototypes["Barracks"] = Entity("Building", "Barracks", "Barracks", SDLFPoint(2.0f, 2.0f));
    m_entityPrototypes["Barracks"].addAbility("TrainFootman", m_abilityPrototypes["TrainFootman"]);
    m_entityPrototypes["Barracks2"] = Entity("Building", "Barracks2", "Barracks2", SDLFPoint(2.0f, 4.0f));
    m_entityPrototypes["Tower"] = Entity("Building", "Tower", "Tower", SDLFPoint(1.0f, 3.0f));

    loadEntities();

}

std::vector<Entity*>& Map::getEntities()
{
    return m_entities;
}

Entity* Map::getEntityPrototypeByID(std::string name)
{
    return &m_entityPrototypes[name];
}

SDL_Point Map::getSize()
{
    return m_size;
}

int Map::getTeamPopulation(int nTeam)
{
	int nPopulation = 0;
	for (size_t i = 0; i < m_units.size(); i++)
	{
		if (m_units[i]->m_nTeam == nTeam) nPopulation++;
	}
	return nPopulation;
}

Entity* Map::placeEntity(std::string sPrototypeName, SDL_FPoint coordinates, int nTeam)
{
    Entity* newEntity = new Entity(&m_entityPrototypes[sPrototypeName], coordinates, nTeam);
	m_entities.push_back(newEntity);
    m_units.push_back(newEntity);
	return (Unit*)m_entities.back();
}

void Map::loadEntities()
{
    // North Player
    m_entities.push_back(new Entity(&m_entityPrototypes["Fortress"], SDLFPoint(-29.0f, -29.0f), 1));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(-33.0f, -25.0f), 1));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(-25.0f, -33.0f), 1));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(-24.0f, -24.0f), 1));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(-23.0f, -28.0f), 1));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(-28.0f, -23.0f), 1));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(-29.0f, -34.0f), 1));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(-34.0f, -29.0f), 1));
    
    // South Player
    m_entities.push_back(new Entity(&m_entityPrototypes["Fortress"], SDLFPoint(29.0f, 29.0f), 2));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(33.0f, 25.0f), 2));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(25.0f, 33.0f), 2));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(24.0f, 24.0f), 2));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(24.0f, 29.0f), 2));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(29.0f, 24.0f), 2));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(30.0f, 35.0f), 2));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(35.0f, 30.0f), 2));

	// East Player
    m_entities.push_back(new Entity(&m_entityPrototypes["Fortress"], SDLFPoint(-29.0f, 29.0f), 3));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(-34.0f, 24.0f), 3));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(-24.0f, 34.0f), 3));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(-25.0f, 25.0f), 3));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(-24.0f, 29.0f), 3));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(-29.0f, 24.0f), 3));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(-29.0f, 34.0f), 3));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(-34.0f, 29.0f), 3));

	// West Player
    m_entities.push_back(new Entity(&m_entityPrototypes["Fortress"], SDLFPoint(29.0f, -29.0f), 4));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(34.0f, -24.0f), 4));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(24.0f, -34.0f), 4));
    m_entities.push_back(new Entity(&m_entityPrototypes["Barracks"], SDLFPoint(25.0f, -25.0f), 4));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(24.0f, -29.0f), 4));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(29.0f, -24.0f), 4));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(29.0f, -34.0f), 4));
    m_entities.push_back(new Entity(&m_entityPrototypes["Tower"], SDLFPoint(34.0f, -29.0f), 4));

}

void Map::loadAbilities()
{
	//Ability Prototypes
    //TrainUnitAbility newAbility = TrainUnitAbility(new Map(), "footman");
    m_abilityPrototypes["TrainFootman"] = new TrainUnitAbility(this, "Footman");
}