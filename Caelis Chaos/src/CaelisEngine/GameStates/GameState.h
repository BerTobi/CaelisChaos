#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL3/SDL.h>
#include <../CaelisEngine/GUI/Button.h>

class CaelisEngine;

class GameState
{

public:
	
	// = 0 means it's a pure virtual function

	virtual void init(CaelisEngine* game) = 0;
	virtual void cleanup() = 0;

	virtual void handleEvents(SDL_Event* eventHandler, CaelisEngine* game) = 0;
	virtual void update() = 0;
	virtual void render(SDL_Window* window, SDL_Renderer* renderer) = 0;

	virtual ~GameState() = default;

private:

	//Interfaz
	
	
};

#endif
