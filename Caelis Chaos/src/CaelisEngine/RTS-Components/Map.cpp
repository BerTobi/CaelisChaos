#include "Map.h"


Map::Map()
{
    m_size = SDLPoint(128, 128);

    m_entities.push_back( new Building(SDLFPoint(30.0f, 30.0f)));
    m_entities.push_back( new Building(SDLFPoint(-30.0f,30.0f)));
    m_entities.push_back( new Building(SDLFPoint(30.0f, -30.0f)));
    m_entities.push_back( new Building(SDLFPoint(-30.0f, -30.0f)));
    m_entities.push_back( new Unit(SDLFPoint(25.0f, 30.0f)));
}

std::vector<Entity*>& Map::getEntities()
{
    return m_entities;
}

SDL_Point Map::getSize()
{
    return m_size;
}
