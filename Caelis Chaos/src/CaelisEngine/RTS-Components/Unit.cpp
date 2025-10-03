#include "Unit.h"

Unit::Unit() : Entity(){
	m_sType = "Unit";
}


Unit::Unit(SDL_FPoint initialCoords) : Entity(initialCoords) { // Unit utiliza el constructor de Entity
	m_sType = "Unit";
    m_spriteID = "Footman";
    m_size = SDLFPoint(1.0f, 1.0f);
    //m_fMovementSpeed = 0.1f;
    //m_movementTarget = SDLFPoint(0.0f,0.0f);
}

Unit::Unit(std::string spriteID) : Entity() {
	m_sType = "Unit";
    m_spriteID = spriteID;
    m_size = SDLFPoint(1.0f, 1.0f);
    //m_fMovementSpeed = 0.1f;
    //m_movementTarget = SDLFPoint(0.0f, 0.0f);
}

Unit::Unit(Unit* prototype, SDL_FPoint initialCoords) : Entity(initialCoords){
	m_sType = "Unit";
    m_spriteID = prototype->m_spriteID;
    m_size = prototype->m_size;
    m_fMovementSpeed = 0.1f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
}

