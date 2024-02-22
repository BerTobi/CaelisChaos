#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <string>

//Texture wrapper class
class LTexture
{
public:

	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;
	TTF_Font* gFont;

	//Initializes variables
	LTexture();

	//Initializes variables
	LTexture(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font = NULL);

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	#endif

	//Loads image into pixel buffer
	bool loadPixelsFromFile(std::string path);

	//Creates image from preloaded pixels
	bool loadFromPixels();

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, int width, int height, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Pixel accessors
	Uint32* getPixels32();
	Uint32 getPitch32();
	Uint32 mapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
	//The actual hardware texture
	

	SDL_Window* mWindow;

	//Surface pixels
	SDL_Surface* mSurfacePixels;

	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif