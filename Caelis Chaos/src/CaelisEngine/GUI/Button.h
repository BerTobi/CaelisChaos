#ifndef BUTTON_H
#define BUTTON_H

#include "GUIComponent.h"

enum buttonStates
{
	DISABLED,
	IDLE,
	PRESSED,
	HOVERED
};

class Button : public GUIComponent
{
public:

    Button(SDL_FPoint origin, SDL_FPoint extent, SDL_Point windowResolution, SDL_Color backgroundColor);

	void draw(SDL_Renderer* renderer);

	void handleEvents(SDL_Event* eventHandler);

	bool isPressed() const;

	void loadIconFromText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor);

private:

	SDL_Color m_backgroundColor;
	int m_nCurrentState;
	Texture m_icon;
};

#endif
