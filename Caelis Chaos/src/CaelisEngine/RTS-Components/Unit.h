#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"


class   Unit : public Entity
{
public:
    Unit();
    Unit(SDL_FPoint initialCoords);
    Unit(std::string spriteID);
    Unit(Unit* prototype, SDL_FPoint initialCoords);


private:

};

#endif
