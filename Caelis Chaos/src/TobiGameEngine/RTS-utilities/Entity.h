#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include <iostream>
#include <string>

struct Point
{
	float x;
	float y;
};

class Entity
{
public:

	Entity();

	void setSprite(std::string newSprite);

	void setCoords(float nX, float nY);

	void setCoords(Point nPosition);

	void move(Point nCoordinate);

	void move(Point nCoordinate, float fSpeed);

	void setTeam(int team);

	int getTeam();

	int getID();

	void setID(int nID);

	virtual void setTargetPosition(float nX, float nY);

	virtual void setTargetPosition(Point targetPosition);

	Point mPosition;
	Point mTargetPosition;

	virtual ~Entity() = default;

	int nKillReward;
    
	std::string pSprite;
	std::string sName;
	float fHeight;
	float fWidth;

	float fMovementSpeed = 0;
	int nMaxHealth;
	int nHealth;
	float fMovementAngle;

	int nAttack;
	int nAttackSpeed;
	float fSplashArea;

protected:

	int nTeam;

private:

	int ID;
	
};

#endif
