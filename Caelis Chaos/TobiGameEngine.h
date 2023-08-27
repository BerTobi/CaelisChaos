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

	void drawSprite(wstring sprite, int x, int y, int size)
	{
		for (int sX = 0; sX < size; sX++)
			for (int sY = 0; sY < size; sY++)
			{
				int currentPixel = x - (size / 2) + sX + nScreenWidth * (y - (size / 2) + sY);
				if (currentPixel >= 0 && currentPixel < nScreenWidth * nScreenHeight && sprite[sX + sY * size] != ' ') bfScreen[x - (size / 2) + sX + nScreenWidth * (y - (size / 2) + sY)] = sprite[sX + sY * size];
			}
	}

	wstring scaleSprite(wstring sprite, int size, int newSize)
	{
		int neighbourPixels = 0;
		wstring newSprite;
		if (newSize == size) return sprite;

		else if (newSize < size)
		{
			if (newSize != size - 1)
			{
				sprite = scaleSprite(sprite, size, newSize + 1);
				size = newSize + 1;
			}
			for (int sY = 0; sY < newSize; sY++)
				for (int sX = 0; sX < newSize; sX++)
				{
					neighbourPixels += (sprite[sX + sY * size] != ' ') ? 1 : 0;
					neighbourPixels += (sprite[sX + 1 + sY * size] != ' ') ? 1 : 0;
					neighbourPixels += (sprite[sX + 1 + (sY + 1) * size] != ' ') ? 1 : 0;
					neighbourPixels += (sprite[sX + (sY + 1) * size] != ' ') ? 1 : 0;
					if (neighbourPixels > 2) newSprite.push_back(0x2588);
					else newSprite.push_back(' ');
					neighbourPixels = 0;
				}
		}

		else if (newSize > size)
		{
			if (newSize != size + 1)
			{
				sprite = scaleSprite(sprite, size, newSize - 1);
				size = newSize - 1;
			}
			for (int sY = 0; sY < newSize; sY++)
				for (int sX = 0; sX < newSize; sX++)
				{
					if (sY < size && sY > 0 && sX < size && sX > 0)
					{
						if (sprite[sX + sY * size] != ' ' || sprite[sX - 1 + sY * size] != ' ' || sprite[sX - 1 + (sY - 1) * size] != ' ' || sprite[sX + (sY - 1) * size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
					else if (sY < size && sY > 0 && sX == 0)
					{
						if (sprite[sX + sY * size] != ' ' || sprite[sX + (sY - 1) * size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
					else if (sY < size && sY > 0 && sX == size)
					{
						if (sprite[sX - 1 + sY * size] != ' ' || sprite[sX - 1 + (sY - 1) * size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
					else if (sY == 0 && sX < size && sX > 0)
					{
						if (sprite[sX + sY * size] != ' ' || sprite[sX - 1 + sY * size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
					else if (sY == size && sX < size && sX > 0)
					{
						if (sprite[sX + (sY - 1) * size] != ' ' || sprite[sX - 1 + (sY - 1) * size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
					else if (sY == size && sX == size)
					{
						if (sprite[sX - 1 + (sY - 1) * size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
					else if (sY == 0 && sX == 0)
					{
						if (sprite[sX + (sY) * size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
					else if (sY == size && sX == 0)
					{
						if (sprite[sX + (sY - 1)*size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
					else if (sY == 0 && sX == size)
					{
						if (sprite[sX - 1 + (sY) * size] != ' ') newSprite.push_back(0x2588);
						else newSprite.push_back(' ');
					}
				}
		}



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