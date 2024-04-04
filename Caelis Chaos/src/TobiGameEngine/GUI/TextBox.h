#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "LTexture.h"

class TextBox
{
public:

	TextBox();

	TextBox(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

	void setLayer(int layer);

	void editable(bool editable);

	void showBorder(bool show);

	//Sets top left position
	void setPosition(float x, float y);

	void setSize(float width, float height);

	void setLength(int length);

	void setFontSize(int size);

	void setFontSizeRelative(float size);

	void setText(std::string text);

	void setTextColor(SDL_Color color);

	void setBackgroundColor(SDL_Color color);

	void handleEvent(SDL_Event* e);

	void enable(bool state);

	void setAlignment(std::string alignment);

	bool isEnabled();

	//Show button sprite
	void render();

	void free();

	std::string mText;
	std::string mTextAlignment;
	int mLayer;

private:

	//Top left position
	SDL_Point mPosition;
	SDL_Color mTextColor;
	SDL_Color mBackgroundColor;

	LTexture mSprite;

	SDL_Renderer* mRenderer;

	int mHeight;
	int mWidth;
	int mFontSize;
	int mTextLength;

	bool mEditable;
	bool mShowBorder;
	bool mEnabled;

	int mScreenHeight;
	int mScreenWidth;
};


#endif