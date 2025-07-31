#include "Map.h"

Map::Map()
{
	entities.push_back(Entity({ 600.0f, 500.0f }));
	entities.push_back(Entity({ 40.0f, 620.0f }));
	entities.push_back(Entity({ 70.0f, 120.0f }));
	entities.push_back(Entity({ 500.0f, 40.0f }));
}

std::vector<Entity>& Map::getEntities()
{
	return entities;
}