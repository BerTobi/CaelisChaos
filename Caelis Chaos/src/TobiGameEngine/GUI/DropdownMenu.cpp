#include "DropdownMenu.h"

DropdownMenu::DropdownMenu()
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    mBorderThickness = 5;

    mColumns = 0;
    mRows = 0;

    button = new Button();
    menu = new Menu();
    menu->enable(false);
    menu->setTableSize(0, 0);

    mEnabled = true;
}

DropdownMenu::DropdownMenu(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
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

    button = new Button(renderer, window, font);
    menu = new Menu(renderer, window, font);
    menu->enable(false);
    menu->setTableSize(0, 0);

    mEnabled = true;

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);
}

void DropdownMenu::setTitle(std::string title)
{
    button->setText(title);
}

void DropdownMenu::free()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mRelativePositionX = 0;
    mRelativePositionY = 0;

    button->free();
    menu->free();
}

void DropdownMenu::setLayer(int layer)
{
    mLayer = layer;
    button->setLayer(layer);
    menu->setLayer(layer);
}

void DropdownMenu::setPosition(float x, float y)
{
    mPosition.x = x * mScreenWidth;
    mPosition.y = y * mScreenHeight;

    mRelativePositionX = x;
    mRelativePositionY = y;

    button->setPosition(x, y);
    menu->setPosition(x, y);
}

void DropdownMenu::setSize(float width, float height)
{
    mWidth = width * mScreenWidth;
    mHeight = height * mScreenHeight;

    mRelativeWidth = width;
    mRelativeHeight = height;

    menu->setSize(width, height);
}

void DropdownMenu::setButtonSize(float width, float height)
{
    button->setSize(width, height);
}

void DropdownMenu::setBorderThickness(int thickness)
{
    mBorderThickness = thickness;
    button->setBorderThickness(thickness);
    menu->setBorderThickness(thickness);
}

void DropdownMenu::addItem(std::string name, std::string text)
{
    mRows++;
    menu->setTableSize(mRows, 1);
    menu->addButton(name, text);
    
}

bool DropdownMenu::handleEvent(SDL_Event* e)
{
    if (mEnabled)
    {
        if (button->isEnabled())
        {
            button->handleEvent(e);
            if (button->bPressed)
            {
                menu->enable(true);
                button->enable(false);
                button->bPressed = false;
                return true;
            }
            else if (button->bHovered) return true;
        }
        
        if (menu->isEnabled())
        { 
            for (auto menuButton : menu->Buttons)
            {
                menuButton.second->handleEvent(e);
                if (menuButton.second->bPressed)
                {
                    button->setText(menuButton.second->mText);
                    menu->enable(false);
                    button->enable(true);
                    return true;
                }
            }

            return menu->handleEvent(e);
        }

        

    }
    return false;
}

void DropdownMenu::render()
{
    SDL_Rect Border = { mPosition.x, mPosition.y, mWidth, mHeight };

    //SDL_SetRenderDrawColor(mRenderer, 0xDF, 0xF9, 0xBA, 0xFF);
    //
    //SDL_RenderFillRect(mRenderer, &Border);

    button->render();
    if (menu->isEnabled())menu->render();
}

void DropdownMenu::enable(bool state)
{
    mEnabled = state;
}

bool DropdownMenu::isEnabled()
{
    return mEnabled;
}