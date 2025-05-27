#include "SingleplayerLobby.h"
#include "../CaelisEngine.h"
#include <cstdio>


SingleplayerLobby::SingleplayerLobby()
{

}

void SingleplayerLobby::init(CaelisEngine* game)
{

}

void SingleplayerLobby::cleanup()
{

}

void SingleplayerLobby::update()
{

}

void SingleplayerLobby::handleEvents(SDL_Event* eventHandler, CaelisEngine* game)
{
    while (SDL_PollEvent(eventHandler) != 0)
    {
        switch (eventHandler->type)
        {
            case SDL_EVENT_QUIT:
                game->quit();
                break;

            case SDL_EVENT_KEY_DOWN:
                printf("Key pressed in singleplayer lobby!");
                break;
        }
    }
}

void SingleplayerLobby::draw(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}