#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "Utilities/Util.h"

struct Camera
{
	SDL_FPoint coords;
	SDL_FPoint fTileSize;

	Camera() : coords(SDLFPoint(0.0f, 0.0f)), fTileSize(SDLFPoint(128.0f, 64.0f)) {}

	Camera(SDL_FPoint newCoords, SDL_FPoint newfTileSize) : coords(newCoords), fTileSize(newfTileSize) {}
};

class Player
{
public:

	Player();
	Player(int nTeam);

	Camera m_Camera;

private:
	int m_nGold;
	int m_nTeam;
	
};

#endif