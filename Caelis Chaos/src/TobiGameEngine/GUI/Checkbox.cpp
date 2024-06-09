#include "Checkbox.h"

Checkbox::Checkbox(bool* assigned)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mBorderThickness = 5;

    bVisible = true;
    mEnabled = true;
    bChecked = false;

    mSpritePath = "res/textures/Cross.png";
    mButtonSprite.loadFromFile(mSpritePath);

    assignedVariable = assigned;
}

Checkbox::Checkbox(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font, bool* assigned)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mBorderThickness = 5;

    mRenderer = renderer;
    mButtonSprite = LTexture(renderer, window, font);
    mTitle = LTexture(renderer, window, font);

    bVisible = true;
    mEnabled = true;
    bChecked = false;

    assignedVariable = assigned;

    if (*assignedVariable) mSpritePath = "res/textures/Tick.png";
    else mSpritePath = "res/textures/Cross.png";
    
    mButtonSprite.loadFromFile(mSpritePath);

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);

    mText = "Button";
    mTitle.free();
    mTitle.loadFromRenderedText(mText, { 0, 0, 0 });

    
}

void Checkbox::setTitle(std::string title)
{
    mText = title;

    mTitle.free();
    mTitle.loadFromRenderedText(mText, { 0x00, 0x00, 0x00 });


}

void Checkbox::handleEvent(SDL_Event* e)
{
    if (mEnabled)
    {
        //If mouse event happened
            //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < mPosition.x + mBorderThickness)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (x > mPosition.x + mWidth - mBorderThickness)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < mPosition.y + mBorderThickness)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > mPosition.y + mHeight - mBorderThickness)
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
                bChecked = !bChecked;
                if (*assignedVariable == false) *assignedVariable = true;
                else *assignedVariable = false;

                if (bChecked)
                {
                    mSpritePath = "res/textures/Tick.png";
                }
                else
                {
                    mSpritePath = "res/textures/Cross.png";
                }
                
                mButtonSprite.loadFromFile(mSpritePath);
                break;
            }
        }
    }
}

void Checkbox::render()
{
    if (bVisible && mEnabled)
    {
        SDL_Rect Border = { mPosition.x, mPosition.y, mWidth, mHeight };

        SDL_Rect Interior = { mPosition.x + mBorderThickness, mPosition.y + mBorderThickness, mWidth - mBorderThickness * 2, mHeight - mBorderThickness * 2 };

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



        if (mText.size() > 0)
            mTitle.render(mPosition.x - mWidth / 2.0f, mPosition.y - mHeight, mWidth * 2.0f, mHeight);

        mButtonSprite.render(mPosition.x + mBorderThickness, mPosition.y + mBorderThickness, mWidth - mBorderThickness * 2, mHeight - mBorderThickness * 2);

    }
}