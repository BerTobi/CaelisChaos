#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Button.h"

class Checkbox : public Button
{
public:
	Checkbox(bool* assigned);

	Checkbox(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font, bool* assigned);

	bool bChecked;
	bool* assignedVariable;

	void setTitle(std::string title);

	void handleEvent(SDL_Event* e);

	void render();

	LTexture mTitle;
};

#endif