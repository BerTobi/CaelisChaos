/*
Tobi Console Game Engine

Version 0.5

Provides basic functionalities to create a game in SDL2.
*/

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <atomic>
#include <stdlib.h>
#include <Tchar.h>
#include <string.h>
#include <sstream>
#include <exception>
#include <vector>
#include <unordered_map>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "LTexture.h"
#include "LTimer.h"
#include "GUI/Button.h"
#include "GUI/TextBox.h"

#include "RTS-utilities/Sprite.h"
#include "RTS-utilities/Entity.h"
#include "RTS-utilities/Unit.h"
#include "RTS-utilities/Building.h"
#include "RTS-utilities/Projectile.h"

#define startMenu 0
#define inMatch 1
#define matchLobby 2
#define multiplayerMenu 3
#define IPscreen 4

using namespace std;

class TobiGameEngine
{
public:
	TobiGameEngine()
	{
		m_nScreenWidth = 800;
		m_nScreenHeight = 600;

		wConsoleHnd = GetStdHandle(STD_OUTPUT_HANDLE);
		rConsoleHnd = GetStdHandle(STD_INPUT_HANDLE);

		m_sConsoleTitle = L"Tobi Game Engine";

		m_fTickDuration = 0.05;
		m_fTimeSinceLastTick = 0;
		m_nGameState = 0;

		m_Window = NULL;
		m_Renderer = NULL;
		m_Font = NULL;

		avgFPS = 0;

	}

	bool createWindow(string sWindowTitle)
	{
		//Initialization flag
		bool bSuccess = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initalize! SDL Error: %s\n", SDL_GetError());
			bSuccess = false;
		}
		else
		{
			//Set texture filtering to nearest
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
			{
				printf("Warning: Nearest texture filtering not enabled!");
			}

			//Create window
			m_Window = SDL_CreateWindow(sWindowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_nScreenWidth, m_nScreenHeight, SDL_WINDOW_SHOWN);
			if (m_Window == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				bSuccess = false;
			}
			else
			{
				//Create renderer for window
				m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
				if (m_Renderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					bSuccess = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_Color textColor = { 0, 0, 0, 255 };

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						bSuccess = false;
					}

					//Initialize SDL_ttf
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						m_Font = TTF_OpenFont("res/fonts/PixeloidSans-mLxMm.ttf", 50);
						bSuccess = false;
					}
				}
			}
		}
		return bSuccess;
	}

	void close()
	{
		for (int i = 0; i < 4; i++)
		{
			for (auto texture : m_Textures[i])
			{
				texture.second.free();
			}
		}
		
		//Free global font
		TTF_CloseFont(m_Font);
		m_Font = NULL;

		//Destroy window    
		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);
		m_ScreenSurface = NULL;
		m_Window = NULL;
		m_Renderer = NULL;

		//Quit SDL subsystems
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();

		bAtomActive = false;
		bClose = true;
	}

	SDL_Texture* loadTexture(std::string path)
	{
		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
	}

	//Creates a Console
	int createConsole(wstring title, int width, int height, short nFontWidth = 16, short nFontHeight = 16)
	{
		CONSOLE_FONT_INFOEX fontInfo;

		fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		fontInfo.nFont = 0;
		fontInfo.dwFontSize.X = nFontWidth;
		fontInfo.dwFontSize.Y = nFontHeight;
		fontInfo.FontFamily = FF_DONTCARE;
		fontInfo.FontWeight = FW_NORMAL;
		wcscpy_s(fontInfo.FaceName, L"Consolas");

		if (!SetCurrentConsoleFontEx(wConsoleHnd, false, &fontInfo))
			throw new exception("Couldn't set font");

		m_sConsoleTitle = title;
		const wchar_t* cConsoleTitle = m_sConsoleTitle.c_str();

		SetConsoleTitle(cConsoleTitle);

		m_nScreenWidth = width;
		m_nScreenHeight = height;

		SMALL_RECT srMinimalWindowSize = { 0, 0, 1, 1 };
		
		if (!SetConsoleWindowInfo(wConsoleHnd, TRUE, &srMinimalWindowSize)) 
			return 1;

		COORD cLargestWindow = GetLargestConsoleWindowSize(wConsoleHnd);

		if (cLargestWindow.X == 0 && cLargestWindow.Y == 0)
			throw new exception("Unable to retrieve largest possible window coordinates");

		m_nScreenWidth = min(cLargestWindow.X, m_nScreenWidth);
		m_nScreenHeight = min(cLargestWindow.Y, m_nScreenHeight);

		COORD cBufferSize = { (short)m_nScreenWidth, (short)m_nScreenHeight };
		

		if (!SetConsoleScreenBufferSize(wConsoleHnd, cBufferSize)) 
			return 2;

		srWindowSize = { 0, 0, (short)(m_nScreenWidth - 1), (short)(m_nScreenHeight - 1) };

		if (!SetConsoleWindowInfo(wConsoleHnd, TRUE, &srWindowSize))
		{
			DWORD error = GetLastError();
			return error;
		}
		
		bfScreen = new CHAR_INFO[m_nScreenWidth * m_nScreenHeight];
		
		SetConsoleOutputCP(65001);

		return 0;
	}

	//Write an screen buffer to screen from coordinates {0, 0}
	void writeToScreen(CHAR_INFO* screen, int screenSize)
	{
		DWORD dwBytesWritten = 0;
		WriteConsoleOutputW(wConsoleHnd, screen, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &srWindowSize);
	}

	//Sets the amount of game updates per second
	void setGameTick(float fTicksPerSecond)
	{
		m_fTickDuration = 1 / fTicksPerSecond;
	}

	void setCursorVisibility(bool visible)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = visible;
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	void drawSprite(int x, int y, Sprite sprite, int color)
	{
		for (int sX = 0; sX < sprite.nSize; sX++)
			for (int sY = 0; sY < sprite.nSize; sY++)
			{
				int currentPixel = x - (sprite.nSize / 2) + sX + m_nScreenWidth * (y - (sprite.nSize / 2) + sY);
				if (currentPixel >= 0 && currentPixel < m_nScreenWidth * m_nScreenHeight && sprite.sprite[sX + sY * sprite.nSize] != ' ')
				{
					bfScreen[x - (sprite.nSize / 2) + sX + m_nScreenWidth * (y - (sprite.nSize / 2) + sY)].Char.UnicodeChar = sprite.sprite[sX + sY * sprite.nSize];
					bfScreen[x - (sprite.nSize / 2) + sX + m_nScreenWidth * (y - (sprite.nSize / 2) + sY)].Attributes = color;
				}
			}
	}

	Sprite scaleSprite(Sprite sprite, int newSize)
	{
		int neighbourPixels = 0;
		Sprite newSprite;
		if (newSize == sprite.nSize) return sprite;

		else if (newSize < sprite.nSize)
		{
			if (newSize != sprite.nSize - 1)
			{
				sprite = scaleSprite(sprite, newSize + 1);
				sprite.nSize = newSize + 1;
			}
			for (int sY = 0; sY < newSize; sY++)
				for (int sX = 0; sX < newSize; sX++)
				{
					neighbourPixels += (sprite.sprite[sX + sY * sprite.nSize] != ' ') ? 1 : 0;
					neighbourPixels += (sprite.sprite[sX + 1 + sY * sprite.nSize] != ' ') ? 1 : 0;
					neighbourPixels += (sprite.sprite[sX + 1 + (sY + 1) * sprite.nSize] != ' ') ? 1 : 0;
					neighbourPixels += (sprite.sprite[sX + (sY + 1) * sprite.nSize] != ' ') ? 1 : 0;
					if (neighbourPixels > 2) newSprite.sprite.push_back(0x2588);
					else newSprite.sprite.push_back(' ');
					neighbourPixels = 0;
				}
		}

		else if (newSize > sprite.nSize)
		{
			if (newSize != sprite.nSize + 1)
			{
				sprite = scaleSprite(sprite, newSize - 1);
				sprite.nSize = newSize - 1;
			}
			for (int sY = 0; sY < newSize; sY++)
				for (int sX = 0; sX < newSize; sX++)
				{
					if (sY < sprite.nSize && sY > 0 && sX < sprite.nSize && sX > 0)
					{
						if (sprite.sprite[sX + sY * sprite.nSize] != ' ' || sprite.sprite[sX - 1 + sY * sprite.nSize] != ' ' || sprite.sprite[sX - 1 + (sY - 1) * sprite.nSize] != ' ' || sprite.sprite[sX + (sY - 1) * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY < sprite.nSize && sY > 0 && sX == 0)
					{
						if (sprite.sprite[sX + sY * sprite.nSize] != ' ' || sprite.sprite[sX + (sY - 1) * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY < sprite.nSize && sY > 0 && sX == sprite.nSize)
					{
						if (sprite.sprite[sX - 1 + sY * sprite.nSize] != ' ' || sprite.sprite[sX - 1 + (sY - 1) * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY == 0 && sX < sprite.nSize && sX > 0)
					{
						if (sprite.sprite[sX + sY * sprite.nSize] != ' ' || sprite.sprite[sX - 1 + sY * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY == sprite.nSize && sX < sprite.nSize && sX > 0)
					{
						if (sprite.sprite[sX + (sY - 1) * sprite.nSize] != ' ' || sprite.sprite[sX - 1 + (sY - 1) * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY == sprite.nSize && sX == sprite.nSize)
					{
						if (sprite.sprite[sX - 1 + (sY - 1) * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY == 0 && sX == 0)
					{
						if (sprite.sprite[sX + (sY) * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY == sprite.nSize && sX == 0)
					{
						if (sprite.sprite[sX + (sY - 1)*sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY == 0 && sX == sprite.nSize)
					{
						if (sprite.sprite[sX - 1 + (sY) * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
				}
		}


		newSprite.nSize = newSize;

		return newSprite;
	}

	void Start()
	{
		bAtomActive = true;
		bClose = false;
		
		std::thread t = std::thread(&TobiGameEngine::GameThread, this);

		t.join();
	}

	virtual void Settings()
	{

	}

	virtual void CreateMatch()
	{

	}

	virtual void Input()
	{

	}

	virtual void Update(float fElapsedTime)
	{

	}

	virtual void Render()
	{

	}

	virtual int Client()
	{
		return 0;
	}

	virtual int initializeClient()
	{
		return 0;
	}

	virtual void Server()
	{

	}

	virtual int initializeServer() 
	{
		return 0;
	}
	
	virtual void CreateMenu()
	{

	}

	virtual void UpdateMenu()
	{

	}

private:

	void GameThread()
	{
		while (!bClose)
		{
			CreateMenu();
			while ((m_nGameState == startMenu || m_nGameState == multiplayerMenu || m_nGameState == IPscreen) && !bClose)
			{
				UpdateMenu();
			}

			if (bServer) initializeServer();
			else if (bMultiplayer) initializeClient();

			while (m_nGameState == matchLobby && !bClose)
			{
				if (bServer) Server();
				else Client();
			}

			if (bServer)
			{
				while (m_nGameState == inMatch && !bClose)
				{ 
					Server();
				}
			}

			else
			{
				Settings();
				CreateMatch();

				auto tp1 = chrono::system_clock::now();
				auto tp2 = chrono::system_clock::now();

				while (bAtomActive && m_nGameState == inMatch && !bClose)
				{
					tp2 = std::chrono::system_clock::now();
					std::chrono::duration<float> elapsedTime = tp2 - tp1;
					tp1 = tp2;
					float fElapsedTime = elapsedTime.count();

					avgFPS = 1.0f / fElapsedTime;

					m_fTimeSinceLastTick += fElapsedTime;
					if (m_fTimeSinceLastTick >= m_fTickDuration)
					{
						
						Update(fElapsedTime);
						if (bMultiplayer)
						{
							Client();
						}
						m_fTimeSinceLastTick -= m_fTickDuration;
					}

					Render();
					Input();
					

					//wchar_t s[256];
					//wstring sConsoleTitle2 = m_sConsoleTitle;
					//sConsoleTitle2.append(L" - FPS %3.2f");
					//const wchar_t* cConsoleTitle = sConsoleTitle2.c_str();
					//swprintf_s(s, 256, cConsoleTitle, 1.0f / fElapsedTime);
					////SetConsoleTitle(s);
					//writeToScreen(bfScreen, m_nScreenWidth * m_nScreenHeight);
				}

				
			}
			//SDL Close
			close();
		}
		
	}

protected:

	bool bMultiplayer;
	bool bServer;
	bool bClose;

	int m_nScreenWidth;
	int m_nScreenHeight;
	float m_fTickDuration;
	float m_fTimeSinceLastTick;
	wstring m_sConsoleTitle;

	int countedFrames;
	float avgFPS;

	SDL_Window* m_Window;
	SDL_Surface* m_ScreenSurface;
	SDL_Renderer* m_Renderer;
	TTF_Font* m_Font;
	//map<string, SDL_Texture*> m_Textures[4];
	unordered_map<string, LTexture> m_Textures[4];
	LTimer fpsTimer;

	SDL_Event m_Event;

	HANDLE wConsoleHnd;
	HANDLE rConsoleHnd;
	CHAR_INFO *bfScreen;
	SMALL_RECT srWindowSize;
	
	static std::atomic<bool> bAtomActive;

	unordered_map<int, Entity*> entityList;

	int m_nGameState;
	bool pause;

};

float cDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

std::atomic<bool> TobiGameEngine::bAtomActive(false);