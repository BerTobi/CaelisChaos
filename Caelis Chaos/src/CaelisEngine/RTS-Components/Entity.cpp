#include "Entity.h"

Entity::Entity(SDL_FPoint initialCoords)
{
	m_coords = initialCoords;
    m_size = SDLFPoint(4.0f, 2.0f);
}


