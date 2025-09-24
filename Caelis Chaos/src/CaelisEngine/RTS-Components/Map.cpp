#include "Map.h"


Map::Map()
{
    m_size = SDLPoint(128, 128);

    //Prototypes
    m_unitPrototypes["footman"] = Unit("Footman"); // Parametros propios de un footman
    m_unitPrototypes["mage"] = Unit("Mage"); //Parametros propios de un mago
    m_buildingPrototypes["fortress"] = Building("Fortress", SDLFPoint(3.0f, 3.0f));
	m_buildingPrototypes["barracks"] = Building("Barracks", SDLFPoint(2.0f, 2.0f));
    m_buildingPrototypes["tower"] = Building("Tower", SDLFPoint(1.0f, 1.0f));

    m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(30.0f, 30.0f))); //Si a new Building le damos como parametro un Bulding (el prototipo) entonces la clase puede tener un constructor que simplemente copie los atributos que quiera de ese prototipo y devuelva una nueva intancia.
    m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(-30.0f, 30.0f)));
    m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(30.0f, -30.0f)));
    m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(-30.0f, -30.0f)));
	m_entities.push_back( new Building(&m_buildingPrototypes["barracks"], SDLFPoint(33.0f, 27.0f)));
	m_entities.push_back( new Building(&m_buildingPrototypes["barracks"], SDLFPoint(27.0f, 33.0f)));
	m_entities.push_back( new Building(&m_buildingPrototypes["barracks"], SDLFPoint(27.0f, 27.0f)));
    m_entities.push_back( new Building(&m_buildingPrototypes["tower"], SDLFPoint(-27.0f, -30.0f)));
    m_entities.push_back( new Building(&m_buildingPrototypes["tower"], SDLFPoint(-30.0f, -27.0f)));
	m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(19.0f, 15.0f)));
    //m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(17.0f, 15.0f)));
	//m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(15.0f, 15.0f)));
	m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(17.0f, 17.0f)));
	//m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(17.0f, 19.0f)));
    m_entities.push_back( new Unit(&m_unitPrototypes["footman"], SDLFPoint(29.0f, 32.0f) ) );
    m_entities.push_back( new Unit(&m_unitPrototypes["mage"], SDLFPoint(20.0f, 31.0f) ) );

}

std::vector<Entity*>& Map::getEntities()
{
    return m_entities;
}

Unit Map::getUnitPrototypeByID(std::string name)
{
    return m_unitPrototypes[name];
}

Building Map::getBuildingPrototypeByID(std::string name)
{
    return m_buildingPrototypes[name];
}

SDL_Point Map::getSize()
{
    return m_size;
}
