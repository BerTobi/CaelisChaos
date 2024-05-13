#include "ListUI.h"

ListUI::ListUI()
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mTextColor = { 0xFF, 0xFF, 0xFF };
    mBackgroundColor = { 0, 0, 0 };

    mColumns = 0;
    mRows = 0;

    mEnabled = true;
}

ListUI::ListUI(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mTextColor = { 0xFF, 0xFF, 0xFF };
    mBackgroundColor = { 0, 0, 0 };

    mColumns = 0;
    mRows = 0;

    mRenderer = renderer;
    mWindow = window;
    mFont = font;

    mEnabled = true;

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);
}

void ListUI::free()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    for (auto textBox : TextBoxes)
    {
        textBox.second->free();
    }
    Title.free();
}

void ListUI::setLayer(int layer)
{
    mLayer = layer;
}

void ListUI::setPosition(float x, float y)
{
    mPosition.x = x * mScreenWidth;
    mPosition.y = y * mScreenHeight;

    mRelativePositionX = x;
    mRelativePositionY = y;

    int row = 0;
    int column = 0;

    for (auto textBox : TextBoxes)
    {
        textBox.second->setPosition(mRelativePositionX + mRelativeWidth / (float)mColumns * column, mRelativePositionY + mRelativeHeight / (float)mRows * row);
        textBox.second->setSize(mRelativeWidth / (float)mColumns, mRelativeHeight / (float)mRows);
        if (column < mColumns - 1) column++;
        else
        {
            column = 0;
            row++;
        }

    }
}

void ListUI::setSize(float width, float height)
{
    mWidth = width * mScreenWidth;
    mHeight = height * mScreenHeight;

    mRelativeWidth = width;
    mRelativeHeight = height;

    int row = 0;
    int column = 0;

    for (auto textBox : TextBoxes)
    {
        textBox.second->setPosition(mRelativePositionX + mRelativeWidth / (float)mColumns * column, mRelativePositionY + mRelativeHeight / (float)mRows * row);
        textBox.second->setSize(mRelativeWidth / (float)mColumns, mRelativeHeight / (float)mRows);
        if (column < mColumns - 1) column++;
        else
        {
            column = 0;
            row++;
        }

    }
}

void ListUI::setTableSize(int rows, int columns)
{
    mRows = rows;
    mColumns = columns;
}

void ListUI::setFontSize(int size)
{
    mFontSize = size;
}

void ListUI::showBorder(bool show)
{
    mShowBorder = show;

    if (!TextBoxes.empty())
    {
        for (auto textBox : TextBoxes) textBox.second->showBorder(mShowBorder);
    }
}

void ListUI::addItem(std::string name, std::string text)
{
    TextBoxes[name] = new TextBox(mRenderer, mWindow, mFont);
    TextBoxes[name]->setText(text);
    TextBoxes[name]->setFontSize(mFontSize);
    TextBoxes[name]->setAlignment("LEFT");
    TextBoxes[name]->setBackgroundColor(mBackgroundColor);
    TextBoxes[name]->setTextColor({ mTextColor });
    TextBoxes[name]->showBorder(mShowBorder);

    int row = 0;
    int column = 0;

    for (auto textBox : TextBoxes)
    {
        textBox.second->setPosition(mRelativePositionX + mRelativeWidth / (float)mColumns * column, mRelativePositionY + mRelativeHeight / (float)mRows * row);
        textBox.second->setSize(mRelativeWidth / (float)mColumns, mRelativeHeight / (float)mRows);
        if (column < mColumns - 1) column++;
        else
        {
            column = 0;
            row++;
        }

    }
}

void ListUI::setTextColor(SDL_Color color)
{
    mTextColor = color;

    for (auto textBox : TextBoxes)
    {
        textBox.second->setTextColor(mTextColor);
    }
}

void ListUI::setBackgroundColor(SDL_Color color)
{
    mBackgroundColor = color;

    for (auto textBox : TextBoxes)
    {
        textBox.second->setBackgroundColor(mBackgroundColor);
    }
}

void ListUI::render()
{
    for (auto textBox : TextBoxes)
    {
        textBox.second->render();
    }
}

void ListUI::enable(bool state)
{
    mEnabled = state;
}

bool ListUI::isEnabled()
{
    return mEnabled;
}