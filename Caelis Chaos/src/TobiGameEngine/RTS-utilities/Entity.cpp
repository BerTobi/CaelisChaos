#include "Entity.h"
#include <string>

Entity::Entity()
{
	mPosition = { 0, 0 };
	mTargetPosition = { 0, 0 };
	nTeam = 0;
	nKillReward = 0;
	pSprite = "";
	sName = "";

	fHeight = 0;
	fWidth = 0;
	nMaxHealth = 0;
	nHealth = 0;
	fMovementAngle = 0;
	fMovementSpeed = 0;
	fSplashArea = 0.0f;
}

void Entity::setSprite(std::string newSprite)
{
	pSprite = newSprite;
}

void Entity::setCoords(float nX, float nY)
{
	mPosition = { nX, nY };
}

void Entity::setCoords(Point nPosition)
{
	mPosition = nPosition;
}

void Entity::move(Point nCoordinate)
{
	Point fDistance = { nCoordinate.x - mPosition.x , nCoordinate.y - mPosition.y };

	float fHypotenuse = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
	float fHorizontalAngle = acos(fDistance.x / fHypotenuse);
	float fVerticalAngle = asin(fDistance.y / fHypotenuse);

	float fSpeedX = fMovementSpeed * cos(fHorizontalAngle);
	float fSpeedY = fMovementSpeed * sin(fVerticalAngle);

	Point nextPosition = mPosition;

	if (nCoordinate.x != mPosition.x)
		if (abs(nCoordinate.x - mPosition.x) < fSpeedX)
			nextPosition.x = nCoordinate.x;
		else
			nextPosition.x = mPosition.x + fSpeedX;

	if (nCoordinate.y != mPosition.y)
		if (abs(nCoordinate.y - mPosition.y) < fSpeedY)
			nextPosition.y = nCoordinate.y;
		else
			nextPosition.y = mPosition.y + fSpeedY;

	setCoords(nextPosition);

	fMovementAngle = fHorizontalAngle;
}

void Entity::move(Point nCoordinate, float fSpeed)
{
	Point fDistance = { nCoordinate.x - mPosition.x , nCoordinate.y - mPosition.y };

	float fHypotenuse = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
	float fHorizontalAngle = acos(fDistance.x / fHypotenuse);
	float fVerticalAngle = asin(fDistance.y / fHypotenuse);

	float fSpeedX = fSpeed * cos(fHorizontalAngle);
	float fSpeedY = fSpeed * sin(fVerticalAngle);

	Point nextPosition = mPosition;

	if (nCoordinate.x != mPosition.x)
		if (abs(nCoordinate.x - mPosition.x) < fSpeedX)
			nextPosition.x = nCoordinate.x;
		else
			nextPosition.x = mPosition.x + fSpeedX;

	if (nCoordinate.y != mPosition.y)
		if (abs(nCoordinate.y - mPosition.y) < fSpeedY)
			nextPosition.y = nCoordinate.y;
		else
			nextPosition.y = mPosition.y + fSpeedY;

	setCoords(nextPosition);

	fMovementAngle = fHorizontalAngle;
}

void Entity::setTeam(int team)
{
	nTeam = team;
}

int Entity::getTeam()
{
	return nTeam;
}

int Entity::getID()
{
	return ID;
}

void Entity::setID(int nID)
{
	ID = nID;
}

void Entity::setTargetPosition(float nX, float nY)
{
	mTargetPosition = { nX, nY };
}

void Entity::setTargetPosition(Point targetPosition)
{
	mTargetPosition = targetPosition;
}