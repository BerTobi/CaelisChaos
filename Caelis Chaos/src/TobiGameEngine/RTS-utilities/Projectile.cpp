#include "Projectile.h"
#include "Entity.h"

Projectile::Projectile()
{
	fSplashArea = 0.0f;
	nTeam = 0;
	sName = "NONE";
	sClass = "PROJECTILE";
	isCollidable = false;
	bFriendlyFire = false;

	nTargetID = -1;

}

bool Projectile::move(Vector2D nCoordinate, std::unordered_map<int, Entity*>& entityList)
{
	Vector2D fDistance = { nCoordinate.x - mPosition.x , nCoordinate.y - mPosition.y };

	float fHypotenuse = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
	float fHorizontalAngle = acos(fDistance.x / fHypotenuse);
	float fVerticalAngle = asin(fDistance.y / fHypotenuse);

	float fSpeedX = fMovementSpeed * cos(fHorizontalAngle);
	float fSpeedY = fMovementSpeed * sin(fVerticalAngle);

	fMovementAngle = atan2f(0.0f - (mTargetPosition.y - mPosition.y), mTargetPosition.x - mPosition.x) * 180.0f / PI;

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

	for (auto& entity : entityList)
	{
		if (entity.second->getID() != getID() && entity.second->isCollidable)
		{
			if (bFriendlyFire || entity.second->getTeam() != getTeam())
			{
				//Vector2D UpperCorner = { entity.second->mPosition.x - entity.second->fWidth / 2.0f, entity.second->mPosition.y - entity.second->fHeight / 2.0f };
				//Vector2D LowerCorner = { entity.second->mPosition.x + entity.second->fWidth / 2.0f, entity.second->mPosition.y + entity.second->fHeight / 2.0f };
				//if (nextPosition.x >= UpperCorner.x && nextPosition.x <= LowerCorner.x && nextPosition.y >= UpperCorner.y && nextPosition.y <= LowerCorner.y)
				//{
				//	if (entity.second->mPosition.x <= mPosition.x)
				//		nextPosition.x = nextPosition.x + 0.01f;
				//	else 
				//		nextPosition.x = nextPosition.x - 0.01f;
				//	
				//	if (entity.second->mPosition.y <= mPosition.y)
				//		nextPosition.y = nextPosition.y + 0.01f;
				//	else
				//		nextPosition.y = nextPosition.y - 0.01f;
				//}
				if (cDistance(entity.second->mPosition, mPosition) < fHeight / 2.5f + entity.second->fHeight / 2.5f)
				{
					if (fSplashArea > 0.0f)
					{
						for (auto& entityInArea : entityList)
						{
							if (entityInArea.second->sClass == "BUILDING" || entityInArea.second->sClass == "UNIT")
							{
								if (cDistance(entityInArea.second->mPosition, mPosition) <= fSplashArea && (bFriendlyFire || entityInArea.second->getTeam() != getTeam()))
								{
									if (entityInArea.second->getLastHitID() == -1 && (entityInArea.second->nHealth - nAttack) <= 0) entityInArea.second->setLastHitID(getTeam());
									entityInArea.second->addHealth(0 - (nAttack * (1.0f - (float)entityInArea.second->getArmour() / 100.0f)));
								}
							}
							
						}
					}
					else
					{
						if (entity.second->getLastHitID() == -1 && (entity.second->nHealth - nAttack) <= 0) entity.second->setLastHitID(getTeam());
						entity.second->addHealth(0 - (nAttack * (1.0f - (float)entity.second->getArmour() / 100.0f)));
					}
					return true;
				}
			}
			
		}
	}

	if (cDistance(mPosition, mTargetPosition) < 0.01f)
	{
		if (fSplashArea > 0.0f)
		{
			for (auto& entityInArea : entityList)
			{
				if (entityInArea.second->sClass == "BUILDING" || entityInArea.second->sClass == "UNIT")
				{
					if (cDistance(entityInArea.second->mPosition, mPosition) <= fSplashArea && (bFriendlyFire || entityInArea.second->getTeam() != getTeam()))
					{
						if (entityInArea.second->getLastHitID() == -1 && (entityInArea.second->nHealth - nAttack) <= 0) entityInArea.second->setLastHitID(getTeam());
						entityInArea.second->addHealth(0 - (nAttack * (1.0f - (float)entityInArea.second->getArmour() / 100.0f)));
					}
				}
		
			}
		}
		
		return true;
	}

	setCoords(nextPosition);

	return false;
}

