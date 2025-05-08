#include "Menu.h"

Menu::Menu()
{
	mPosition.x = 0;
	mPosition.y = 0;
    mLayer = 0;
    mFontSize = 10;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mBorderThickness = 5;

    mColumns = 0;
    mRows = 0;

    mBorderPath = "NONE";

	mEnabled = true;
}

Menu::Menu(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;
    mFontSize = 10;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mBorderThickness = 5;

    mColumns = 0;
    mRows = 0;

    mRenderer = renderer;
    mWindow = window;
    mFont = font;

    mBorderSprite = LTexture(renderer, window, font);
    mBorderPath = "NONE";

    mEnabled = true;

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);

    mBorderSprite.free();
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

void Menu::setBorderSprite(std::string path)
{
    mBorderPath = path;
    if (path != "NONE")
    {
        mBorderSprite.loadFromFile(mBorderPath);
        mBorderSprite.setBlendMode(SDL_BLENDMODE_BLEND);
    }
}

void Menu::setBorderThickness(int thickness)
{
    mBorderThickness = thickness;
}

void Menu::setButtonBorderSprite(std::string path)
{
    for (auto button : Buttons)
    {
        button.second->setBorderSprite(path);
    }
}

void Menu::setFontSize(int size)
{
    mFontSize = size;
}

void Menu::setFontSizeRelative(float size)
{
    mFontSize = size * mScreenWidth;
}

void Menu::addButton(std::string name, std::string text)
{
    Buttons[name] = new Button(mRenderer, mWindow, mFont);
    Buttons[name]->setText(text);
    Buttons[name]->enable(mEnabled);
    Buttons[name]->setFontSize(mFontSize);

    int row = 0;
    int column = 0;

    float mRelativeButtonWidth = mRelativeWidth / (float)mColumns;
    float mRelativeButtonHeight = mRelativeHeight / (float)mRows;

    for (auto button : Buttons)
    {
        button.second->setPosition(mRelativePositionX + (mRelativeButtonWidth) * (float)column, mRelativePositionY + (mRelativeButtonHeight) * (float)row);
        button.second->setSize(mRelativeButtonWidth, mRelativeButtonHeight);
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

    if (mBorderPath != "NONE")
    {
        mBorderSprite.render(mPosition.x - mWidth / 20, mPosition.y - mHeight / 20, mWidth + mWidth / 10, mHeight + mHeight / 10);
    }
}

void Menu::enable(bool state)
{
    mEnabled = state;

    for (auto button : Buttons)
    {
        button.second->enable(state);
    }
}

bool Menu::isEnabled()
{
    return mEnabled;
}