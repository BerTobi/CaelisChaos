#include "TextBox.h"

TextBox::TextBox()
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;
    mTextLength = 0;
    mTextColor = { 0xFF, 0xFF, 0xFF };
    mBackgroundColor = { 0, 0, 0 };

    mFontSize = 10;
    mEditable = false;
    mShowBorder = false;
    mEnabled = true;

    mTextAlignment = "LEFT";
}

TextBox::TextBox(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mLayer = 0;
    mTextLength = 0;
    mTextColor = { 0xFF, 0xFF, 0xFF };
    mBackgroundColor = { 0, 0, 0 };

    mFontSize = 10;
    mEditable = false;
    mShowBorder = false;
    mEnabled = true;

    mTextAlignment = "LEFT";

    mRenderer = renderer;
    mSprite = LTexture(renderer, window, font);

    SDL_GetWindowSize(window, &mScreenWidth, &mScreenHeight);
}

void TextBox::free()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mSprite.free();
}

void TextBox::setLayer(int layer)
{
    mLayer = layer;
}

void TextBox::editable(bool editable)
{
    mEditable = editable;
}

void TextBox::showBorder(bool show)
{
    mShowBorder = show;
}

void TextBox::setPosition(float x, float y)
{
    mPosition.x = x * mScreenWidth;
    mPosition.y = y * mScreenHeight;
}

void TextBox::setSize(float width, float height)
{
    mWidth = width * mScreenWidth;
    mHeight = height * mScreenHeight;
}

void TextBox::setLength(int length)
{
    mTextLength = length;
}

void TextBox::setFontSize(int size)
{
    mFontSize = size;
}

void TextBox::setFontSizeRelative(float size)
{
    mFontSize = size * mScreenWidth;
}

void TextBox::setText(std::string text)
{
    mText = text;
    mSprite.free();
    mSprite.loadFromRenderedText(mText, mTextColor);
}

void TextBox::setTextColor(SDL_Color color)
{
    mTextColor = color;
    mSprite.free();
    mSprite.loadFromRenderedText(mText, mTextColor);
}

void TextBox::setBackgroundColor(SDL_Color color)
{
    mBackgroundColor = color;
}

void TextBox::setAlignment(std::string alignment)
{
    mTextAlignment = alignment;
}

void TextBox::handleEvent(SDL_Event* e)
{
    if (mEditable)
    {
        if (e->type == SDL_TEXTINPUT)
        {
            if (mTextLength > 0)
            {
                if (mText.length() < mTextLength)
                    mText += e->text.text;
            }
            else mText += e->text.text;
            mSprite.free();
            mSprite.loadFromRenderedText(mText, mTextColor);
            SDL_StopTextInput();
        }

        else if (e->type == SDL_KEYDOWN)
        {
            if (e->key.keysym.sym == SDLK_BACKSPACE)
            {
                mText = mText.substr(0, mText.length() - 1);
                mSprite.free();
                mSprite.loadFromRenderedText(mText, mTextColor);
            }
            else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
            {
                SDL_SetClipboardText(mText.c_str());
            }
            else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
            {
                char* tempText = SDL_GetClipboardText();
                mText = tempText;
                SDL_free(tempText);
                mSprite.free();
                mSprite.loadFromRenderedText(mText, mTextColor);
            }
        }
    }
}

void TextBox::render()
{
    if (mShowBorder)
    {
        SDL_Rect Border = { mPosition.x, mPosition.y, mWidth, mHeight };
        SDL_SetRenderDrawColor(mRenderer, mBackgroundColor.r , mBackgroundColor.g, mBackgroundColor.b, 0xFF);
        SDL_RenderFillRect(mRenderer, &Border);
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(mRenderer, &Border);
    }
    
    if (mText.length() > 0)
    {
        if (mTextLength > 0)
        {
            mFontSize = (mWidth - mWidth / 10) / mTextLength;
        }
       
        if (mTextAlignment == "CENTERED")
        {
            mSprite.render(mPosition.x + mWidth / 2 - std::min((int)(mWidth - mFontSize), (int)(mFontSize * mText.length())) * 0.5f, mPosition.y + mHeight * 0.1f, std::min((int)(mWidth - mFontSize), (int)(mFontSize * mText.length())), mHeight * 0.8f);
        }
        else
        {
            mSprite.render(mPosition.x + mFontSize / 2, mPosition.y + mHeight * 0.1f, std::min((int)(mWidth - mFontSize), (int)(mFontSize * mText.length())), mHeight * 0.8f);
        }
    }
    
}

void TextBox::enable(bool state)
{
    mEnabled = state;
}

bool TextBox::isEnabled()
{
    return mEnabled;
}