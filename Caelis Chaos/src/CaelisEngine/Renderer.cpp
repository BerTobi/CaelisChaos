#include "Renderer.h"
#include <cmath>

Renderer::Renderer(Map* gameMap, SDL_Renderer* renderer, TTF_Font* font, SDL_Point screenResolution)
{
	m_gameMap = gameMap;
	m_renderer = renderer;
	m_font = font;
	m_playerCamera = Camera( SDLFPoint(0.0f, 0.0f), SDLFPoint(8.0f, 4.0f) );
	m_screenResolution = screenResolution;
	generateTilemapTexture();
	loadSprite("Fortress", "res/textures/Buildings/CGA0-Tower.png");
	loadSprite("Tower", "res/textures/Buildings/Cami-Tower.png");
	loadSprite("Footman", "res/textures/Buildings/CGA-Footman.png");
    loadSprite("Mage", "res/textures/Mage.png");
}

void Renderer::renderDottedLine(SDL_Renderer* renderer, float startX, float startY, float endX, float endY, int dotSpacing) 
{
    float horizontal_distance = abs(endX - startX);
    float vertical_distance = abs(endY - startY);
    float x_step_direction = (startX < endX) ? 1 : -1;
    float y_step_direction = (startY < endY) ? 1 : -1;
    float bresenham_error = horizontal_distance - vertical_distance;
    
    float current_x = startX;
    float current_y = startY;
    int pixels_traversed = 0;
    
    while (true) {
        bool should_draw_dot = (pixels_traversed % dotSpacing == 0);
        if (should_draw_dot) {
            SDL_RenderPoint(renderer, current_x, current_y);
        }
        
        bool reached_destination = (current_x == endX && current_y == endY);
        if (reached_destination) break;
        
        float double_error = 2 * bresenham_error;
        
        bool should_step_horizontally = (double_error > -vertical_distance);
        if (should_step_horizontally) {
            bresenham_error -= vertical_distance;
            current_x += x_step_direction;
        }
        
        bool should_step_vertically = (double_error < horizontal_distance);
        if (should_step_vertically) {
            bresenham_error += horizontal_distance;
            current_y += y_step_direction;
        }
        
        pixels_traversed++;
    }
}

void Renderer::generateTilemapTexture()
{
	float textureWidth = m_gameMap->getSize().x * m_playerCamera.fTileSize.x * 2.0f;
	float textureHeight = m_gameMap->getSize().y * m_playerCamera.fTileSize.y * 2.0f;
	m_TilemapTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, static_cast<int>(textureWidth), static_cast<int>(textureHeight));

	SDL_SetTextureScaleMode(m_TilemapTexture, SDL_SCALEMODE_NEAREST);
	// Render to texture instead of screen
	SDL_SetRenderTarget(m_renderer, m_TilemapTexture);
	// Clear to transparent
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0);
	SDL_RenderClear(m_renderer);
	float leftmostCoord = 0.0f;
	float rightmostCoord = static_cast<float>(m_gameMap->getSize().x);
	float bottommostCoord = 0.0f;
	float topmostCoord = static_cast<float>(m_gameMap->getSize().y);
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 255);

	//Horizontal lines
	for (float i = bottommostCoord; i <= topmostCoord; i++)
	{
		SDL_FPoint screenCoords1 = SDLFPoint((leftmostCoord - i) * m_playerCamera.fTileSize.x + (textureWidth * 0.5f), (leftmostCoord + i) * m_playerCamera.fTileSize.y);
		SDL_FPoint screenCoords2 = SDLFPoint((rightmostCoord - i) * m_playerCamera.fTileSize.x + (textureWidth * 0.5f), (rightmostCoord + i) * m_playerCamera.fTileSize.y);
		renderDottedLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y,2);
	}
	//Vertical lines
	for (float i = leftmostCoord; i <= rightmostCoord; i++)
	{
		SDL_FPoint screenCoords1 = SDLFPoint((i - topmostCoord) * m_playerCamera.fTileSize.x + (textureWidth * 0.5f), (i + topmostCoord) * m_playerCamera.fTileSize.y);
		SDL_FPoint screenCoords2 = SDLFPoint((i - bottommostCoord) * m_playerCamera.fTileSize.x + (textureWidth * 0.5f), (i + bottommostCoord) * m_playerCamera.fTileSize.y);
		renderDottedLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y,2);
	}

	SDL_SetRenderTarget(m_renderer, nullptr);
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
	generateTilemapTexture();
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
		SDL_FPoint entitySizeInScreen = { entities[i]->m_size.x * m_playerCamera.fTileSize.x * 2.0f, entities[i]->m_size.y * m_playerCamera.fTileSize.y * 2.0f };
		SDL_FPoint currentEntitySpriteOffset = { entitySizeInScreen.x / 2.0f, entitySizeInScreen.y / 2.0f };

		SDL_FPoint currentEntityScreenCoords = translateMapCoordsToScreenCoords(entities[i]->m_coords);
		SDL_FPoint offsetedEntityScreenCords = SDLFPoint(currentEntityScreenCoords.x - currentEntitySpriteOffset.x, currentEntityScreenCoords.y - currentEntitySpriteOffset.y);

		m_spriteManager[entities[i]->m_spriteID].render(m_renderer, offsetedEntityScreenCords.x, offsetedEntityScreenCords.y, nullptr, entitySizeInScreen.x, entitySizeInScreen.y);
	}

}

void Renderer::renderTiles()
{
	SDL_FPoint screenCoords1 = translateMapCoordsToScreenCoords(SDLFPoint(0.0f, 0.0f));
	SDL_FPoint screenCoords2 = translateMapCoordsToScreenCoords(SDLFPoint(10.0f, 10.0f));

	SDL_FPoint currentMapCoords = SDLFPoint(0.0f, 0.0f);
	SDL_FPoint mapSizeInScreen = { m_gameMap->getSize().x * m_playerCamera.fTileSize.x, m_gameMap->getSize().y * m_playerCamera.fTileSize.y };
	SDL_FPoint currentMapSpriteOffset = { mapSizeInScreen.x / 2.0f, mapSizeInScreen.y / 2.0f };

	SDL_FPoint currentMapScreenCoords = translateMapCoordsToScreenCoords(currentMapCoords);
	
	SDL_FRect screenMap = SDLFRect(currentMapScreenCoords.x - currentMapSpriteOffset.x, currentMapScreenCoords.y - currentMapSpriteOffset.y, mapSizeInScreen.x, mapSizeInScreen.y);

	SDL_RenderTexture(m_renderer, m_TilemapTexture, nullptr, &screenMap);
}

void Renderer::loadSprite(std::string id, std::string path)
{
	m_spriteManager[id].loadFromFile(path, m_renderer);
}
