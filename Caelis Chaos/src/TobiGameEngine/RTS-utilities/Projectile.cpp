#include "Projectile.h"
#include "Entity.h"

Projectile::Projectile()
{
	fSpeed = 0;
	fTargetX = fX;
	fTargetY = fY;
	nTeam = 0;
	sName = "NONE";
}

void Projectile::move(float nX, float nY)
{
	Entity::move(nX, nY, fSpeed);
}

void Projectile::setTarget(float nX, float nY)
{
	fTargetX = nX;
	fTargetY = nY;
}
