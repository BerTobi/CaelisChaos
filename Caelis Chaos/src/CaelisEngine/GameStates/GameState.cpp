#include "GameState.h"

void GameState::handleGUIEvents(SDL_Event* eventHandler, CaelisEngine* game)
{

    for (auto it = m_GUIComponents.begin(); it != m_GUIComponents.end(); ++it)
	{
		auto& name = it->first;         // Access the key
		auto& component = it->second;   // Access the value
		component->handleEvents(eventHandler);
	}
}

void GameState::renderGUI(SDL_Renderer* renderer)
{
	for (auto it = m_GUIComponents.begin(); it != m_GUIComponents.end(); ++it)
	{
		auto& name = it->first;         // Access the key
		auto& component = it->second;   // Access the value
		component->draw(renderer);
	}
}