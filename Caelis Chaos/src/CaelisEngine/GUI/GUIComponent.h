#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#define COLOR_CHANNELS(color) color.r, color.g, color.b, color.a

#include <SDL3/SDL.h>
#include "Utilities/Util.h"
#include "Graphics/Texture.h"

class GUIComponent
{
public:

	virtual void draw(SDL_Renderer* renderer) = 0;

	virtual void handleEvents(SDL_Event* eventHandler) = 0;

    virtual ~GUIComponent() {};

    SDL_Point translateRelativeToAbsolute(SDL_FPoint relativeCoords, SDL_Point windowResolution) const; // May need modification to support every type of container and no only window


protected:

	SDL_Point m_position;
	int m_nWidth;
	int m_nHeight;

};

#endif
