#ifndef GAMESTATE_H
#define GAMESTATE_H

#define COLOR_CHANNELS(color) color.r, color.g, color.b, color.a

#include <unordered_map>
#include <string>
#include "GUI/Button.h"
#include "GUI/Textbox.h"
#include <cstdint>

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
    virtual std::uint64_t update() = 0;
	virtual void render(SDL_Window* window, SDL_Renderer* renderer) = 0;
    virtual void renderGUI(SDL_Renderer* renderer);

	virtual ~GameState() {};

protected:

	//Interfaz
	std::unordered_map<std::string, GUIComponent*> m_GUIComponents;
	SDL_Color m_backgroundColor;
	
	
};

#endif
