#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"

class Building : public Entity
{
public:
    Building();
    Building(SDL_FPoint initialCoords);
    Building(std::string spriteID);
    Building(Building* prototype, SDL_FPoint initialCoords);

private:
};

#endif





