#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include <vector>

class Map
{
public:

	Map();

	std::vector<Entity>& getEntities();
	SDL_Point getSize();

private:

	std::vector<Entity> entities;
	SDL_Point m_size;

};

#endif

