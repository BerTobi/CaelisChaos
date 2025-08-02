#include "Map.h"

Map::Map()
{
	entities.push_back(Entity({ 10.0f, 0.0f }));
	entities.push_back(Entity({ -10.0f, 0.0f }));
	entities.push_back(Entity({ 0.0f, 10.0f }));
	entities.push_back(Entity({ 0.0f, -10.0f }));
}

std::vector<Entity>& Map::getEntities()
{
	return entities;
}