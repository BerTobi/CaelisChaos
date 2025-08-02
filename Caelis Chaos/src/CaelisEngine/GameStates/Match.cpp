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
    gameMap = new Map();
    gameRenderer = new Renderer(gameMap, game->getRenderer(), game->getScreenResolution());
    keyboardState = game->keyboardState;
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
            if (keyboardState[SDL_SCANCODE_UP]) gameRenderer->moveCamera({0.0f, -0.1f});
            if (keyboardState[SDL_SCANCODE_DOWN]) gameRenderer->moveCamera({ 0.0f, 0.1f });
            if (keyboardState[SDL_SCANCODE_LEFT]) gameRenderer->moveCamera({ -0.1f, 0.0f });
            if (keyboardState[SDL_SCANCODE_RIGHT]) gameRenderer->moveCamera({ 0.1f, 0.0f });
            if (keyboardState[SDL_SCANCODE_Z]) gameRenderer->changeCameraTileSizeBy(1);
            if (keyboardState[SDL_SCANCODE_X]) gameRenderer->changeCameraTileSizeBy(-1);
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
    gameRenderer->renderEntities();
    gameRenderer->renderTiles();
    SDL_RenderPresent(renderer);
    
}
