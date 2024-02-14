#include "LTexture.h"

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mSurfacePixels = NULL;
	mWindow = NULL;
	mWidth = 0;
	mHeight = 0;
	mRenderer = NULL;
	gFont = NULL;
}

LTexture::LTexture(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
	//Initialize
	mTexture = NULL;
	mSurfacePixels = NULL;
	mWidth = 0;
	mHeight = 0;
	mRenderer = renderer;
	mWindow = window;
	gFont = font;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Load pixels
	if (!loadPixelsFromFile(path))
	{
		printf("Failed to load pixels for %s!\n", path.c_str());
	}
	else
	{
		//Load texture from pixels
		if (!loadFromPixels())
		{
			printf("Failed to texture from pixels from %s!\n", path.c_str());
		}
	}

	//Return success
	return mTexture != NULL;
}

bool LTexture::loadPixelsFromFile(std::string path)
{
	//Free preexisting assets
	free();

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		mSurfacePixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(mWindow), 0);
		if (mSurfacePixels == NULL)
		{
			printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = mSurfacePixels->w;
			mHeight = mSurfacePixels->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return mSurfacePixels != NULL;
}

bool LTexture::loadFromPixels()
{
	//Only load if pixels exist
	if (mSurfacePixels == NULL)
	{
		printf("No pixels loaded!");
	}
	else
	{
		//Color key image
		SDL_SetColorKey(mSurfacePixels, SDL_TRUE, SDL_MapRGB(mSurfacePixels->format, 0xAA, 0xAA, 0xAA));

		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurfacePixels);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from loaded pixels! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = mSurfacePixels->w;
			mHeight = mSurfacePixels->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(mSurfacePixels);
		mSurfacePixels = NULL;
	}

	//Return success
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	//Free surface if it exists
	if (mSurfacePixels != NULL)
	{
		SDL_FreeSurface(mSurfacePixels);
		mSurfacePixels = NULL;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, int width, int height, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	//if (clip != NULL)
	//{
	//	renderQuad2.w = clip->w;
	//	renderQuad2.h = clip->h;
	//}

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Uint32* LTexture::getPixels32()
{
	Uint32* pixels = NULL;

	if (mSurfacePixels != NULL)
	{
		pixels = static_cast<Uint32*>(mSurfacePixels->pixels);
	}

	return pixels;
}

Uint32 LTexture::getPitch32()
{
	Uint32 pitch = 0;

	if (mSurfacePixels != NULL)
	{
		pitch = mSurfacePixels->pitch / 4;
	}

	return pitch;
}


Uint32 LTexture::mapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Uint32 pixel = 0;

	if (mSurfacePixels != NULL)
	{
		pixel = SDL_MapRGBA(mSurfacePixels->format, r, g, b, a);
	}

	return pixel;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif