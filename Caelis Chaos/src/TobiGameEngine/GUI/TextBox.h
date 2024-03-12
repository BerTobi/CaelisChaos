#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "LTexture.h"

class TextBox
{
public:

	TextBox();

	TextBox(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

	void editable(bool editable);

	void showBorder(bool show);

	//Sets top left position
	void setPosition(float x, float y);

	void setSize(float width, float height);

	void setFontSize(int size);

	void setText(std::string text);

	void handleEvent(SDL_Event* e);

	void enable(bool state);

	bool isEnabled();

	//Show button sprite
	void render();

	void free();

	std::string mText;

private:

	//Top left position
	SDL_Point mPosition;
	LTexture mSprite;

	SDL_Renderer* mRenderer;

	int mHeight;
	int mWidth;
	int mFontSize;

	bool mEditable;
	bool mShowBorder;
	bool mEnabled;

	int mScreenHeight;
	int mScreenWidth;
};


#endif