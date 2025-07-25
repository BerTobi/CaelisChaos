#include "GameState.h"

void GameState::handleGUIEvents(SDL_Event* eventHandler, CaelisEngine* game)
{

    for (auto& [name, component] : GUIComponents) {
        component->handleEvents(eventHandler);
    }
}

void GameState::renderGUI(SDL_Renderer* renderer)
{
    for (auto& [name, component] : GUIComponents) {
        component->draw(renderer);
    }
}