#include "Map.h"


Map::Map()
{
    m_size = SDLPoint(128, 128);

    //Prototypes
    m_unitPrototypes["footman"]= Unit("Footman"); // Parametros propios de un footman
    m_unitPrototypes["mage"]= Unit("Mage"); //Parametros propios de un mago
    m_buildingPrototypes["fortress"]= Building("Fortress");
    m_buildingPrototypes["tower"]= Building("Tower");

    m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(30.0f, 30.0f))); //Si a new Building le damos como parametro un Bulding (el prototipo) entonces la clase puede tener un constructor que simplemente copie los atributos que quiera de ese prototipo y devuelva una nueva intancia.
    m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(-30.0f,30.0f)));
    m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(30.0f,-30.0f)));
    m_entities.push_back( new Building(&m_buildingPrototypes["fortress"], SDLFPoint(-30.0f,-30.0f)));
    m_entities.push_back( new Building(&m_buildingPrototypes["tower"], SDLFPoint(-27.0f, -30.0f)));
    m_entities.push_back( new Building(&m_buildingPrototypes["tower"], SDLFPoint(-30.0f, -27.0f)));
    m_entities.push_back( new Unit(&m_unitPrototypes["footman"], SDLFPoint(29.0f, 32.0f) ) );
    m_entities.push_back( new Unit(&m_unitPrototypes["mage"], SDLFPoint(30.0f, 31.0f) ) );




    m_entities[4]->m_spriteID = "Tower"; // Sprite modificado manualmente, esto no va una vez existan los prototipos

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
