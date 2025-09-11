#include "Building.h"

Building::Building(SDL_FPoint initialCoords) : Entity(initialCoords) {
	m_spriteID = "Fortress";
	m_size = SDLFPoint(1.0f, 2.0f);
}
