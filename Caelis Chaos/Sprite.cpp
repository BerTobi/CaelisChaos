#include "Sprite.h"
#include <iostream>

Sprite::Sprite()
{
	sprite = L"";
	nSize = 0;
}

void Sprite::modifySprite(std::wstring newSprite, int newSize)
{
	sprite = newSprite;
	nSize = newSize;
}