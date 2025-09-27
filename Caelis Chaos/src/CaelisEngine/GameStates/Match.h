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

    std::uint64_t update();
    void updateDebugInfo(CaelisEngine* game);
    void render(SDL_Window* window, SDL_Renderer* renderer);

private:

	Map* m_gameMap;
	Renderer* m_gameRenderer;
	const bool* m_keyboardState;
    bool m_bRenderDebugInfo;
    int m_nTicksSinceStart;
    std::vector<Unit*> m_units;

};

#endif
