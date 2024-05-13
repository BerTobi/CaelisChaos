#include "UnitHUD.h"

UnitHUD::UnitHUD()
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mBorderThickness = 5;

    stats = new ListUI();

    mEnabled = true;
}

UnitHUD::UnitHUD(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mBorderThickness = 5;

    mRenderer = renderer;
    mWindow = window;
    mFont = font;

    stats = new ListUI(renderer, window, font);
    stats->setFontSize(20);
    stats->setTextColor({ 0x00, 0x00, 0x00 });
    stats->setBackgroundColor({ 0x00, 0x00, 0xFF });
    stats->enable(true);
    stats->setTableSize(3, 3);
    stats->addItem("0 placeholder", "");
    stats->addItem("1 Name", "");
    stats->addItem("10 placeholder", "");
    stats->addItem("2 Health", "Health: ");
    stats->addItem("3 Armour", "Armour: ");
    stats->addItem("31 placeholder", "");
    stats->addItem("4 Damage", "Damage: ");
    stats->addItem("5 Range", "Range: ");
    stats->addItem("6 AoE", "AoE: ");

    mEnabled = true;

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);
}

void UnitHUD::free()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mLayer = 0;

    stats->free();
}

void UnitHUD::setLayer(int layer)
{
    mLayer = layer;
    stats->setLayer(layer);
}

void UnitHUD::setPosition(float x, float y)
{
    mPosition.x = x * mScreenWidth;
    mPosition.y = y * mScreenHeight;

    mRelativePositionX = x;
    mRelativePositionY = y;

    stats->setPosition(x, y);
}

void UnitHUD::setSize(float width, float height)
{
    mWidth = width * mScreenWidth;
    mHeight = height * mScreenHeight;

    mRelativeWidth = width;
    mRelativeHeight = height;

    stats->setSize(width, height);
}

void UnitHUD::render()
{
    SDL_Rect Border = { mPosition.x, mPosition.y, mWidth, mHeight };

    SDL_SetRenderDrawColor(mRenderer, 0xDF, 0xF9, 0xBA, 0xFF);
    
    SDL_RenderFillRect(mRenderer, &Border);

    stats->render();
}

void UnitHUD::enable(bool state)
{
    mEnabled = state;
}

bool UnitHUD::isEnabled()
{
    return mEnabled;
}