#include "Map.h"


Map::Map()
{
    m_size = SDLPoint(128, 128);

    m_unitPrototypes["footman"]= Unit("Footman"); // Parametros propios de un footman
    m_unitPrototypes["mage"]= Unit("Mage"); // parametros propios de un mago

    m_entities.push_back( new Building(SDLFPoint(30.0f, 30.0f)));//Si a new Building le damos como parametro un Bulding (el prototipo) entonces la clase puede tener un constructor que simplemente copie.
    m_entities.push_back( new Building(SDLFPoint(-30.0f,30.0f)));
    m_entities.push_back( new Building(SDLFPoint(30.0f, -30.0f)));
    m_entities.push_back( new Building(SDLFPoint(-30.0f, -30.0f)));
    m_entities.push_back( new Building(SDLFPoint(-27.0f, -30.0f)));
    m_entities.push_back( new Unit(&m_unitPrototypes["footman"], SDLFPoint(29.0f, 32.0f) ) );
    m_entities.push_back( new Unit(&m_unitPrototypes["mage"], SDLFPoint(30.0f, 31.0f) ) );


    m_entities[4]->m_spriteID = "Tower"; // Sprite modificado manualmente, esto no va una vez existan los prototipos

}

std::vector<Entity*>& Map::getEntities()
{
    return m_entities;
}

Unit Map::getPrototypeByID(std::string name)
{
    return m_unitPrototypes[name];
}

SDL_Point Map::getSize()
{
    return m_size;
}
