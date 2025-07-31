#ifndef RENDERER_H
#define RENDERER_H

#include "RTS-Components/Map.h"
#include <SDL3/SDL.h>

struct Camera
{
	SDL_FPoint coords;
};

class Renderer
{
public:

	Renderer(Map* gameMap, SDL_Renderer* renderer);

	void moveCamera(SDL_FPoint offset);

	void renderEntities();

private:

	Map* m_gameMap;
	SDL_Renderer* m_renderer;
	Camera playerCamera;

};

#endif

