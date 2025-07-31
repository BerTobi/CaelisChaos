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
		SDL_FPoint currentEntityCoords = entities[i].m_coords;

        SDL_FRect Border = { currentEntityCoords.x , currentEntityCoords.y, 30, 30 };

        SDL_SetRenderDrawColor(m_renderer, 200, 0, 0, 255);

        SDL_RenderFillRect(m_renderer, &Border);
	}
}