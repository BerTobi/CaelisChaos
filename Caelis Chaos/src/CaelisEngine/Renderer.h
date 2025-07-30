#ifndef RENDERER_H
#define RENDERER_H

#include "RTS-Components/Map.h"
#include <SDL3/SDL.h>

class Renderer
{
public:

	Renderer(Map* gameMap, SDL_Renderer* renderer);

	void renderEntities();

private:

	Map* m_gameMap;
	SDL_Renderer* m_renderer;

};

#endif

