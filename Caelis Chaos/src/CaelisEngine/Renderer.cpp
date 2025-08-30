#include "Renderer.h"
#include <cmath>

Renderer::Renderer(Map* gameMap, SDL_Renderer* renderer, TTF_Font* font, SDL_Point screenResolution)
{
	m_gameMap = gameMap;
	m_renderer = renderer;
	m_font = font;
	m_playerCamera = Camera( SDLFPoint(0.0f, 0.0f), SDLFPoint(32.0f, 16.0f) );
	m_screenResolution = screenResolution;
	generateTilemapTexture();
}

void Renderer::generateTilemapTexture()
{
	float textureWidth = m_gameMap->getSize().x * m_playerCamera.fTileSize.x * 2.0f;
	float textureHeight = m_gameMap->getSize().y * m_playerCamera.fTileSize.y * 2.0f;
	m_TilemapTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);

	// Render to texture instead of screen
	SDL_SetRenderTarget(m_renderer, m_TilemapTexture);
	// Clear to transparent
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
	float leftmostCoord = 0.0f;
	float rightmostCoord = m_gameMap->getSize().x;
	float bottommostCoord = 0.0f;
	float topmostCoord = m_gameMap->getSize().y;
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	//Horizontal lines
	for (float i = bottommostCoord; i <= topmostCoord; i++)
	{
		SDL_FPoint screenCoords1 = SDLFPoint((leftmostCoord - i) * m_playerCamera.fTileSize.x + (textureWidth * 0.5f), (leftmostCoord + i) * m_playerCamera.fTileSize.y);
		SDL_FPoint screenCoords2 = SDLFPoint((rightmostCoord - i) * m_playerCamera.fTileSize.x + (textureWidth * 0.5f), (rightmostCoord + i) * m_playerCamera.fTileSize.y);
		SDL_RenderLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	}
	//Vertical lines
	for (float i = leftmostCoord; i <= rightmostCoord; i++)
	{
		SDL_FPoint screenCoords1 = SDLFPoint((i - topmostCoord) * m_playerCamera.fTileSize.x + (textureWidth * 0.5f), (i + topmostCoord) * m_playerCamera.fTileSize.y);
		SDL_FPoint screenCoords2 = SDLFPoint((i - bottommostCoord) * m_playerCamera.fTileSize.x + (textureWidth * 0.5f), (i + bottommostCoord) * m_playerCamera.fTileSize.y);
		SDL_RenderLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	}

	//SDL_RenderLine(m_renderer, 0.0f, 0.0f, (textureWidth - 1.0f), 0.0f);
	//SDL_RenderLine(m_renderer, (textureWidth - 1.0f), 0.0f, (textureWidth - 1.0f), (textureHeight - 1.0f));
	//SDL_RenderLine(m_renderer, (textureWidth - 1.0f), (textureHeight - 1.0f), 0.0f, (textureHeight - 1.0f));
	//SDL_RenderLine(m_renderer, 0.0f, (textureHeight - 1.0f), 0.0f, 0.0f);
	SDL_SetRenderTarget(m_renderer, nullptr);
}

void Renderer::moveCamera(SDL_FPoint offset)
{
	m_playerCamera.coords.x += offset.x;
	m_playerCamera.coords.y += offset.y;
	//generateTilemapTexture();
}

void Renderer::scaleCameraTileSizeBy(float scaling)
{
	m_playerCamera.fTileSize.x *= scaling;
	m_playerCamera.fTileSize.y *= scaling;
	//generateTilemapTexture();
}

void Renderer::changeCameraTileSizeBy(int pixelAmount)
{
	//if (m_playerCamera.fTileSize.x + pixelAmount > 1.0f) m_playerCamera.fTileSize.x += pixelAmount;
	//if (m_playerCamera.fTileSize.y + pixelAmount > 1.0f) m_playerCamera.fTileSize.y += pixelAmount;
	m_playerCamera.fTileSize.y += pixelAmount;
	//generateTilemapTexture();
}

SDL_FPoint Renderer::translateMapCoordsToScreenCoords(SDL_FPoint mapCoords) {
	return SDLFPoint(
		((mapCoords.x - m_playerCamera.coords.x) - (mapCoords.y - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.x * 0.5f + m_screenResolution.x * 0.5f,
		((mapCoords.x - m_playerCamera.coords.x) + (mapCoords.y - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.y * 0.5f + m_screenResolution.y * 0.5f
	);
}

void Renderer::renderEntities()
{
    std::vector<Entity*> entities = m_gameMap->getEntities();

	for (int i = 0; i < (int)entities.size(); i++)
	{
        SDL_FPoint currentEntityCoords = entities[i]->m_coords;
		SDL_FPoint entitySizeInScreen = { entities[i]->m_fSize * m_playerCamera.fTileSize.x, entities[i]->m_fSize * m_playerCamera.fTileSize.y };
		SDL_FPoint currentEntitySpriteOffset = { entitySizeInScreen.x / 2.0f, entitySizeInScreen.y / 2.0f };

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
	//float leftmostCoord = -(m_gameMap->getSize().x / 2.0f);
	//float rightmostCoord = m_gameMap->getSize().x / 2.0f;
	//float bottommostCoord = -(m_gameMap->getSize().y / 2.0f);
	//float topmostCoord = m_gameMap->getSize().y / 2.0f;
	//SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	//
	////Horizontal lines
	//for (float i = leftmostCoord; i <= rightmostCoord; i++)
	//{
	//	SDL_FPoint screenCoords1 = translateMapCoordsToScreenCoords(SDLFPoint(leftmostCoord, i));
	//	SDL_FPoint screenCoords2 = translateMapCoordsToScreenCoords(SDLFPoint(rightmostCoord, i));
	//	SDL_RenderLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	//}
	////Vertical lines
	//for (float i = bottommostCoord; i <= topmostCoord; i++)
	//{
	//	SDL_FPoint screenCoords1 = translateMapCoordsToScreenCoords(SDLFPoint(i, bottommostCoord));
	//	SDL_FPoint screenCoords2 = translateMapCoordsToScreenCoords(SDLFPoint(i, topmostCoord));
	//	SDL_RenderLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	//}

	float leftmostCoord = -(m_gameMap->getSize().x / 2.0f);
	float bottommostCoord = -(m_gameMap->getSize().y / 2.0f);
	float rightmostCoord = m_gameMap->getSize().x / 2.0f;
	float topmostCoord = m_gameMap->getSize().y / 2.0f;
	
	SDL_FPoint screenCoords1 = translateMapCoordsToScreenCoords(SDLFPoint(0.0f, 0.0f));
	SDL_FPoint screenCoords2 = translateMapCoordsToScreenCoords(SDLFPoint(10.0f, 10.0f));

	SDL_FPoint currentMapCoords = SDLFPoint(0.0f, 0.0f);
	SDL_FPoint mapSizeInScreen = { m_gameMap->getSize().x * m_playerCamera.fTileSize.x, m_gameMap->getSize().y * m_playerCamera.fTileSize.y };
	SDL_FPoint currentMapSpriteOffset = { mapSizeInScreen.x / 2.0f, mapSizeInScreen.y / 2.0f };


	SDL_FPoint currentMapScreenCoords = translateMapCoordsToScreenCoords(currentMapCoords);
	
	SDL_FRect screenMap = SDLFRect(currentMapScreenCoords.x - currentMapSpriteOffset.x, currentMapScreenCoords.y - currentMapSpriteOffset.y, mapSizeInScreen.x, mapSizeInScreen.y);

	SDL_RenderTexture(m_renderer, m_TilemapTexture, nullptr, &screenMap);
}
