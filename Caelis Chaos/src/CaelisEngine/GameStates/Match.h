#ifndef MATCH_H
#define MATCH_H

#include "GameState.h"
#include "RTS-Components/Map.h"
#include "Renderer.h"


class Match : public GameState
{
public:

	Match();

	void init(CaelisEngine* game);
	void cleanup();

	void handleEvents(SDL_Event* eventHandler, CaelisEngine* game);
	void handleGUI(CaelisEngine* game);

	void update();
	void render(SDL_Window* window, SDL_Renderer* renderer);

private:

	Map* gameMap;
	Renderer* gameRenderer;
	const bool* keyboardState;

};

#endif
