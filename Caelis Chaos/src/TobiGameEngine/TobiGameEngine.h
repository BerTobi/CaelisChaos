#ifndef TOBIGAMEENGINE_H
#define TOBIGAMEENGINE_H

/*
Tobi Console Game Engine

Version 0.6.0

Provides basic functionalities to create a game in SDL2.
*/

#include <iostream>
#include <fstream>
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
#include "GUI/Menu.h"
#include "GUI/ListUI.h"

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
#define initializing 5
#define optionMenu 6
#define usernameInput 7

class TobiGameEngine
{
public:
	TobiGameEngine()
	{
		m_nScreenWidth = 800;
		m_nScreenHeight = 600;

		m_fTickDuration = 0.05;
		m_fTimeSinceLastTick = 0;
		m_nGameState = initializing;

		m_Window = NULL;
		m_Renderer = NULL;
		m_Font = NULL;

		avgFPS = 0;

		//Deprecated 

		wConsoleHnd = GetStdHandle(STD_OUTPUT_HANDLE);
		rConsoleHnd = GetStdHandle(STD_INPUT_HANDLE);

		m_sConsoleTitle = L"Tobi Game Engine";
	}

	bool createWindow(std::string sWindowTitle)
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

			SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_PING, "1");
			SDL_SetHint(SDL_HINT_VIDEO_X11_FORCE_EGL, "1");
			SetProcessDPIAware();

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
		if (bFullscreen)
		{
			SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			SDL_GetWindowSize(m_Window, &m_nScreenWidth, &m_nScreenHeight);
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

	//SDL_Texture* loadTexture(std::string path)
	//{
	//	//The final texture
	//	SDL_Texture* newTexture = NULL;
	//
	//	//Load image at specified path
	//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	//	if (loadedSurface == NULL)
	//	{
	//		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	//	}
	//	else
	//	{
	//		//Create texture from surface pixels
	//		newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
	//		if (newTexture == NULL)
	//		{
	//			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	//		}
	//
	//		//Get rid of old loaded surface
	//		SDL_FreeSurface(loadedSurface);
	//	}
	//
	//	return newTexture;
	//}

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
	
	virtual void CreateGUI()
	{

	}

	virtual void UpdateMenu()
	{

	}

	//GUI functions

	virtual bool GUIInput()
	{
		for (int i = 0; i < Layers; i++)
		{

			if (!Menus.empty())
			{
				for (auto menu : Menus)
				{
					if (menu.second->isEnabled() && menu.second->mLayer == i)
					{
						if (menu.second->handleEvent(&m_Event))
						{
							return true;
						}
					}
				}
			}

			if (!Buttons.empty())
			{
				for (auto button : Buttons)
				{
					if (button.second->mLayer == i)
						button.second->handleEvent(&m_Event);
					if (button.second->bPressed)
					{
						return true;
					}
				}
			}

			if (!TextBoxes.empty())
			{
				for (auto textBox : TextBoxes)
				{
					if (textBox.second->isEnabled() && textBox.second->mLayer == i)
					{
						textBox.second->handleEvent(&m_Event);
					}
				}
			}

		}

		return false;
	}

	virtual void GUIRender()
	{
		for (int i = Layers; i >= 0; i--)
		{
			if (!TextBoxes.empty())
			{
				for (auto textBox : TextBoxes)
				{
					if (textBox.second->isEnabled() && textBox.second->mLayer == i)
					{
						textBox.second->render();
					}
				}
			}

			if (!Buttons.empty())
			{
				for (auto button : Buttons)
				{
					if (button.second->mLayer == i)
						button.second->render();
				}
			}

			if (!Menus.empty())
			{
				for (auto menu : Menus)
				{
					if (menu.second->isEnabled() && menu.second->mLayer == i)
					{
						menu.second->render();
					}
				}
			}

			if (!Lists.empty())
			{
				for (auto list : Lists)
				{
					if (list.second->isEnabled() && list.second->mLayer == i)
					{
						list.second->render();
					}
				}
			}
		}

		

	}

	virtual void DestroyGUI()
	{
		Buttons.clear();
		TextBoxes.clear();
		Lists.clear();
		
		if (!Menus.empty())
		{
			for (auto menu : Menus)
			{
				if (menu.second->isEnabled())
				{
					menu.second->enable(false);
				}
			}
		}
	}

	virtual void LoadConfiguration()
	{
		std::fstream Settings;
		Settings.open("settings.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		std::string TextBuffer;

		while (getline(Settings, TextBuffer)) {

			if (TextBuffer.substr(0, 9) == "Language=") mLanguage = TextBuffer.substr(9);
			if (TextBuffer.substr(0, 11) == "Fullscreen=")
			{
				if (TextBuffer.substr(11, 4) == "True") bFullscreen = true;				
				else bFullscreen = false;

			}
			if (bFullscreen == false && TextBuffer.substr(0, 11) == "Resolution=")
			{
				if (TextBuffer.substr(9) == "2160") 
				{
					m_nScreenWidth = 3840;
					m_nScreenHeight = 2160;
				}
				else if (TextBuffer.substr(9) == "1440")
				{
					m_nScreenWidth = 2560;
					m_nScreenHeight = 1440;
				}
				else if (TextBuffer.substr(9) == "1080")
				{
					m_nScreenWidth = 1920;
					m_nScreenHeight = 1080;
				}
				else if (TextBuffer.substr(9) == "900")
				{
					m_nScreenWidth = 1600;
					m_nScreenHeight = 900;
				}
				else if (TextBuffer.substr(9) == "720")
				{
					m_nScreenWidth = 1280;
					m_nScreenHeight = 720;
				}

			}
		}

		Settings.close();
	}

	virtual void SetConfiguration()
	{
		std::fstream Settings;
		Settings.open("settings.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
		Settings << "Language=" + mLanguage << std::endl;
		if (bFullscreen) Settings << "Fullscreen=True" << std::endl;
		else Settings << "Fullscreen=False" << std::endl;
		Settings << "Resolution=" + std::to_string(m_nScreenHeight) << std::endl;
		Settings.close();
	}

	//Creates a Console
	int createConsole(std::wstring title, int width, int height, short nFontWidth = 16, short nFontHeight = 16)
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
			throw new std::exception("Couldn't set font");

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
			throw new std::exception("Unable to retrieve largest possible window coordinates");

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
						if (sprite.sprite[sX + (sY)*sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY == sprite.nSize && sX == 0)
					{
						if (sprite.sprite[sX + (sY - 1) * sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
					else if (sY == 0 && sX == sprite.nSize)
					{
						if (sprite.sprite[sX - 1 + (sY)*sprite.nSize] != ' ') newSprite.sprite.push_back(0x2588);
						else newSprite.sprite.push_back(' ');
					}
				}
		}


		newSprite.nSize = newSize;

		return newSprite;
	}

private:

	void GameThread()
	{
		while (!bClose)
		{
			LoadConfiguration();
			CreateGUI();
			while ((m_nGameState == startMenu || m_nGameState == multiplayerMenu || m_nGameState == IPscreen || m_nGameState == optionMenu || m_nGameState == usernameInput) && !bClose)
			{
				UpdateMenu();
			}

			if (bServer) initializeServer();
			else if (bMultiplayer) initializeClient();

			while (m_nGameState == matchLobby && !bClose)
			{
				if (bServer) Server();
				else Client();
				UpdateMenu();
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

				auto tp1 = std::chrono::system_clock::now();
				auto tp2 = std::chrono::system_clock::now();

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
					
				}

				
			}

			
		}
		//SDL Close
		close();
	}

protected:

	bool bMultiplayer;
	bool bServer;
	bool bClose;
	bool bFullscreen = false;

	std::string mLanguage = "English";

	int m_nScreenWidth;
	int m_nScreenHeight;
	float m_fTickDuration;
	float m_fTimeSinceLastTick;

	int countedFrames;
	float avgFPS;

	SDL_Window* m_Window;
	SDL_Surface* m_ScreenSurface;
	SDL_Renderer* m_Renderer;
	TTF_Font* m_Font;
	//map<string, SDL_Texture*> m_Textures[4];
	std::unordered_map<std::string, LTexture> m_Textures[4];
	LTimer fpsTimer;

	SDL_Event m_Event;
	
	static std::atomic<bool> bAtomActive;

	std::unordered_map<int, Entity*> entityList;

	int m_nGameState;
	bool pause;

	//GUI

	int Layers = 2;

	std::unordered_map<std::string, Button*> Buttons;
	std::unordered_map<std::string, TextBox*> TextBoxes;
	std::unordered_map<std::string, Menu*> Menus;
	std::unordered_map<std::string, ListUI*> Lists;

	//Deprecated
	std::wstring m_sConsoleTitle;
	HANDLE wConsoleHnd;
	HANDLE rConsoleHnd;
	CHAR_INFO* bfScreen;
	SMALL_RECT srWindowSize;

};

std::atomic<bool> TobiGameEngine::bAtomActive(false);

#endif