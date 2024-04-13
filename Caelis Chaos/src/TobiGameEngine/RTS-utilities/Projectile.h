#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();

	virtual ~Projectile() = default;

	bool move(Point nCoordinate, std::unordered_map<int, Entity*>& entityList);

public:

	int nTargetID;
	bool bFriendlyFire;

protected:

};

#endif
