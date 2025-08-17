#ifndef RENDERER_H
#define RENDERER_H

#include "RTS-Components/Map.h"
#include "Graphics/Texture.h"
#include <SDL3/SDL.h>

struct Camera
{
	SDL_FPoint coords;
	SDL_FPoint fTileSize;
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

private:

	Map* m_gameMap;
	SDL_Renderer* m_renderer;
	TTF_Font* m_font;
	Camera m_playerCamera;
	SDL_Point m_screenResolution;

};

#endif

