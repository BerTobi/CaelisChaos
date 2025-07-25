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

    if (m_nCurrentState == HOVERED) 
    {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    }
    else if (m_nCurrentState == PRESSED)
    {
        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    }

    SDL_RenderFillRect(renderer, &Border);
}

void Button::handleEvents(SDL_Event* event)
{
    if (m_nCurrentState != DISABLED)
    {
        //If mouse event happened
        //Get mouse position
        float cursorX, cursorY;
        SDL_GetMouseState(&cursorX, &cursorY);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if ( cursorX < m_position.x)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (cursorX > m_position.x + m_nWidth)
        {
            inside = false;
        }
        //Mouse above the button
        else if (cursorY < m_position.y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (cursorY > m_position.y + m_nHeight)
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
            switch (event->type)
            {
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                m_nCurrentState = PRESSED;
                break;
            }

        }
    }
}

bool Button::isPressed() const
{
    return m_nCurrentState == PRESSED;
}