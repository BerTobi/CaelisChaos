#include "Renderer.h"
#include <cmath>
#include <algorithm>

Renderer::Renderer(Map* gameMap, SDL_Renderer* renderer, TTF_Font* font, SDL_Point screenResolution)
{
	m_gameMap = gameMap;
	m_renderer = renderer;
	m_font = font;
	m_playerCamera = new Camera( SDLFPoint(0.0f, 0.0f), SDLFPoint(16.0f, 8.0f) );
	m_screenResolution = screenResolution;
	generateTilemapTexture();
	loadSprites();

}

Renderer::~Renderer()
{

	printf("Destroying sprites...\n");
    for (auto it = m_spriteManager.begin(); it != m_spriteManager.end(); ++it)
    {
        printf("Destroying sprite: %s\n", it->first.c_str());
        it->second.destroy();
        printf("Sprite destroyed: %s\n", it->first.c_str());
    }
    m_spriteManager.clear();
    printf("All sprites destroyed.\n");
    
    printf("Destroying tilemap...\n");
    if (m_TilemapTexture) {
        SDL_DestroyTexture(m_TilemapTexture);
        m_TilemapTexture = nullptr;
    }
    printf("Tilemap destroyed.\n");
    
    printf("Destroying font...\n");
    if (m_font) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
    printf("Font destroyed.\n");
    
    printf("About to destroy renderer...\n");
    if (m_renderer) {
        m_renderer = nullptr;
    }
    printf("Renderer destroyed.\n");
}

void Renderer::renderDottedLine(SDL_Renderer* renderer, float fStartX, float fStartY, float fEndX, float fEndY, int nDotSpacing) 
{
    float fHorizontalDistance = abs(fEndX - fStartX);
    float fVerticalDistance = abs(fEndY - fStartY);
    float fXStepDirection = (fStartX < fEndX) ? 1.0f : -1.0f;
    float fYStepDirection = (fStartY < fEndY) ? 1.0f : -1.0f;
    float fBresenhamError = fHorizontalDistance - fVerticalDistance; // look for bresenham's line algorithm
    
    float fCurrentX = fStartX;
    float fCurrentY = fStartY;
    int nPixelsTraversed = 0;
    
    while (true) 
	{
        if (nPixelsTraversed % nDotSpacing == 0) SDL_RenderPoint(renderer, fCurrentX, fCurrentY);
        
        if (fCurrentX >= fEndX && fCurrentY >= fEndY) break;
        
        if (2*fBresenhamError > -fVerticalDistance)
		{
			fBresenhamError -= fVerticalDistance;
            fCurrentX += fXStepDirection;	// horizontal step
        }
        
        if (2*fBresenhamError < fHorizontalDistance)
		{
            fBresenhamError += fHorizontalDistance;
            fCurrentY += fYStepDirection;	// vertical step
        }
        
        nPixelsTraversed++;
    }
}

void Renderer::generateTilemapTexture()
{
	float textureWidth = m_gameMap->getSize().x * m_playerCamera->fTileSize.x * 2.0f;
	float textureHeight = m_gameMap->getSize().y * m_playerCamera->fTileSize.y * 2.0f;
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
		SDL_FPoint screenCoords1 = SDLFPoint((leftmostCoord - i) * m_playerCamera->fTileSize.x + (textureWidth * 0.5f), (leftmostCoord + i) * m_playerCamera->fTileSize.y);
		SDL_FPoint screenCoords2 = SDLFPoint((rightmostCoord - i) * m_playerCamera->fTileSize.x + (textureWidth * 0.5f), (rightmostCoord + i) * m_playerCamera->fTileSize.y);
		renderDottedLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y,2);
	}
	//Vertical lines
	for (float i = leftmostCoord; i <= rightmostCoord; i++)
	{
		SDL_FPoint screenCoords1 = SDLFPoint((i - topmostCoord) * m_playerCamera->fTileSize.x + (textureWidth * 0.5f), (i + topmostCoord) * m_playerCamera->fTileSize.y);
		SDL_FPoint screenCoords2 = SDLFPoint((i - bottommostCoord) * m_playerCamera->fTileSize.x + (textureWidth * 0.5f), (i + bottommostCoord) * m_playerCamera->fTileSize.y);
		renderDottedLine(m_renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y,2);
	}

	SDL_SetRenderTarget(m_renderer, nullptr);
}

void Renderer::setCamera(Camera* camera)
{
	m_playerCamera = camera;
}

void Renderer::moveCamera(SDL_FPoint offset)
{
	m_playerCamera->coords.x += offset.x;
	m_playerCamera->coords.y += offset.y;
}

void Renderer::scaleCameraTileSizeBy(float fScaling)
{
	m_playerCamera->fTileSize.x *= fScaling;
	m_playerCamera->fTileSize.y *= fScaling;
}

