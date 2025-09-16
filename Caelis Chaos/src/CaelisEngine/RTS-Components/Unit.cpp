#include "Unit.h"

Unit::Unit() : Entity(){

}


Unit::Unit(SDL_FPoint initialCoords) : Entity(initialCoords) { // Unit utiliza el constructor de Entity
    m_spriteID = "Footman";
    m_size = SDLFPoint(0.5f, 1.0f);
}

Unit::Unit(std::string spriteID) : Entity() {
    m_spriteID = spriteID;
    m_size = SDLFPoint(0.5f, 1.0f);
}

Unit::Unit(Unit* prototype, SDL_FPoint initialCoords) : Entity(initialCoords){
    m_spriteID = prototype->m_spriteID;
    m_size = prototype->m_size;
}

