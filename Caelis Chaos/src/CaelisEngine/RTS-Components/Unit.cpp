#include "Unit.h"

Unit::Unit(SDL_FPoint initialCoords) : Entity(initialCoords) { // Unit utiliza el constructor de Entity
    m_spriteID = "Footman";
    m_fSize = 0.7f;
}
