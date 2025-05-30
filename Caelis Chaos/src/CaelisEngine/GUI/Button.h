#ifndef BUTTON_H
#define BUTTON_H

#include "GUIComponent.h"

class Button : public GUIComponent
{
public:

	Button();

	Button(SDL_Point position, int nWidth, int nHeight, SDL_Color backgroundColor);

	void draw(SDL_Renderer* renderer);

private:

	SDL_Color m_backgroundColor;

};

#endif
