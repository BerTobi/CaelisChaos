#include "GameState.h"

void GameState::handleGUIEvents(SDL_Event* eventHandler, CaelisEngine* game)
{

    for (auto it = GUIComponents.begin(); it != GUIComponents.end(); ++it) 
	{
		auto& name = it->first;         // Access the key
		auto& component = it->second;   // Access the value
		component->handleEvents(eventHandler);
	}
}

void GameState::renderGUI(SDL_Renderer* renderer)
{
	for (auto it = GUIComponents.begin(); it != GUIComponents.end(); ++it) 
	{
		auto& name = it->first;         // Access the key
		auto& component = it->second;   // Access the value
		component->draw(renderer);
	}
}