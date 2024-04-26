#ifndef MENU_H
#define MENU_H

#include "LTexture.h"
#include "Button.h"
#include "TextBox.h"
#include <map>
#include <string>

class Menu
{
public:

	Menu();

	Menu(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

	void setLayer(int layer);

	void setPosition(float x, float y);

	void setSize(float width, float height);

	void setTableSize(int rows, int colums);

	void setBorderThickness(int thickness);
	
	void addButton(std::string name, std::string text);

	bool handleEvent(SDL_Event* e);

	void enable(bool state);

	bool isEnabled();

	//Show button sprite
	void render();

	void free();

	std::map<std::string, Button*> Buttons;
	TextBox Title;
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
