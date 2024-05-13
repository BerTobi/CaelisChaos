#ifndef UNITHUD_H
#define UNITHUD_H

#include "ListUI.h"

class UnitHUD
{
public:

	UnitHUD();

	UnitHUD(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

	void free();

	void setLayer(int layer);

	void setPosition(float x, float y);

	void setSize(float width, float height);

	void enable(bool state);

	bool isEnabled();

	void render();

	ListUI* stats;
	int mLayer;

private:

	SDL_Point mPosition;
	float mRelativePositionX;
	float mRelativePositionY;
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
	TTF_Font* mFont;

	int mBorderThickness;

	int mHeight;
	int mWidth;

	float mRelativeHeight;
	float mRelativeWidth;

	int mScreenHeight;
	int mScreenWidth;

	bool mEnabled;
};

#endif
