#include "Button.h"

Button::Button()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

Button::Button(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
    mPosition.x = 0;
    mPosition.y = 0;
    
    mRenderer = renderer;
    mButtonSprite = LTexture(renderer, window, font);
}

void Button::free()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mButtonSprite.free();
}

void Button::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Button::setSize(int width, int height)
{
    mWidth = width;
    mHeight = height;
}

void Button::setText(std::string text)
{
    mText = text;
    mButtonSprite.free();
    mButtonSprite.loadFromRenderedText(mText, { 0, 0, 0 });
}

void Button::handleEvent(SDL_Event* e)
{
	//If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < mPosition.x)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (x > mPosition.x + mWidth)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < mPosition.y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > mPosition.y + mHeight)
        {
            inside = false;
        }

        //Mouse is outside button
        if (!inside)
        {
            mState = BUTTON_STATE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                mState = BUTTON_STATE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mState = BUTTON_STATE_MOUSE_DOWN;
                bPressed = true;
                break;

            case SDL_MOUSEBUTTONUP:
                mState = BUTTON_STATE_MOUSE_UP;
                break;
            }
        }
    }
}

void Button::render()
{
    SDL_Rect Border = { mPosition.x, mPosition.y, mWidth, mHeight };
    if (mState == BUTTON_STATE_MOUSE_DOWN)
    {
        SDL_SetRenderDrawColor(mRenderer, 0x55, 0x55, 0x55, 0xFF);
    }
    else
    {
        SDL_SetRenderDrawColor(mRenderer, 0xAA, 0xAA, 0xAA, 0xFF);
    }
    
    SDL_RenderFillRect(mRenderer, &Border);
    mButtonSprite.render(mPosition.x, mPosition.y, mWidth, mHeight);
}