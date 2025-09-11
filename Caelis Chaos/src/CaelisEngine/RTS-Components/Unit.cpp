#include "Unit.h"

Unit::Unit(SDL_FPoint initialCoords) : Entity(initialCoords) { // Unit utiliza el constructor de Entity
    m_spriteID = "Footman";
    m_size = SDLFPoint(0.5f, 1.0f);
}
