#ifndef GAMESTATE_H
#define GAMESTATE_H

#define COLOR_CHANNELS(color) color.r, color.g, color.b, color.a

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include "GUI/Button.h"

class CaelisEngine;

class GameState
{

public:
	
	// = 0 means it's a pure virtual function

	virtual void init(CaelisEngine* game) = 0;
	virtual void cleanup() = 0;

	virtual void handleEvents(SDL_Event* eventHandler, CaelisEngine* game) = 0;
	virtual void handleGUIEvents(SDL_Event* eventHandler, CaelisEngine* game);
	virtual void handleGUI(CaelisEngine* game) = 0;
	virtual void update() = 0;
	virtual void render(SDL_Window* window, SDL_Renderer* renderer) = 0;
	virtual void renderGUI(SDL_Renderer* renderer);

	virtual ~GameState() = default;

protected:

	//Interfaz
	std::unordered_map<std::string, GUIComponent*> GUIComponents;
	SDL_Color m_backgroundColor;
	
	
};

#endif
