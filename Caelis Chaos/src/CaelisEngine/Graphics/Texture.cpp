#include "Texture.h"

//LTexture Implementation
Texture::Texture() :
    //Initialize texture variables
    m_Texture(nullptr),
    m_nWidth(0),
    m_nHeight(0)
{

}

Texture::~Texture()
{
    //Clean up texture
    destroy();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    //Clean up texture if it already exists
    destroy();

    //Load surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        //Color key image
        if (SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0xAA, 0xAA, 0xAA)) == false)
        {
            SDL_Log("Unable to color key! SDL error: %s", SDL_GetError());
        }
        else
        {
            //Create texture from surface
			m_Texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            SDL_SetTextureScaleMode(m_Texture, SDL_SCALEMODE_NEAREST);
            if (m_Texture == nullptr)
            {
                SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
            }
            else
            {
                //Get image dimensions
                m_nWidth = loadedSurface->w;
                m_nHeight = loadedSurface->h;
            }
        }

        //Clean up loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    //Return success if texture loaded
    return m_Texture != nullptr;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor)
{
    //Clean up existing texture
    destroy();

    //Load text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), 0, textColor, 0);
    if (textSurface == nullptr)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create texture from surface
		m_Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (m_Texture == nullptr)
        {
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            m_nWidth = textSurface->w;
            m_nHeight = textSurface->h;
        }

        //Free temp surface
        SDL_DestroySurface(textSurface);
    }

    //Return success if texture loaded
    return m_Texture != nullptr;
}
#endif

void Texture::destroy()
{
    //Clean up texture
    SDL_DestroyTexture(m_Texture);
    m_Texture = nullptr;
    m_nWidth = 0;
    m_nHeight = 0;
}

void Texture::render(SDL_Renderer* renderer, float x, float y, SDL_FRect* clip, float width, float height, double degrees, SDL_FPoint* center, SDL_FlipMode flipMode)
{
    //Set texture position
    SDL_FRect dstRect = SDLFRect(x, y, static_cast<float>(m_nWidth), static_cast<float>(m_nHeight));

    //Default to clip dimensions if clip is given
    if (clip != nullptr)
    {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    //Resize if new dimensions are given
    if (width > 0)
    {
        dstRect.w = width;
    }
    if (height > 0)
    {
        dstRect.h = height;
    }

    //Render texture
    SDL_RenderTextureRotated(renderer, m_Texture, clip, &dstRect, degrees, center, flipMode);
}

int Texture::getWidth()
{
    return m_nWidth;
}

int Texture::getHeight()
{
    return m_nHeight;
}

bool Texture::isLoaded()
{
    return m_Texture != nullptr;
}

void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(m_Texture, r, g, b);
}

void Texture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void Texture::setBlending(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(m_Texture, blendMode);
}