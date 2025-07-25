#include "SingleplayerLobby.h"
#include "Match.h"
#include "../CaelisEngine.h"
#include <cstdio>


SingleplayerLobby::SingleplayerLobby()
{
    GUIComponents = {};
    m_backgroundColor = { 0, 100, 0, 255 };
}

void SingleplayerLobby::init(CaelisEngine* game)
{
    GUIComponents["Start"] = new Button({ 500, 100 }, 300, 100, { 100, 100, 100, 255 });
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
        handleGUIEvents(eventHandler, game);
    }
}

void SingleplayerLobby::handleGUI(CaelisEngine* game)
{
    if (((Button*)GUIComponents["Start"])->isPressed())
    {
        game->changeGameState(new Match);
    };
}

void SingleplayerLobby::render(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, COLOR_CHANNELS(m_backgroundColor));
    SDL_RenderClear(renderer);
    renderGUI(renderer);
    SDL_RenderPresent(renderer);
}
