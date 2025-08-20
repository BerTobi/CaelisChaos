#ifndef SINGLEPLAYERLOBBY_H
#define SINGLEPLAYERLOBBY_H

#include "GameState.h"


class SingleplayerLobby : public GameState
{
public:

    SingleplayerLobby();

    void init(CaelisEngine* game);
    void cleanup();

    void handleEvents(SDL_Event* eventHandler, CaelisEngine* game);
    void handleGUI(CaelisEngine* game);

    std::uint64_t update();
    void render(SDL_Window* window, SDL_Renderer* renderer);


};

#endif
