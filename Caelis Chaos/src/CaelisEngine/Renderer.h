#ifndef RENDERER_H
#define RENDERER_H

#include "RTS-Components/Map.h"
#include "Graphics/Texture.h"
#include "Utilities/Util.h"
#include <SDL3/SDL.h>
#include <unordered_map>

struct Camera
{
	SDL_FPoint coords;
	SDL_FPoint fTileSize;

	Camera() : coords(SDLFPoint(0.0f, 0.0f)), fTileSize(SDLFPoint(128.0f, 64.0f)) {}

	Camera(SDL_FPoint newCoords, SDL_FPoint newfTileSize) : coords(newCoords), fTileSize(newfTileSize) {}
};

class Renderer
{
public:

	Renderer(Map* gameMap, SDL_Renderer* renderer, TTF_Font* font, SDL_Point screenResolution);

	void moveCamera(SDL_FPoint offset);

	SDL_FPoint translateMapCoordsToScreenCoords(SDL_FPoint mapCoords);

	void renderEntities();
	void renderTiles();

	void scaleCameraTileSizeBy(float scaling);
	void changeCameraTileSizeBy(int pixelAmount);

	void generateTilemapTexture();

	void loadSprite(std::string id, std::string path);

private:

	Map* m_gameMap;
	SDL_Renderer* m_renderer;
	TTF_Font* m_font;
	Camera m_playerCamera;
	SDL_Point m_screenResolution;

	SDL_Texture* m_TilemapTexture;

	std::unordered_map<std::string, Texture> m_spriteManager;

};

#endif

