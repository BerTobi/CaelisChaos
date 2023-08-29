#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>

class Sprite
{
public:
	Sprite();

	void modifySprite(std::wstring newSprite, int newSize);

	int nSize;
	std::wstring sprite;
};

#endif