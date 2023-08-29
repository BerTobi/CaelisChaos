/*
Tobi Console Game Engine

Version 0.2b

Provides basic functionalities to create a game in the system console.
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <Windows.h>
#include <Tchar.h>
#include <string.h>
#include <exception>

using namespace std;

class Sprite
{
public:
	Sprite()
	{
		sprite = L"";
		nSize = 0;
	};

	void modifySprite(std::wstring newSprite, int newSize)
	{
		sprite = newSprite;
		nSize = newSize;
	};

	int nSize;
	std::wstring sprite;
};

class TobiGameEngine
{
public:
	TobiGameEngine()
	{
		nScreenWidth = 80;
		nScreenHeight = 30;

		wConsoleHnd = GetStdHandle(STD_OUTPUT_HANDLE);
		rConsoleHnd = GetStdHandle(STD_INPUT_HANDLE);

		sConsoleTitle = L"Tobi Game Engine";
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

		SMALL_RECT srWindowSize = { 0, 0, (nScreenWidth - 1), (nScreenHeight - 1) };

		if (!SetConsoleWindowInfo(wConsoleHnd, TRUE, &srWindowSize))
		{
			DWORD error = GetLastError();
			return error;
		}
		
		bfScreen = new wchar_t[nScreenWidth * nScreenHeight];

		return 0;
	}

	//Write an screen buffer to screen from coordinates {0, 0}
	void writeToScreen(wchar_t* screen, int screenSize)
	{
		DWORD dwBytesWritten = 0;
		WriteConsoleOutputCharacter(wConsoleHnd, screen, screenSize, { 0,0 }, &dwBytesWritten);
	}

	//Sets the time between game ticks in milliseconds
	void setGameTick(int nMilliseconds)
	{
		this_thread::sleep_for(chrono::milliseconds(nMilliseconds));
	}

	void setCursorVisibility(bool visible)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = visible;
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	void drawSprite(int x, int y, Sprite sprite)
	{
		for (int sX = 0; sX < sprite.nSize; sX++)
			for (int sY = 0; sY < sprite.nSize; sY++)
			{
				int currentPixel = x - (sprite.nSize / 2) + sX + nScreenWidth * (y - (sprite.nSize / 2) + sY);
				if (currentPixel >= 0 && currentPixel < nScreenWidth * nScreenHeight && sprite.sprite[sX + sY * sprite.nSize] != ' ') bfScreen[x - (sprite.nSize / 2) + sX + nScreenWidth * (y - (sprite.nSize / 2) + sY)] = sprite.sprite[sX + sY * sprite.nSize];
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

protected:

	int nScreenWidth;
	int nScreenHeight;
	HANDLE wConsoleHnd;
	HANDLE rConsoleHnd;

	wchar_t *bfScreen;

	wstring sConsoleTitle;
};

class Entity
{
public:

	Entity()
	{
		fX = 0;
		fY = 0;
	}

	void setSprite(Sprite newSprite)
	{
		sprite = newSprite;
	}

	void setCoords(float nX, float nY)
	{
		fX = nX;
		fY = nY;
	}

	void move(float nX, float nY, float fSpeed)
	{
		float nextX = fX;
		float nextY = fY;

		if (nX > fX)
			if (abs(nX - fX) < fSpeed)
				nextX = nX;
			else
				nextX = fX + fSpeed;
		else if (nX < fX) 
			if (abs(nX - fX) < fSpeed)
				nextX = nX;
			else
				nextX = fX - fSpeed;

		if (nY > fY)
			if (abs(nY - fY) < fSpeed)
				nextY = nY;
			else
				nextY = fY + fSpeed;
		else if (nX < fY)
			if (abs(nY - fY) < fSpeed)
				nextY = nY;
			else
				nextY = fY - fSpeed;

		setCoords(nextX, nextY);
	}

float fX;
float fY;
Sprite sprite;

protected:

};

class Unit : public Entity
{
public:
	Unit()
	{
		nHealth = 0;
		fSpeed = 0;
		fTargetX = fX;
		fTargetY = fY;
	}

	void setHealth(int newHealth)
	{
		nHealth = newHealth;
	}

	void setSpeed(int newSpeed)
	{
		fSpeed = newSpeed;
	}

	void move(float nX, float nY)
	{
		Entity::move(nX, nY, fSpeed);
	}

	void setTarget(float nX, float nY)
	{
		fTargetX = nX;
		fTargetY = nY;
	}

public:

	float fTargetX;
	float fTargetY;

protected:

	int nHealth;
	float fSpeed;
	
};