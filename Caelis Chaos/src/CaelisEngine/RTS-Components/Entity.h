#ifndef ENTITY_H
#define ENTITY_H
#include <SDL3/SDL.h>

class Entity
{
public:

	Entity(SDL_FPoint initialCoords);

	SDL_FPoint m_coords;
	float m_fSize;

private:

};

#endif

