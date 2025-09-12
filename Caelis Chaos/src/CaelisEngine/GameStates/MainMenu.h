#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"


class MainMenu : public GameState
{
public:

	MainMenu();

	void init(CaelisEngine* game);
	void cleanup();

	void handleEvents(SDL_Event* eventHandler, CaelisEngine* game);
	void handleGUI(CaelisEngine* game);

	std::uint64_t update();
	void render(SDL_Window* window, SDL_Renderer* renderer);

	
private:

	Button* button;

};

#endif
