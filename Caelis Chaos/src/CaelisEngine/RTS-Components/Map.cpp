#include "Map.h"


Map::Map()
{
    m_size = { 128, 128 };

    m_entities.push_back( new Building({ 30.0f, 30.0f }));
    m_entities.push_back( new Building({ -30.0f,30.0f }));
    m_entities.push_back( new Building({ 30.0f, -30.0f }));
    m_entities.push_back( new Building({ -30.0f, -30.0f }));
    m_entities.push_back( new Unit({ 0.0f, 0.0f }));
}

std::vector<Entity*>& Map::getEntities()
{
    return m_entities;
}

SDL_Point Map::getSize()
{
    return m_size;
}
