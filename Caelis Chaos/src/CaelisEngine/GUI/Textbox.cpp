#include "Textbox.h"

Textbox::Textbox(SDL_FPoint origin, SDL_FPoint extent, SDL_Point windowResolution, SDL_Color backgroundColor)
{
    m_position = translateRelativeToAbsolute(origin, windowResolution);
    m_nWidth = translateRelativeToAbsolute(extent, windowResolution).x;
    m_nHeight = translateRelativeToAbsolute(extent, windowResolution).y;
    m_backgroundColor = backgroundColor;
    m_bVisible = true;
}

void Textbox::draw(SDL_Renderer* renderer)
{
    if (m_bVisible)
    {
        SDL_FRect Border = { static_cast<float>(m_position.x), static_cast<float>(m_position.y), static_cast<float>(m_nWidth), static_cast<float>(m_nHeight) };

        SDL_SetRenderDrawColor(renderer, COLOR_CHANNELS(m_backgroundColor));

        SDL_RenderFillRect(renderer, &Border);
        m_icon.render(renderer, static_cast<float>(m_position.x), static_cast<float>(m_position.y), nullptr, static_cast<float>(m_nWidth), static_cast<float>(m_nHeight));
    }  
}

void Textbox::handleEvents(SDL_Event* event)
{
   
}

void Textbox::loadIconFromText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor)
{
    m_icon.loadFromRenderedText(renderer, font, textureText, textColor);
}
