#include "Entity.h"
#include <string>

Entity::Entity()
{
	mPosition = { 0, 0 };
	mTargetPosition = { 0, 0 };

	pSprite = "";
	sName = "";
	sClass = "OBJECT";
	fHeight = 0;
	fWidth = 0;

	nKillReward = 0;
	nMaxHealth = 0;
	nHealth = 0;
	nArmour = 0;
	fMovementAngle = 0;
	fMovementSpeed = 0;
	fSplashArea = 0.0f;
	nTeam = 0;

}

void Entity::setSprite(std::string newSprite)
{
	pSprite = newSprite;
}

void Entity::setCoords(float nX, float nY)
{
	mPosition = { nX, nY };
}

void Entity::setCoords(Vector2D nPosition)
{
	mPosition = nPosition;
}

void Entity::move(Vector2D nCoordinate)
{
	Vector2D fDistance = { nCoordinate.x - mPosition.x , nCoordinate.y - mPosition.y };

	float fHypotenuse = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
	float fHorizontalAngle = acos(fDistance.x / fHypotenuse);
	float fVerticalAngle = asin(fDistance.y / fHypotenuse);

	float fSpeedX = fMovementSpeed * cos(fHorizontalAngle);
	float fSpeedY = fMovementSpeed * sin(fVerticalAngle);

	Vector2D nextPosition = mPosition;

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

	fMovementAngle = atan2f(mTargetPosition.y - mPosition.y, mTargetPosition.x - mPosition.x) * 180.0f / PI;

	setCoords(nextPosition);

	
}

void Entity::move(Vector2D nCoordinate, float fSpeed)
{
	Vector2D fDistance = { nCoordinate.x - mPosition.x , nCoordinate.y - mPosition.y };

	float fHypotenuse = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
	float fHorizontalAngle = acos(fDistance.x / fHypotenuse);
	float fVerticalAngle = asin(fDistance.y / fHypotenuse);

	float fSpeedX = fSpeed * cos(fHorizontalAngle);
	float fSpeedY = fSpeed * sin(fVerticalAngle);

	Vector2D nextPosition = mPosition;

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

	fMovementAngle = atan2f(0.0f - (mTargetPosition.y - mPosition.y), mTargetPosition.x - mPosition.x) * 180.0f / PI;

	setCoords(nextPosition);

}

bool Entity::checkCollition(std::unordered_map<int, Entity*>& entityList)
{
	bool Collided = false;
	Vector2D nextPosition = mPosition;

	if (isCollidable)
	{
		for (auto& entity : entityList)
		{
			if (entity.second->getID() != getID() && entity.second->isCollidable)
			{
				Vector2D UpperCorner = { entity.second->mPosition.x - entity.second->fWidth / 2.0f, entity.second->mPosition.y - entity.second->fHeight / 2.0f };
				Vector2D LowerCorner = { entity.second->mPosition.x + entity.second->fWidth / 2.0f, entity.second->mPosition.y + entity.second->fHeight / 2.0f };
				if (nextPosition.x + fWidth / 2.0f >= UpperCorner.x && nextPosition.x <= LowerCorner.x && nextPosition.y + fHeight / 2.0f >= UpperCorner.y && nextPosition.y <= LowerCorner.y)
				{
					if (entity.second->mPosition.x <= mPosition.x)
						nextPosition.x = nextPosition.x + 0.01f;
					else 
						nextPosition.x = nextPosition.x - 0.01f;
					
					if (entity.second->mPosition.y <= mPosition.y)
						nextPosition.y = nextPosition.y + 0.01f;
					else
						nextPosition.y = nextPosition.y - 0.01f;

					Collided = true;
					
				}

			}
		}
	}

	setCoords(nextPosition);

	return Collided;
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

void Entity::setTargetPosition(Vector2D targetPosition)
{
	mTargetPosition = targetPosition;
}

void Entity::setHealth(int newHealth)
{
	nHealth = newHealth;
}

void Entity::setMaxHealth(int newMaxHealth)
{
	nMaxHealth = newMaxHealth;
}

void Entity::addHealth(int health)
{
	nHealth += health;
}

void Entity::addMaxHealth(int health)
{
	nMaxHealth += health;
}

int Entity::getArmour() {
	return nArmour;
}

void Entity::setArmour(int newArmour) {
	nArmour = newArmour;
}

int Entity::getLastHitID()
{
	return lastHitID;
}

void Entity::setLastHitID(int id)
{
	lastHitID = id;
}