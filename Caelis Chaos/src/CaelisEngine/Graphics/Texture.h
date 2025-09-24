#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "Utilities/Util.h"

/* Class Prototypes */
class Texture
{
public:

    //Initializes texture variables
    Texture();

    //Cleans up texture variables
    ~Texture();

    //Loads texture from disk
    bool loadFromFile(std::string path, SDL_Renderer* renderer);

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates texture from text
    bool loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor);
#endif

    //Cleans up texture
    void destroy();

    //Sets color modulation
    void setColor(Uint8 r, Uint8 g, Uint8 b);

    //Sets opacity
    void setAlpha(Uint8 alpha);

    //Sets blend mode
    void setBlending(SDL_BlendMode blendMode);

    //Draws texture
    void render(SDL_Renderer* renderer, float x, float y, SDL_FRect* clip = nullptr, float width = -1.f, float height = -1.f, double degrees = 0.0, SDL_FPoint* center = nullptr, SDL_FlipMode flipMode = SDL_FLIP_NONE);

    //Gets texture attributes
    int getWidth();
    int getHeight();
    bool isLoaded();

private:
    //Contains texture data
    SDL_Texture* m_Texture;

    //Texture dimensions
    int m_nWidth;
    int m_nHeight;

	//Remove copy constructor
    //Texture(const Texture&);

    //Remove copy assignment
    Texture& operator=(const Texture&);

    //Remove move constructor
    //Texture(Texture&&);

    //Remove move assignment
    Texture& operator=(Texture&&);
};

#endif