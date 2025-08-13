#ifndef CAELISENGINE_H
#define CAELISENGINE_H

constexpr auto ENGINE_VERSION_STRING = "0.2.0";

/*
Tobi Console Game Engine

Copyright (c) Tobias Bersia

All rights reserved.
*/

//#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "GameStates/GameState.h"

class CaelisEngine
{
public:

    CaelisEngine()
    {
        m_nScreenWidth = 640;
        m_nScreenHeight = 480;

        m_window = NULL;
        m_renderer = NULL;

        m_font = NULL;

        m_bQuit = false;

        m_currentGameState = NULL;
        keyboardState = SDL_GetKeyboardState(NULL);

        m_nTickRate = 20;
        m_nTickDuration = 1000 / m_nTickRate; // In milliseconds
    }

    int createWindow(std::string sWindowTitle)
    {

        // Initialize SDL
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            printf("SDL Could not initialize! SDL_Error: %s\n", SDL_GetError());
            return 1;
        }
        else
        {

            //Create window
            SDL_WindowFlags flags = SDL_WINDOW_OPENGL;
            flags = 0;
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
                    if (!TTF_Init())
                    {
                        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError());
                        m_font = TTF_OpenFont("res/fonts/PixeloidSans-mLxMm.ttf", 50);
                        return 4;
                    }

                    return 0;
                }
            }

        }
    }

    void handleEvents()
    {
        m_currentGameState->handleEvents(&m_eventHandler, this);
        m_currentGameState->handleGUI(this);
    }

    void setGameState(GameState* gameState)
    {
        m_currentGameState = gameState;
        m_currentGameState->init(this);
    }

    void changeGameState(GameState* gameState)
    {
        m_currentGameState->cleanup();
        m_currentGameState = gameState;
        m_currentGameState->init(this);
    }

    void setScreenResolution(int nScreenWidth, int nScreenHeight)
    {
        m_nScreenWidth = nScreenWidth;
        m_nScreenHeight = nScreenHeight;
        SDL_SetWindowSize(m_window, m_nScreenWidth, m_nScreenHeight);
    }

    SDL_Point getScreenResolution() const
    {
        return {m_nScreenWidth, m_nScreenHeight};
    }

    SDL_Renderer* getRenderer() const
    {
        return m_renderer;
    }

    void setTickRate(int nTickRate)
    {
        m_nTickRate = nTickRate;
        m_nTickDuration = 1000 / m_nTickRate;
    }

    void changeTickRateBy(int nTickRate)
    {
        if( (m_nTickRate + nTickRate) < 0) m_nTickRate = 1;
        else m_nTickRate +=  nTickRate;
        m_nTickDuration = 1000 / m_nTickRate;
    }

    void quit()
    {
        m_bQuit = true;
    }


    int start()
    {
        int result = createWindow("Test");
        std::uint64_t nLastUpdateTime = 0;
        std::uint64_t nCurrentTime = 0;

        if (result != 0)
        {
            return result;
        }

        while (!m_bQuit)
        {
            nCurrentTime = SDL_GetTicks();
            if( (nLastUpdateTime + m_nTickDuration) < nCurrentTime){
                nLastUpdateTime = m_currentGameState->update();
            }
            handleEvents();
            m_currentGameState->render(m_window, m_renderer);
        }

        //Destroy window
        SDL_DestroyWindow(m_window);

        //Quit SDL subsystems
        SDL_Quit();

        return 0;
    }

    void fillBackground()
    {
        //Get window surface
        //m_screenSurface = SDL_GetWindowSurface(m_window);

        //Fill the surface white
        //SDL_FillSurfaceRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0xFF, 0xFF, 0xFF));

        //Update the surface
        //SDL_UpdateWindowSurface(m_window);
    }

private:

    bool m_bQuit;

    SDL_Event m_eventHandler;

    int m_nScreenWidth;
    int m_nScreenHeight;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    TTF_Font* m_font;

protected:

    GameState* m_currentGameState;
    int m_nTickRate;
    int m_nTickDuration;
public:

    const bool* keyboardState;
};


#endif
