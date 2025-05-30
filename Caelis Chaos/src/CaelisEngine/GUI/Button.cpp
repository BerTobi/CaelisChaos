#include "Button.h"

Button::Button(SDL_Point position, int nWidth, int nHeight, SDL_Color backgroundColor)
{
    m_position = position;
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_backgroundColor = backgroundColor;
}

void Button::draw(SDL_Renderer* renderer)
{
    SDL_FRect Border = { m_position.x, m_position.y, m_nWidth, m_nHeight };

    SDL_SetRenderDrawColor(renderer, COLOR_CHANNELS(m_backgroundColor));

    SDL_RenderFillRect(renderer, &Border);
}