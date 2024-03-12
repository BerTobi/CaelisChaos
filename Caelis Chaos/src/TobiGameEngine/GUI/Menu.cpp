#include "Menu.h"

Menu::Menu()
{
	mPosition.x = 0;
	mPosition.y = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mColumns = 0;
    mRows = 0;

	mEnabled = true;
}

Menu::Menu(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
    mPosition.x = 0;
    mPosition.y = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mColumns = 0;
    mRows = 0;

    mRenderer = renderer;
    mWindow = window;
    mFont = font;

    mEnabled = true;

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);
}

void Menu::free()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    for (auto button : Buttons)
    {
        button.second->free();
    }
    Title.free();
}

void Menu::setPosition(float x, float y)
{
    mPosition.x = x * mScreenWidth;
    mPosition.y = y * mScreenHeight;

    mRelativePositionX = x;
    mRelativePositionY = y;
}

void Menu::setSize(float width, float height)
{
    mWidth = width * mScreenWidth;
    mHeight = height * mScreenHeight;

    mRelativeWidth = width;
    mRelativeHeight = height;
}

void Menu::setTableSize(int rows, int columns)
{
    mRows = rows;
    mColumns = columns;
}

void Menu::addButton(std::string name, std::string text)
{
    Buttons[name] = new Button(mRenderer, mWindow, mFont);
    Buttons[name]->setText(text);

    int row = 0;
    int column = 0;

    for (auto button : Buttons)
    {
        button.second->setPosition(mRelativePositionX + mRelativeWidth / (float)mColumns * column, mRelativePositionY + mRelativeHeight / (float)mRows * row);
        button.second->setSize(mRelativeWidth / (float)mColumns, mRelativeHeight / (float)mRows);
        button.second->setVisibility(true);
        if (column < mColumns - 1) column++;
        else
        {
            column = 0;
            row++;
        }

    }
}

void Menu::handleEvent(SDL_Event* e)
{
    for (auto button : Buttons)
    {
        button.second->handleEvent(e);
    }
}

void Menu::render()
{
    for (auto button : Buttons)
    {
        button.second->render();
    }
}

void Menu::enable(bool state)
{
    mEnabled = state;
}

bool Menu::isEnabled()
{
    return mEnabled;
}