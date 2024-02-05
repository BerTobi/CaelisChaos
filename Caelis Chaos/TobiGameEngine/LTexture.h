

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <string>

//Texture wrapper class
class LTexture
{
public:

	//Initializes variables
	LTexture();

	//Initializes variables
	LTexture(SDL_Renderer* renderer);

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;

	//Image dimensions
	int mWidth;
	int mHeight;
};