void Renderer::changeCameraTileSizeBy(int nPixelAmount)
{
	//if (m_playerCamera->fTileSize.x + pixelAmount > 1.0f) m_playerCamera->fTileSize.x += pixelAmount;
	//if (m_playerCamera->fTileSize.y + pixelAmount > 1.0f) m_playerCamera->fTileSize.y += pixelAmount;
	m_playerCamera->fTileSize.x += 2 * nPixelAmount;
	m_playerCamera->fTileSize.y += nPixelAmount;
	//generateTilemapTexture();
}

SDL_FPoint Renderer::translateMapCoordsToScreenCoords(SDL_FPoint mapCoords) {
	return SDLFPoint(
		((mapCoords.x - m_playerCamera->coords.x) - (mapCoords.y - m_playerCamera->coords.y)) * m_playerCamera->fTileSize.x * 0.5f + m_screenResolution.x * 0.5f,
		((mapCoords.x - m_playerCamera->coords.x) + (mapCoords.y - m_playerCamera->coords.y)) * m_playerCamera->fTileSize.y * 0.5f + m_screenResolution.y * 0.5f
	);
}

bool comp(Entity* a, Entity* b) {
	return (a->m_coords.x + a->m_coords.y) < (b->m_coords.x + b->m_coords.y);
}

void Renderer::renderEntities()
{
    std::vector<Entity*> entities = m_gameMap->getEntities();
	std::sort(entities.begin(), entities.end(), comp);

	for (int i = 0; i < (int)entities.size(); i++)
	{
        SDL_FPoint currentEntityCoords = entities[i]->m_coords;
		SDL_FPoint entitySizeInScreen = { entities[i]->m_size.x * m_playerCamera->fTileSize.x, entities[i]->m_size.y * m_playerCamera->fTileSize.y };
		float fAspectRatio = entities[i]->m_size.y / entities[i]->m_size.x;
		SDL_FPoint currentEntitySpriteOffset = { entitySizeInScreen.x / 2.0f, entitySizeInScreen.y * (1.0f - 0.5f / fAspectRatio) };

		SDL_FPoint currentEntityScreenCoords = translateMapCoordsToScreenCoords(entities[i]->m_coords);
		SDL_FPoint offsetedEntityScreenCords = SDLFPoint(currentEntityScreenCoords.x - currentEntitySpriteOffset.x, currentEntityScreenCoords.y - currentEntitySpriteOffset.y);

		bool bDebugMode = false;
		if (bDebugMode)
		{
			SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 255);
			SDL_FRect spriteArea = SDLFRect(offsetedEntityScreenCords.x, offsetedEntityScreenCords.y, entitySizeInScreen.x, entitySizeInScreen.y);
			SDL_RenderRect(m_renderer, &spriteArea);
		}

		
		m_spriteManager[entities[i]->m_spriteID].render(m_renderer, offsetedEntityScreenCords.x, offsetedEntityScreenCords.y, nullptr, entitySizeInScreen.x, entitySizeInScreen.y);
	}

	SDL_RenderPoint(m_renderer, 640, 360);

}

void Renderer::renderTiles()
{
	SDL_FPoint screenCoords1 = translateMapCoordsToScreenCoords(SDLFPoint(0.0f, 0.0f));
	SDL_FPoint screenCoords2 = translateMapCoordsToScreenCoords(SDLFPoint(10.0f, 10.0f));

	SDL_FPoint currentMapCoords = SDLFPoint(0.0f, 0.0f);
	SDL_FPoint mapSizeInScreen = { m_gameMap->getSize().x * m_playerCamera->fTileSize.x, m_gameMap->getSize().y * m_playerCamera->fTileSize.y };
	SDL_FPoint currentMapSpriteOffset = { mapSizeInScreen.x / 2.0f, mapSizeInScreen.y / 2.0f };

	SDL_FPoint currentMapScreenCoords = translateMapCoordsToScreenCoords(currentMapCoords);
	
	SDL_FRect screenMap = SDLFRect(currentMapScreenCoords.x - currentMapSpriteOffset.x, currentMapScreenCoords.y - currentMapSpriteOffset.y, mapSizeInScreen.x, mapSizeInScreen.y);

	SDL_RenderTexture(m_renderer, m_TilemapTexture, nullptr, &screenMap);
}

void Renderer::loadSprite(std::string sId, std::string sPath)
{
	m_spriteManager[sId].loadFromFile(sPath, m_renderer);
}

void Renderer::loadSprites()
{
	loadSprite("Fortress", "res/textures/CGA0/Buildings/placeholder2.png");
	loadSprite("Tower", "res/textures/CGA0/Buildings/tower.png");
	loadSprite("Barracks", "res/textures/CGA0/Buildings/placeholder2.png");
	loadSprite("Barracks2", "res/textures/CGA0/Buildings/placeholder.png");
	loadSprite("Footman", "res/textures/CGA0/Units/Footman.png");
    loadSprite("Mage", "res/textures/CGA0/Units/Mage.png");
}
