#include "Building.h"

Building::Building(SDL_FPoint initialCoords) : Entity(initialCoords) {
	m_spriteID = "Fortress";
	m_fSize = 4;
}
