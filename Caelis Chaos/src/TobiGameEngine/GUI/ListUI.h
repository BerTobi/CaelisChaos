#ifndef LISTUI_H
#define LISTUI_H

#include "LTexture.h"
#include "Button.h"
#include "TextBox.h"
#include <map>
#include <string>

class ListUI
{
public:

	ListUI();

	ListUI(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

	void setLayer(int layer);

	void setPosition(float x, float y);

	void setSize(float width, float height);

	void setTableSize(int rows, int colums);

	void setFontSize(int size);

	void addItem(std::string name, std::string text);

	void setTextColor(SDL_Color color);

	void setBackgroundColor(SDL_Color color);

	bool handleEvent(SDL_Event* e);

	void enable(bool state);

	bool isEnabled();

	//Show button sprite
	void render();

	void free();

	std::map<std::string, TextBox*> TextBoxes;
	TextBox Title;
	int mLayer;

private:

	SDL_Point mPosition;
	float mRelativePositionX;
	float mRelativePositionY;
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
	TTF_Font* mFont;

	SDL_Color mTextColor;
	SDL_Color mBackgroundColor;

	int mHeight;
	int mWidth;
	int mFontSize;

	float mRelativeHeight;
	float mRelativeWidth;

	int mScreenHeight;
	int mScreenWidth;

	int mColumns, mRows;

	bool mEnabled;
};


#endif
