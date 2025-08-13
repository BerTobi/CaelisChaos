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
	

void Renderer::renderEntities()
{
	std::vector<Entity> entities = m_gameMap->getEntities();

	//float horizontalTilesOnHalfScreen = (m_screenResolution.x / m_playerCamera.fTileSize) / 2;
	//float verticalTilesOnHalfScreen = (m_screenResolution.y / m_playerCamera.fTileSize) / 2;

	for (int i = 0; i < (int)entities.size(); i++)
	{
		SDL_FPoint currentEntityCoords = entities[i].m_coords;
		float entitySizeInScreen = entities[i].m_fSize * m_playerCamera.fTileSize.x;
		float currentEntitySpriteOffset = entities[i].m_fSize / 2;

		// SDL_FPoint currentEntityScreenCoords = { (currentEntityCoords.x - m_playerCamera.coords.x + horizontalTilesOnHalfScreen - currentEntitySpriteOffset) * m_playerCamera.fTileSize, (currentEntityCoords.y - m_playerCamera.coords.y + verticalTilesOnHalfScreen - currentEntitySpriteOffset) * m_playerCamera.fTileSize };

		SDL_FPoint currentEntityScreenCoords = { ((currentEntityCoords.x - m_playerCamera.coords.x) - (currentEntityCoords.y - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.x * 0.5f, ((currentEntityCoords.x - m_playerCamera.coords.x) + (currentEntityCoords.y - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.y * 0.5f };
		//SDL_FRect Border = { currentEntityScreenCoords.x , currentEntityScreenCoords.y, entitySizeInScreen, entitySizeInScreen };

		// Add cube height
		float cubeHeight = m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize; // Adjust this for desired height

		SDL_Vertex topFace[3] = {
			// top point
			{currentEntityScreenCoords.x, currentEntityScreenCoords.y - (m_playerCamera.fTileSize.y * 0.5f * entities[i].m_fSize) - cubeHeight, 1,0,0,1},
			// left point  
			{currentEntityScreenCoords.x - (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y - cubeHeight, 1,0,0,1},
			// right point
			{currentEntityScreenCoords.x + (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y - cubeHeight, 1,0,0,1}
		};

		// Your second triangle should be:
		SDL_Vertex topFace2[3] = {
			// bottom point of diamond (shifted up)
			{currentEntityScreenCoords.x, currentEntityScreenCoords.y + (m_playerCamera.fTileSize.y * 0.5f * entities[i].m_fSize) - cubeHeight, 1,0,0,1},
			// left point (shifted up)  
			{currentEntityScreenCoords.x - (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y - cubeHeight, 1,0,0,1},
			// right point (shifted up)
			{currentEntityScreenCoords.x + (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y - cubeHeight, 1,0,0,1}
		};

		

		// Left face (darker red)
		SDL_Vertex leftFace[6] = { // 2 triangles = 6 vertices
			// Triangle 1
			{currentEntityScreenCoords.x - (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y, 0.7,0,0,1},
			{currentEntityScreenCoords.x, currentEntityScreenCoords.y + (m_playerCamera.fTileSize.y * 0.5f * entities[i].m_fSize), 0.7,0,0,1},
			{currentEntityScreenCoords.x, currentEntityScreenCoords.y + (m_playerCamera.fTileSize.y * 0.5f * entities[i].m_fSize) - cubeHeight, 0.7,0,0,1},
			// Triangle 2  
			{currentEntityScreenCoords.x - (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y, 0.7,0,0,1},
			{currentEntityScreenCoords.x, currentEntityScreenCoords.y + (m_playerCamera.fTileSize.y * 0.5f * entities[i].m_fSize) - cubeHeight, 0.7,0,0,1},
			{currentEntityScreenCoords.x - (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y - cubeHeight, 0.7,0,0,1}
		};

		// Left face (darker red)
		SDL_Vertex rightFace[6] = { // 2 triangles = 6 vertices
			// Triangle 1
			{currentEntityScreenCoords.x + (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y, 0.5,0,0,1},
			{currentEntityScreenCoords.x, currentEntityScreenCoords.y + (m_playerCamera.fTileSize.y * 0.5f * entities[i].m_fSize), 0.5,0,0,1},
			{currentEntityScreenCoords.x, currentEntityScreenCoords.y + (m_playerCamera.fTileSize.y * 0.5f * entities[i].m_fSize) - cubeHeight, 0.5,0,0,1},
			// Triangle 2  
			{currentEntityScreenCoords.x + (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y, 0.5,0,0,1},
			{currentEntityScreenCoords.x, currentEntityScreenCoords.y + (m_playerCamera.fTileSize.y * 0.5f * entities[i].m_fSize) - cubeHeight, 0.5,0,0,1},
			{currentEntityScreenCoords.x + (m_playerCamera.fTileSize.x * 0.5f * entities[i].m_fSize), currentEntityScreenCoords.y - cubeHeight, 0.5,0,0,1}
		};

        SDL_SetRenderDrawColor(m_renderer, 200, 0, 0, 255);

		SDL_RenderGeometry(m_renderer, NULL, topFace, 3, NULL, 0);
		SDL_RenderGeometry(m_renderer, NULL, topFace2, 3, NULL, 0);
		SDL_RenderGeometry(m_renderer, NULL, leftFace, 6, NULL, 0);
		SDL_RenderGeometry(m_renderer, NULL, rightFace, 6, NULL, 0);


        //SDL_RenderFillRect(m_renderer, &Border);
	}
}

void Renderer::renderTiles()
{
	int leftmostCoord = -(m_gameMap->getSize().x / 2);
	int rightmostCoord = m_gameMap->getSize().x / 2;
	int bottommostCoord = -(m_gameMap->getSize().y / 2);
	int topmostCoord = m_gameMap->getSize().y / 2;
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	//Horizontal lines
	for (int i = leftmostCoord; i <= rightmostCoord; i++)
	{
		float fScreenX1 = ((leftmostCoord - m_playerCamera.coords.x) - (i - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.x * 0.5f;
		float fScreenY1 = ((leftmostCoord - m_playerCamera.coords.x) + (i - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.y * 0.5f;
		float fScreenX2 = ((rightmostCoord - m_playerCamera.coords.x) - (i - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.x * 0.5f;
		float fScreenY2 = ((rightmostCoord - m_playerCamera.coords.x) + (i - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.y * 0.5f;
        SDL_RenderLine(m_renderer, fScreenX1, fScreenY1, fScreenX2, fScreenY2);
	}
	//Vertical lines
	for (int i = bottommostCoord; i <= topmostCoord; i++)
	{
		float fScreenX1 = ((i - m_playerCamera.coords.x) - (bottommostCoord - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.x * 0.5f;
		float fScreenY1 = ((i - m_playerCamera.coords.x) + (bottommostCoord - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.y * 0.5f;
		float fScreenX2 = ((i - m_playerCamera.coords.x) - (rightmostCoord - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.x * 0.5f;
		float fScreenY2 = ((i - m_playerCamera.coords.x) + (rightmostCoord - m_playerCamera.coords.y)) * m_playerCamera.fTileSize.y * 0.5f;
		SDL_RenderLine(m_renderer, fScreenX1, fScreenY1, fScreenX2, fScreenY2);
	}
}
