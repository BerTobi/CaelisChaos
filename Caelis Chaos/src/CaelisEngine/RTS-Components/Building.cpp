#include "Building.h"

Building::Building() : Entity(){
	m_sType = "Building";
}

Building::Building(SDL_FPoint initialCoords) : Entity(initialCoords) {
	m_sType = "Building";
	m_spriteID = "Fortress";
	m_size = SDLFPoint(1.0f, 2.0f);
}


Building::Building(std::string spriteID) : Entity() {
	m_sType = "Building";
    m_spriteID = spriteID;
    m_size = SDLFPoint(1.0f, 1.0f);
}

Building::Building(std::string spriteID, SDL_FPoint size) : Entity() {
	m_sType = "Building";
    m_spriteID = spriteID;
    m_size = size;
}

Building::Building(std::string spriteID, SDL_FPoint size, std::string type) : Entity() {
	m_sType = "Building";
    m_spriteID = spriteID;
    m_size = size;
    m_sType = type;
}

Building::Building(Building* prototype, SDL_FPoint initialCoords) : Entity(initialCoords){
	m_sType = "Building";
    m_spriteID = prototype->m_spriteID;
    m_size = prototype->m_size;
    m_sType = prototype->m_sType;
    m_abilities = prototype->m_abilities;
}

Building::Building(Building* prototype, SDL_FPoint initialCoords, int nTeam) : Entity(initialCoords, nTeam){
	m_sType = "Building";
    m_spriteID = prototype->m_spriteID;
    m_size = prototype->m_size;
    m_sType = prototype->m_sType;
    m_abilities = prototype->m_abilities;
}

