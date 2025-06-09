#include "Button.h"

Button::Button(SDL_Point position, int nWidth, int nHeight, SDL_Color backgroundColor)
{
    m_position = position;
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_backgroundColor = backgroundColor;
    m_nCurrentState = IDLE;
}

void Button::draw(SDL_Renderer* renderer)
{
    SDL_FRect Border = { m_position.x, m_position.y, m_nWidth, m_nHeight };

    SDL_SetRenderDrawColor(renderer, COLOR_CHANNELS(m_backgroundColor));

    SDL_RenderFillRect(renderer, &Border);
}

void Button::handleEvent(SDL_Event* e)
{
    if (m_nCurrentState != DISABLED)
    {
        //If mouse event happened
        //Get mouse position
        int cursorX, cursorY;
        SDL_GetMouseState(&cursorX, &cursorY);

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
            m_nCurrentState = IDLE;
        }
        //Mouse is inside button
        else
        {
            m_nCurrentState = HOVERED;
            //Set mouse over sprite

        }
    }
}