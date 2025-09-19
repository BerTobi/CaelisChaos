#include "Building.h"

Building::Building() : Entity(){

}

Building::Building(SDL_FPoint initialCoords) : Entity(initialCoords) {
	m_spriteID = "Fortress";
	m_size = SDLFPoint(1.0f, 2.0f);
}


Building::Building(std::string spriteID) : Entity() {
    m_spriteID = spriteID;
    m_size = SDLFPoint(1.0f, 2.0f);
}

Building::Building(Building* prototype, SDL_FPoint initialCoords) : Entity(initialCoords){
    m_spriteID = prototype->m_spriteID;
    m_size = prototype->m_size;
}

