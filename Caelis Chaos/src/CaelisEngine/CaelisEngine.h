#ifndef CAELISENGINE_H
#define CAELISENGINE_H

#define VERSION_STRING "0.1.0"

/*
Tobi Console Game Engine

Copyright (c) Tobias Bersia

All rights reserved.
*/

#include <SDL.h>
#include <stdio.h>
#include <string>

class CaelisEngine
{
public:
	CaelisEngine()
	{
		m_nScreenWidth = 640;
		m_nScreenHeight = 480;

		m_window = NULL;
		m_screenSurface = NULL;
	}

	void createWindow(std::string sWindowTitle)
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL Could not initialize! SDL_Error: %s\n", SDL_GetError());
		else
		{
			//Create window
			m_window = SDL_CreateWindow(sWindowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_nScreenWidth, m_nScreenHeight, SDL_WINDOW_SHOWN);

			if (m_window == NULL) printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

			else
			{
				//Get window surface
				m_screenSurface = SDL_GetWindowSurface(m_window);

				//Fill the surface white
				SDL_FillRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0xFF, 0xFF, 0xFF));

				//Update the surface
				SDL_UpdateWindowSurface(m_window);

				//Hack to get window to stay up
				SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
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

	SDL_Window* m_window = NULL;
	SDL_Surface* m_screenSurface = NULL;

};


#endif#pragma once
