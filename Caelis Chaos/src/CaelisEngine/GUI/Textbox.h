#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "GUIComponent.h"

class Textbox : public GUIComponent
{
public:

	Textbox(SDL_FPoint origin, SDL_FPoint extent, SDL_Point windowResolution, SDL_Color backgroundColor);

	void draw(SDL_Renderer* renderer);

	void handleEvents(SDL_Event* eventHandler);

	void loadIconFromText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor);

private:

	SDL_Color m_backgroundColor;
	Texture m_icon;
};

#endif

