#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include <iostream>
#include <string>

class Entity
{
public:

	Entity();

	void setSprite(std::string newSprite);

	void setCoords(float nX, float nY);

	void move(float nX, float nY, float fSpeed);

	void setTeam(int team);

	int getTeam();

	int getID();

	void setID(int nID);

	virtual void setTarget(float nX, float nY);

	float fX;
	float fY;

	virtual ~Entity() = default;

	int nKillReward;
    float fTargetX;
	float fTargetY;
	std::string pSprite;
	std::string sName;
	float fHeight;
	float fWidth;
	int nMaxHealth;
	int nHealth;

protected:

	int nTeam;

private:

	int ID;
	
};

#endif
