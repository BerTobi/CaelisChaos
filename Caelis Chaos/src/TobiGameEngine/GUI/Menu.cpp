#include "Menu.h"

Menu::Menu()
{
	mPosition.x = 0;
	mPosition.y = 0;
    mLayer = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mBorderThickness = 5;

    mColumns = 0;
    mRows = 0;

	mEnabled = true;
}

Menu::Menu(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mBorderThickness = 5;

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

void Menu::setLayer(int layer)
{
    mLayer = layer;
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

void Menu::setBorderThickness(int thickness)
{
    mBorderThickness = thickness;
}

void Menu::addButton(std::string name, std::string text)
{
    Buttons[name] = new Button(mRenderer, mWindow, mFont);
    Buttons[name]->setText(text);

    int row = 0;
    int column = 0;

    for (auto button : Buttons)
    {
        float mRelativeButtonWidth = mRelativeWidth + (float)mBorderThickness / (float)mScreenWidth * ((float)mColumns - 1.0f);
        float mRelativeButtonHeight = mRelativeHeight + (float)mBorderThickness / (float)mScreenHeight * ((float)mRows - 1.0f);

        button.second->setPosition(mRelativePositionX + mRelativeButtonWidth / (float)mColumns * column - (float)mBorderThickness / (float)mScreenWidth * column, mRelativePositionY + mRelativeButtonHeight / (float)mRows * row - (float)mBorderThickness / (float)mScreenHeight * row);
        button.second->setSize(mRelativeButtonWidth / (float)mColumns, mRelativeButtonHeight / (float)mRows);
        button.second->setVisibility(true);
        if (column < mColumns - 1) column++;
        else
        {
            column = 0;
            row++;
        }

    }
}

bool Menu::handleEvent(SDL_Event* e)
{
    if (mEnabled)
    {
        for (auto button : Buttons)
        {
            button.second->handleEvent(e);
            if (button.second->bPressed || button.second->bHovered) return true;
        }
    }
    return false;
}

void Menu::render()
{
    SDL_Rect Border = { mPosition.x, mPosition.y, mWidth, mHeight };

    //SDL_SetRenderDrawColor(mRenderer, 0xDF, 0xF9, 0xBA, 0xFF);
    //
    //SDL_RenderFillRect(mRenderer, &Border);

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