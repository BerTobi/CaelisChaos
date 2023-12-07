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

	int getID();

	void setID(int nID);

	virtual void setTarget(float nX, float nY);

	float fX;
	float fY;
	Sprite sprite;

	virtual ~Entity() = default;

	int nKillReward;
    float fTargetX;
	float fTargetY;

protected:

	int nTeam;

private:

	int ID;

};

#endif
