#include "Map.h"


Map::Map()
{
    m_size = SDLPoint(128, 128);

	loadAbilities();

    //Entity Prototypes
    m_unitPrototypes["Footman"] = Unit("Footman"); // Parametros propios de un footman
    m_unitPrototypes["Mage"] = Unit("Mage"); //Parametros propios de un mago
    m_buildingPrototypes["Fortress"] = Building("Fortress", SDLFPoint(3.0f, 3.0f));
	m_buildingPrototypes["Barracks"] = Building("Barracks", SDLFPoint(2.0f, 2.0f), "Barracks");
    m_buildingPrototypes["Barracks"].addAbility("TrainFootman", m_abilityPrototypes["TrainFootman"]);
    m_buildingPrototypes["Barracks2"] = Building("Barracks2", SDLFPoint(2.0f, 4.0f));
    m_buildingPrototypes["Tower"] = Building("Tower", SDLFPoint(1.0f, 3.0f));

    loadEntities();

}

std::vector<Entity*>& Map::getEntities()
{
    return m_entities;
}

Unit* Map::getUnitPrototypeByID(std::string name)
{
    return &m_unitPrototypes[name];
}

Building* Map::getBuildingPrototypeByID(std::string name)
{
    return &m_buildingPrototypes[name];
}

SDL_Point Map::getSize()
{
    return m_size;
}

Unit* Map::placeUnit(std::string sPrototypeName, SDL_FPoint coordinates)
{
    Unit* newUnit = new Unit(&m_unitPrototypes[sPrototypeName], coordinates);
	m_entities.push_back(newUnit);
    m_units.push_back(newUnit);
	return (Unit*)m_entities.back();
}

void Map::loadEntities()
{
    // North Player
    m_entities.push_back(new Building(&m_buildingPrototypes["Fortress"], SDLFPoint(-29.0f, -29.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(-33.0f, -25.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(-25.0f, -33.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(-24.0f, -24.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(-23.0f, -28.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(-28.0f, -23.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(-29.0f, -34.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(-34.0f, -29.0f)));
    
    // South Player
    m_entities.push_back(new Building(&m_buildingPrototypes["Fortress"], SDLFPoint(29.0f, 29.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(33.0f, 25.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(25.0f, 33.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(24.0f, 24.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(24.0f, 29.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(29.0f, 24.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(30.0f, 35.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(35.0f, 30.0f)));

	// East Player
    m_entities.push_back(new Building(&m_buildingPrototypes["Fortress"], SDLFPoint(-29.0f, 29.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(-34.0f, 24.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(-24.0f, 34.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(-25.0f, 25.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(-24.0f, 29.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(-29.0f, 24.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(-29.0f, 34.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(-34.0f, 29.0f)));

	// West Player
    m_entities.push_back(new Building(&m_buildingPrototypes["Fortress"], SDLFPoint(29.0f, -29.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(34.0f, -24.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(24.0f, -34.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Barracks"], SDLFPoint(25.0f, -25.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(24.0f, -29.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(29.0f, -24.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(29.0f, -34.0f)));
    m_entities.push_back(new Building(&m_buildingPrototypes["Tower"], SDLFPoint(34.0f, -29.0f)));

}

void Map::loadAbilities()
{
	//Ability Prototypes
    //TrainUnitAbility newAbility = TrainUnitAbility(new Map(), "footman");
    m_abilityPrototypes["TrainFootman"] = new TrainUnitAbility(this, "Footman");
}