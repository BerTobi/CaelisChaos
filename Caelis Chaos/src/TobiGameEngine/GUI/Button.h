#ifndef BUTTON_H
#define BUTTON_H

#include "LTexture.h"

enum ButtonState
{
	BUTTON_STATE_MOUSE_OUT = 0,
	BUTTON_STATE_MOUSE_OVER_MOTION = 1,
	BUTTON_STATE_MOUSE_DOWN = 2,
	BUTTON_STATE_MOUSE_UP = 3,
	BUTTON_STATE_TOTAL = 4
};

class Button
{
public:

	//Constructor
	Button();

	Button(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

	void setLayer(int layer);

	//Sets top left position
	void setPosition(float x, float y);

	void setText(std::string text);

	void setSize(float width, float height);

	void setVisibility(bool visible);

	void setBorderThickness(int thickness);

	//Handle mouse event
	void handleEvent(SDL_Event* e);

	//Show button sprite
	void render();

	void free();

	bool bPressed;
	bool bHovered;
	bool bVisible;
	int mLayer;

private:

	//Top left position
	SDL_Point mPosition;
	LTexture mButtonSprite;

	SDL_Renderer* mRenderer;
	
	std::string mText;
	ButtonState mState;

	int mHeight;
	int mWidth;

	int mScreenHeight;
	int mScreenWidth;

	int mBorderThickness;
};

#endif