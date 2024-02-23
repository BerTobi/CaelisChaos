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

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);
}

void Button::free()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mButtonSprite.free();
}

void Button::setPosition(float x, float y)
{
	mPosition.x = x * mScreenWidth;
	mPosition.y = y * mScreenHeight;
}

void Button::setSize(float width, float height)
{
    mWidth = width * mScreenWidth;
    mHeight = height * mScreenHeight;
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
                break;

            case SDL_MOUSEBUTTONUP:
                mState = BUTTON_STATE_MOUSE_UP;
                bPressed = true;
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
    
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    
    SDL_RenderDrawRect(mRenderer, &Border);

    mButtonSprite.render(mPosition.x + mWidth / mText.size() / 2, mPosition.y, mWidth - mWidth / mText.size(), mHeight);
}