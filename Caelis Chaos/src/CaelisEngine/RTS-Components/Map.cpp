#include "Map.h"


Map::Map()
{
    m_size = SDLPoint(128, 128);

    m_entities.push_back( new Building(SDLFPoint(30.0f, 30.0f)));
    m_entities.push_back( new Building(SDLFPoint(-30.0f,30.0f)));
    m_entities.push_back( new Building(SDLFPoint(30.0f, -30.0f)));
    m_entities.push_back( new Building(SDLFPoint(-30.0f, -30.0f)));
    m_entities.push_back( new Building(SDLFPoint(-27.0f, -30.0f)));
    m_entities.push_back( new Unit(SDLFPoint(29.0f, 32.0f)));

    m_entities[4]->m_spriteID = "Tower";
}

std::vector<Entity*>& Map::getEntities()
{
    return m_entities;
}

SDL_Point Map::getSize()
{
    return m_size;
}
