/*
Tobi Console Game Engine

Version 0.4.1

Provides basic functionalities to create a game in the system console.
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <stdlib.h>
#include <Tchar.h>
#include <string.h>
#include <exception>
#include <vector>
#include <unordered_map>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "RTS-utilities/Sprite.h"
#include "RTS-utilities/Entity.h"
#include "RTS-utilities/Unit.h"
#include "RTS-utilities/Building.h"

#define startMenu 0

using namespace std;

class TobiGameEngine
{
public:
	TobiGameEngine()
	{
		nScreenWidth = 800;
		nScreenHeight = 600;

		wConsoleHnd = GetStdHandle(STD_OUTPUT_HANDLE);
		rConsoleHnd = GetStdHandle(STD_INPUT_HANDLE);

		sConsoleTitle = L"Tobi Game Engine";

		tickDuration = 0.05;
		timeSinceLastTick = 0;
		gameState = 0;

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

		sConsoleTitle = title;
		const wchar_t* cConsoleTitle = sConsoleTitle.c_str();

		SetConsoleTitle(cConsoleTitle);

		nScreenWidth = width;
		nScreenHeight = height;

		SMALL_RECT srMinimalWindowSize = { 0, 0, 1, 1 };
		
		if (!SetConsoleWindowInfo(wConsoleHnd, TRUE, &srMinimalWindowSize)) 
			return 1;

		COORD cLargestWindow = GetLargestConsoleWindowSize(wConsoleHnd);

		if (cLargestWindow.X == 0 && cLargestWindow.Y == 0)
			throw new exception("Unable to retrieve largest possible window coordinates");

		nScreenWidth = min(cLargestWindow.X, nScreenWidth);
		nScreenHeight = min(cLargestWindow.Y, nScreenHeight);

		COORD cBufferSize = { (short)nScreenWidth, (short)nScreenHeight };
		

		if (!SetConsoleScreenBufferSize(wConsoleHnd, cBufferSize)) 
			return 2;

		srWindowSize = { 0, 0, (short)(nScreenWidth - 1), (short)(nScreenHeight - 1) };

		if (!SetConsoleWindowInfo(wConsoleHnd, TRUE, &srWindowSize))
		{
			DWORD error = GetLastError();
			return error;
		}
		
		bfScreen = new CHAR_INFO[nScreenWidth * nScreenHeight];
		
		SetConsoleOutputCP(65001);

		return 0;
	}

	//Write an screen buffer to screen from coordinates {0, 0}
	void writeToScreen(CHAR_INFO* screen, int screenSize)
	{
		DWORD dwBytesWritten = 0;
		WriteConsoleOutputW(wConsoleHnd, screen, { (short)nScreenWidth, (short)nScreenHeight }, { 0,0 }, &srWindowSize);
	}

	//Sets the amount of game updates per second
	void setGameTick(float fTicksPerSecond)
	{
		tickDuration = 1 / fTicksPerSecond;
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
				int currentPixel = x - (sprite.nSize / 2) + sX + nScreenWidth * (y - (sprite.nSize / 2) + sY);
				if (currentPixel >= 0 && currentPixel < nScreenWidth * nScreenHeight && sprite.sprite[sX + sY * sprite.nSize] != ' ')
				{
					bfScreen[x - (sprite.nSize / 2) + sX + nScreenWidth * (y - (sprite.nSize / 2) + sY)].Char.UnicodeChar = sprite.sprite[sX + sY * sprite.nSize];
					bfScreen[x - (sprite.nSize / 2) + sX + nScreenWidth * (y - (sprite.nSize / 2) + sY)].Attributes = color;
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
		
		std::thread t = std::thread(&TobiGameEngine::GameThread, this);

		t.join();
	}

	virtual void Settings()
	{

	}

	virtual void Create()
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
	
	virtual void UpdateMenu()
	{

	}

private:

	void GameThread()
	{
		while (true)
		{
			while (gameState == 0)
			{
				UpdateMenu();
			}

			if (bServer) initializeServer();
			else if (bMultiplayer) initializeClient();

			while (gameState == 2)
			{
				if (bServer) Server();
				else Client();
			}

			if (bServer)
			{
				while (gameState == 1)
				{ 
					Server();
				}
			}

			else
			{
				Settings();
				Create();

				auto tp1 = chrono::system_clock::now();
				auto tp2 = chrono::system_clock::now();

				while (bAtomActive && gameState == 1)
				{

					tp2 = std::chrono::system_clock::now();
					std::chrono::duration<float> elapsedTime = tp2 - tp1;
					tp1 = tp2;
					float fElapsedTime = elapsedTime.count();

					timeSinceLastTick += fElapsedTime;
					if (timeSinceLastTick >= tickDuration)
					{
						Input();
						if (!pause) Update(fElapsedTime);
						if (bMultiplayer)
						{
							Client();
						}
						timeSinceLastTick = 0;
					}

					Render();

					wchar_t s[256];
					wstring sConsoleTitle2 = sConsoleTitle;
					sConsoleTitle2.append(L" - FPS %3.2f");
					const wchar_t* cConsoleTitle = sConsoleTitle2.c_str();
					swprintf_s(s, 256, cConsoleTitle, 1.0f / fElapsedTime);
					//SetConsoleTitle(s);
					writeToScreen(bfScreen, nScreenWidth * nScreenHeight);
				}
			}
		}
	}

protected:

	bool bMultiplayer;
	bool bServer;

	int nScreenWidth;
	int nScreenHeight;
	float tickDuration;
	float timeSinceLastTick;
	wstring sConsoleTitle;

	HANDLE wConsoleHnd;
	HANDLE rConsoleHnd;
	CHAR_INFO *bfScreen;
	SMALL_RECT srWindowSize;
	
	static std::atomic<bool> bAtomActive;

	unordered_map<int, Entity*> entityList;

	int gameState;
	bool pause;

};

float cDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

std::atomic<bool> TobiGameEngine::bAtomActive(false);