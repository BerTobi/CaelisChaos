#ifndef DROPDOWNMENU_H
#define DROPDOWNMENU_H

#include "Menu.h"

class DropdownMenu
{
public:

	DropdownMenu();

	DropdownMenu(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

	void setTitle(std::string title);

	void setLayer(int layer);

	void setPosition(float x, float y);

	void setSize(float width, float height);

	void setButtonSize(float width, float height);

	void setBorderThickness(int thickness);

	void addItem(std::string name, std::string text);

	bool handleEvent(SDL_Event* e);

	void enable(bool state);

	bool isEnabled();

	//Show button sprite
	void render();

	void free();

	Button* button;
	Menu* menu;
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

	int mColumns, mRows;

	bool mEnabled;

};

#endif