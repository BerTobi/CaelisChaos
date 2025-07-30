#include "Renderer.h"

Renderer::Renderer(Map* gameMap, SDL_Renderer* renderer)
{
	m_gameMap = gameMap;
	m_renderer = renderer;
}

void Renderer::renderEntities()
{
	std::vector<Entity> entities = m_gameMap->getEntities();

	for (int i = 0; i < entities.size(); i++)
	{
        SDL_FRect Border = { i * 10, i * 10, 10, 10 };

        SDL_SetRenderDrawColor(m_renderer, 200, 0, 0, 255);

        SDL_RenderFillRect(m_renderer, &Border);
	}
}