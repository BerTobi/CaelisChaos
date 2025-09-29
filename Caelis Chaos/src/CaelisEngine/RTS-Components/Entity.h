#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <string>
#include <Utilities/Util.h>

class Entity
{
public:
    Entity(SDL_FPoint initialCoords);
    Entity();
	void move();
	void move(SDL_FPoint movementTarget);
	SDL_FPoint m_coords;
	SDL_FPoint m_size;
	std::string m_spriteID;
	std::string m_sType;

	SDL_FPoint m_movementTarget;
	float m_fMovementSpeed;

private:


};

#endif

