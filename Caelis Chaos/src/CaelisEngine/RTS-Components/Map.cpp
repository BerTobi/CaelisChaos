#include "Map.h"

Map::Map()
{
	m_size = { 128, 128 };

	entities.push_back(Entity({ 30.0f, 30.0f }));
	entities.push_back(Entity({ -30.0f,30.0f }));
	entities.push_back(Entity({ 30.0f, -30.0f }));
	entities.push_back(Entity({ -30.0f, -30.0f }));
}

std::vector<Entity>& Map::getEntities()
{
	return entities;
}

SDL_Point Map::getSize()
{
	return m_size;
}