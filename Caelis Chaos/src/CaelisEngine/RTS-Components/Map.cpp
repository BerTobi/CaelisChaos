#include "Map.h"

Map::Map()
{
	entities.push_back(*(new Entity));
	entities.push_back(*(new Entity));
	entities.push_back(*(new Entity));
	entities.push_back(*(new Entity));
}

std::vector<Entity>& Map::getEntities()
{
	return entities;
}