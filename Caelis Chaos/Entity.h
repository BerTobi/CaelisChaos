#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include <iostream>

class Entity
{
public:

	Entity();

	void setSprite(Sprite newSprite);

	void setCoords(float nX, float nY);

	void move(float nX, float nY, float fSpeed);

	void setTeam(int team);

	int getTeam();

	float fX;
	float fY;
	Sprite sprite;

protected:

	int nTeam;

};

#endif
