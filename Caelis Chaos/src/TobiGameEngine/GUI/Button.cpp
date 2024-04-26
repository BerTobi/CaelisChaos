#include "Button.h"

Button::Button()
{
	mPosition.x = 0;
	mPosition.y = 0;
    mLayer = 0;

    mBorderThickness = 5;

    bVisible = true;
}

Button::Button(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mBorderThickness = 5;
    
    mRenderer = renderer;
    mButtonSprite = LTexture(renderer, window, font);

    bVisible = true;

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);

    mText = "Button";
    mButtonSprite.free();
    mButtonSprite.loadFromRenderedText(mText, { 0, 0, 0 });
}

void Button::free()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mButtonSprite.free();
}

void Button::setLayer(int layer)
{
    mLayer = layer;
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
    mButtonSprite.loadFromRenderedText(mText, { 0xE6, 0xE6, 0xE6 });
}

void Button::setVisibility(bool visible)
{
    bVisible = visible;
}

void Button::setBorderThickness(int thickness)
{
    mBorderThickness = thickness;
}

void Button::handleEvent(SDL_Event* e)
{
	//If mouse event happened
    //Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if (x < mPosition.x + 1)
    {
        inside = false;
    }
    //Mouse is right of the button
    else if (x > mPosition.x + mWidth - 1)
    {
        inside = false;
    }
    //Mouse above the button
    else if (y < mPosition.y + 1)
    {
        inside = false;
    }
    //Mouse below the button
    else if (y > mPosition.y + mHeight - 1)
    {
        inside = false;
    }

    //Mouse is outside button
    if (!inside)
    {
        bHovered = false;
        mState = BUTTON_STATE_MOUSE_OUT;
    }
    //Mouse is inside button
    else
    {
        bHovered = true;
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

void Button::render()
{
    if (bVisible)
    {
        SDL_Rect Border = { mPosition.x, mPosition.y, mWidth, mHeight };

        SDL_Rect Interior = { mPosition.x + mBorderThickness, mPosition.y + mBorderThickness, mWidth - mBorderThickness * 2, mHeight - mBorderThickness * 2};

        SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

        SDL_RenderFillRect(mRenderer, &Border);

        if (mState == BUTTON_STATE_MOUSE_DOWN)
        {
            SDL_SetRenderDrawColor(mRenderer, 0x1E, 0x39, 0x32, 0xFF);
        }
        else
        {
            SDL_SetRenderDrawColor(mRenderer, 0x00, 0x62, 0x41, 0xFF);
        }
        SDL_RenderFillRect(mRenderer, &Interior);

        

        mButtonSprite.render(mPosition.x + mWidth / mText.size() / 2, mPosition.y, mWidth - mWidth / mText.size(), mHeight);
    }
}
