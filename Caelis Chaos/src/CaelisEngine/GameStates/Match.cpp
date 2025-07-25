#include "Match.h"
#include "../CaelisEngine.h"
#include <cstdio>


Match::Match()
{
    GUIComponents = {};
    m_backgroundColor = { 0, 200, 0, 255 };
}

void Match::init(CaelisEngine* game)
{
}

void Match::cleanup()
{

}

void Match::update()
{

}

void Match::handleEvents(SDL_Event* eventHandler, CaelisEngine* game)
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

void Match::handleGUI(CaelisEngine* game)
{

}

void Match::render(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, COLOR_CHANNELS(m_backgroundColor));
    SDL_RenderClear(renderer);
    renderGUI(renderer);
    SDL_RenderPresent(renderer);
}
