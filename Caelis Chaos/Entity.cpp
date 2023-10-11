#include "Entity.h"

Entity::Entity()
{
	fX = 0;
	fY = 0;
	nTeam = 0;
}

void Entity::setSprite(Sprite newSprite)
{
	sprite = newSprite;
}

void Entity::setCoords(float nX, float nY)
{
	fX = nX;
	fY = nY;
}

void Entity::move(float nX, float nY, float fSpeed)
{
	float fDistanceX = nX - fX;
	float fDistanceY = nY - fY;

	float fHypotenuse = sqrt(fDistanceX * fDistanceX + fDistanceY * fDistanceY);
	float fHorizontalAngle = acos(fDistanceX / fHypotenuse);
	float fVerticalAngle = asin(fDistanceY / fHypotenuse);

	float fSpeedX = fSpeed * cos(fHorizontalAngle);
	float fSpeedY = fSpeed * sin(fVerticalAngle);

	float nextX = fX;
	float nextY = fY;

	if (nX != fX)
		if (abs(nX - fX) < fSpeedX)
			nextX = nX;
		else
			nextX = fX + fSpeedX;

	if (nY != fY)
		if (abs(nY - fY) < fSpeedY)
			nextY = nY;
		else
			nextY = fY + fSpeedY;

	setCoords(nextX, nextY);
}

void Entity::setTeam(int team)
{
	nTeam = team;
}

int Entity::getTeam()
{
	return nTeam;
}