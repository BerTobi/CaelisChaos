#include "Renderer.h"
#include <cmath>

Renderer::Renderer(Map* gameMap, SDL_Renderer* renderer, SDL_Point screenResolution)
{
	m_gameMap = gameMap;
	m_renderer = renderer;
	m_playerCamera = { 0.0f, 0.0f, 128.0f, 64.0f };
	m_screenResolution = screenResolution;
}

void Renderer::moveCamera(SDL_FPoint offset)
{
	m_playerCamera.coords.x += offset.x;
	m_playerCamera.coords.y += offset.y;
}

void Renderer::scaleCameraTileSizeBy(float scaling)
{
	m_playerCamera.fTileSize.x *= scaling;
	m_playerCamera.fTileSize.y *= scaling;
}

void Renderer::changeCameraTileSizeBy(int pixelAmount)
{
	//if (m_playerCamera.fTileSize.x + pixelAmount > 1.0f) m_playerCamera.fTileSize.x += pixelAmount;
	//if (m_playerCamera.fTileSize.y + pixelAmount > 1.0f) m_playerCamera.fTileSize.y += pixelAmount;
	m_playerCamera.fTileSize.y += pixelAmount;
}

SDL_FPoint Renderer::translateMapCoordsToScreenCoords(SDL_FPoint mapCoords) {
	return {
		((mapCoords.x - m_playerCamera.coords.x) - (mapCoords.y - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.x * 0.5f + m_screenResolution.x * 0.5f,
		((mapCoords.x - m_playerCamera.coords.x) + (mapCoords.y - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.y * 0.5f + m_screenResolution.y * 0.5f
	};
}

void Renderer::renderEntities()
{
    std::vector<Entity*> entities = m_gameMap->getEntities();

	for (int i = 0; i < (int)entities.size(); i++)
	{
        SDL_FPoint currentEntityCoords = entities[i]->m_coords;
		SDL_FPoint entitySizeInScreen = { entities[i]->m_fSize * m_playerCamera.fTileSize.x, entities[i]->m_fSize * m_playerCamera.fTileSize.y };
		SDL_FPoint currentEntitySpriteOffset = { entitySizeInScreen.x / 2.0f, entitySizeInScreen.y / 2.0f };

		//SDL_FPoint currentEntityScreenCoords = { ((currentEntityCoords.x - m_playerCamera.coords.x) - (currentEntityCoords.y - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.x * 0.5f, ((currentEntityCoords.x - m_playerCamera.coords.x) + (currentEntityCoords.y - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.y * 0.5f };
		SDL_FPoint currentEntityScreenCoords = translateMapCoordsToScreenCoords(entities[i]->m_coords);

		SDL_Vertex topFace[3] = {
			// top point
            {currentEntityScreenCoords.x, currentEntityScreenCoords.y - currentEntitySpriteOffset.y, 1,0,0,1},
			// left point  
            {currentEntityScreenCoords.x - currentEntitySpriteOffset.x, currentEntityScreenCoords.y, 1,0,0,1},
			// right point
            {currentEntityScreenCoords.x + currentEntitySpriteOffset.x, currentEntityScreenCoords.y, 1,0,0,1}
		};

		// Your second triangle should be:
		SDL_Vertex topFace2[3] = {
			// bottom point of diamond (shifted up)
            {currentEntityScreenCoords.x, currentEntityScreenCoords.y + currentEntitySpriteOffset.y, 1,0,0,1},
			// left point (shifted up)  
            {currentEntityScreenCoords.x - currentEntitySpriteOffset.x, currentEntityScreenCoords.y, 1,0,0,1},
			// right point (shifted up)
            {currentEntityScreenCoords.x + currentEntitySpriteOffset.x, currentEntityScreenCoords.y, 1,0,0,1}
		};


        SDL_SetRenderDrawColor(m_renderer, 200, 0, 0, 255);

		SDL_RenderGeometry(m_renderer, NULL, topFace, 3, NULL, 0);
		SDL_RenderGeometry(m_renderer, NULL, topFace2, 3, NULL, 0);


        //SDL_RenderFillRect(m_renderer, &Border);
	}
}

void Renderer::renderTiles()
{
	float leftmostCoord = -(m_gameMap->getSize().x / 2.0f);
	float rightmostCoord = m_gameMap->getSize().x / 2.0f;
	float bottommostCoord = -(m_gameMap->getSize().y / 2.0f);
	float topmostCoord = m_gameMap->getSize().y / 2.0f;
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	//Horizontal lines
	for (float i = leftmostCoord; i <= rightmostCoord; i++)
	{
		SDL_FPoint screenCoords1 = translateMapCoordsToScreenCoords({ leftmostCoord, i });
		SDL_FPoint screenCoords2 = translateMapCoordsToScreenCoords({ rightmostCoord, i });
		SDL_RenderLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	}
	//Vertical lines
	for (float i = bottommostCoord; i <= topmostCoord; i++)
	{
		SDL_FPoint screenCoords1 = translateMapCoordsToScreenCoords({ i, bottommostCoord });
		SDL_FPoint screenCoords2 = translateMapCoordsToScreenCoords({ i, topmostCoord });
		SDL_RenderLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	}
}
