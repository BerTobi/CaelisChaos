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

	Button();

	Button(SDL_Point position, int nWidth, int nHeight, SDL_Color backgroundColor);

	void draw(SDL_Renderer* renderer);

	void handleEvents(SDL_Event* eventHandler);

	bool isPressed() const;

private:

	SDL_Color m_backgroundColor;
	int m_nCurrentState;
};

#endif
