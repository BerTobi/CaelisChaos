#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"


class MainMenu : public GameState
{
public:

	MainMenu();

	void init();
	void cleanup();

	void handleEvents(SDL_Event* eventHandler, CaelisEngine* game);
	void update();
	void draw(SDL_Window* window, SDL_Renderer* renderer);
	
};

#endif