#include "MainMenu.h"
#include "SingleplayerLobby.h"
#include "../CaelisEngine.h"
#include <cstdio>

MainMenu::MainMenu()
{

}

void MainMenu::init(CaelisEngine* game)
{
    game->setScreenResolution(1280, 720);
}

void MainMenu::cleanup()
{

}

void MainMenu::update()
{

}

void MainMenu::handleEvents(SDL_Event* eventHandler, CaelisEngine* game)
{


    while (SDL_PollEvent(eventHandler) != 0)
    {
        switch (eventHandler->type)
        {
            case SDL_EVENT_QUIT:
                game->quit();
                break;

            case SDL_EVENT_KEY_DOWN:
                printf("Key pressed in main menu!");
                if (game->keyboardState[SDL_SCANCODE_RIGHT])
                {
                    game->changeGameState(new SingleplayerLobby);
                }
                break;
        }
    }
}

void MainMenu::draw(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}