#ifndef CAELISENGINE_H
#define CAELISENGINE_H

#define VERSION_STRING "0.1.0"

/*
Tobi Console Game Engine

Copyright (c) Tobias Bersia

All rights reserved.
*/

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <Windows.h>

class CaelisEngine
{
public:
	CaelisEngine()
	{
		m_nScreenWidth = 640;
		m_nScreenHeight = 480;

		m_window = NULL;
		m_screenSurface = NULL;
		m_renderer = NULL;

		m_font = NULL;
	}

	int createWindow(std::string sWindowTitle)
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		{
			printf("SDL Could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 1;
		}
		else
		{

			//Create window
			SDL_WindowFlags flags = SDL_WINDOW_OPENGL;
			m_window = SDL_CreateWindow(sWindowTitle.c_str(), m_nScreenWidth, m_nScreenHeight, flags);

			if (m_window == NULL) 
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				return 2;
			}

			else
			{
				//Create renderer for window
				m_renderer = SDL_CreateRenderer(m_window, NULL);

				SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
				if (m_renderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					return 3;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(m_renderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_Color textColor = { 0, 0, 0, 255 };

					//Initialize SDL_ttf
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError());
						m_font = TTF_OpenFont("res/fonts/PixeloidSans-mLxMm.ttf", 50);
						return 4;
					}
				}
			}

		}
	}

	int start()
	{
		createWindow("Test");

		//Destroy window
		SDL_DestroyWindow(m_window);

		//Quit SDL subsystems
		SDL_Quit();

		return 0;
	}

private:

	bool bSuccess;

	int m_nScreenWidth;
	int m_nScreenHeight;

	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;

	TTF_Font* m_font;

};


#endif#pragma once
