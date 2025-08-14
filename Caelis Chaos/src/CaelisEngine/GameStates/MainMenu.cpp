#include "MainMenu.h"
#include "SingleplayerLobby.h"
#include "../CaelisEngine.h"
#include <cstdio>

MainMenu::MainMenu()
{
    GUIComponents = {};
    m_backgroundColor = { 0, 50, 0, 255 };
}

void MainMenu::init(CaelisEngine* game)
{
    game->setScreenResolution(720, 720);
    GUIComponents["Singleplayer Lobby"] = new Button({0.4f, 0.2f}, {0.2f, 0.1f}, game->getScreenResolution(), { 100, 100, 100, 255 });
}

void MainMenu::cleanup()
{

}

int MainMenu::update()
{
    return 0;
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
        handleGUIEvents(eventHandler, game);
    }
}

void MainMenu::handleGUI(CaelisEngine* game)
{
    if (((Button*)GUIComponents["Singleplayer Lobby"])->isPressed())
    {
        game->changeGameState(new SingleplayerLobby);
    };
}

void MainMenu::render(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, COLOR_CHANNELS(m_backgroundColor));
    SDL_RenderClear(renderer);
    renderGUI(renderer);
    SDL_RenderPresent(renderer);
}

