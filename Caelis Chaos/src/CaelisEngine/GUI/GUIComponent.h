#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#define COLOR_CHANNELS(color) color.r, color.g, color.b, color.a

#include <SDL3/SDL.h>

class GUIComponent
{
public:

	virtual void draw(SDL_Renderer* renderer) = 0;

	virtual ~GUIComponent() = default;

protected:

	SDL_Point m_position;
	int m_nWidth;
	int m_nHeight;

};

#endif
