#include "Renderer.h"
#include <cmath>

Renderer::Renderer(Map* gameMap, SDL_Renderer* renderer, SDL_Point screenResolution)
{
	m_gameMap = gameMap;
	m_renderer = renderer;
	m_playerCamera = { 0.0f, 0.0f, 32.0f };
	m_screenResolution = screenResolution;
}

void Renderer::moveCamera(SDL_FPoint offset)
{
	m_playerCamera.coords.x += offset.x;
	m_playerCamera.coords.y += offset.y;
}

void Renderer::scaleCameraTileSizeBy(float scaling)
{
	m_playerCamera.fTileSize *= scaling;
}

void Renderer::changeCameraTileSizeBy(int pixelAmount)
{
	if (m_playerCamera.fTileSize + pixelAmount > 1.0f) m_playerCamera.fTileSize += pixelAmount;
}
	

void Renderer::renderEntities()
{
	std::vector<Entity> entities = m_gameMap->getEntities();

	float horizontalTilesOnHalfScreen = (m_screenResolution.x / m_playerCamera.fTileSize) / 2;
	float verticalTilesOnHalfScreen = (m_screenResolution.y / m_playerCamera.fTileSize) / 2;

	for (int i = 0; i < (int)entities.size(); i++)
	{
		SDL_FPoint currentEntityCoords = entities[i].m_coords;
		float entitySizeInScreen = entities[i].m_fSize * m_playerCamera.fTileSize;
		float currentEntitySpriteOffset = entities[i].m_fSize / 2;
		
		SDL_FPoint currentEntityScreenCoords = { (currentEntityCoords.x - m_playerCamera.coords.x + horizontalTilesOnHalfScreen - currentEntitySpriteOffset) * m_playerCamera.fTileSize, (currentEntityCoords.y - m_playerCamera.coords.y + verticalTilesOnHalfScreen - currentEntitySpriteOffset) * m_playerCamera.fTileSize };
		
        SDL_FRect Border = { currentEntityScreenCoords.x , currentEntityScreenCoords.y, entitySizeInScreen, entitySizeInScreen };

        SDL_SetRenderDrawColor(m_renderer, 200, 0, 0, 255);

        SDL_RenderFillRect(m_renderer, &Border);
	}
}

void Renderer::renderTiles()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	float horizontalTilesOnHalfScreen = (m_screenResolution.x / m_playerCamera.fTileSize) / 2;
	float verticalTilesOnHalfScreen = (m_screenResolution.y / m_playerCamera.fTileSize) / 2;
	for (int i = (0 - verticalTilesOnHalfScreen) - 1; i < verticalTilesOnHalfScreen + 1; i++)
	{
		float intPart;
		float tileY = (i - modf(m_playerCamera.coords.y, &intPart) + verticalTilesOnHalfScreen) * m_playerCamera.fTileSize;
		SDL_RenderLine(m_renderer, 0.0f, tileY, (float)m_screenResolution.x, tileY);
	}
	for (int i = (0 - horizontalTilesOnHalfScreen) - 1; i < horizontalTilesOnHalfScreen + 1; i++)
	{
		float intPart;
		float tileX = (i - modf(m_playerCamera.coords.x, &intPart) + horizontalTilesOnHalfScreen) * m_playerCamera.fTileSize;
		SDL_RenderLine(m_renderer, tileX, 0.0f, tileX, (float)m_screenResolution.y);
	}
}