#include "Entity.h"

Entity::Entity()
{
    m_coords = SDLFPoint(0.0f, 0.0f);
    m_size = SDLFPoint(4.0f, 2.0f);
}

Entity::Entity(SDL_FPoint initialCoords)
{
	m_coords = initialCoords;
    m_size = SDLFPoint(4.0f, 2.0f);
}


