#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include <vector>

class Map
{
public:

	Map();

	std::vector<Entity>& getEntities();

private:

	std::vector<Entity> entities;

};

#endif

