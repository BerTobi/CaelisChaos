#include "MainMenu.h"
#include "SingleplayerLobby.h"
#include "../CaelisEngine.h"
#include <cstdio>

MainMenu::MainMenu()
{
    GUIComponents = {};
}

void MainMenu::init(CaelisEngine* game)
{
    game->setScreenResolution(1280, 720);
    Button* button = new Button({ 400, 100 }, 500, 100, { 100, 100, 100, 255 });
    GUIComponents.push_back(button);
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
        handleGUI(eventHandler, game);
    }
}

void MainMenu::render(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderGUI(renderer);
    SDL_RenderPresent(renderer);
}

