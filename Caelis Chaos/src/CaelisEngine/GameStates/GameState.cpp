#include "GameState.h"

void GameState::handleGUI(SDL_Event* eventHandler, CaelisEngine* game)
{
    for (int i = 0; i < GUIComponents.size(); i++)
    {
        GUIComponents[i]->handleEvents(eventHandler);
    }
}

void GameState::renderGUI(SDL_Renderer* renderer)
{
    for (int i = 0; i < GUIComponents.size(); i++)
    {
        GUIComponents[i]->draw(renderer);
    }
}