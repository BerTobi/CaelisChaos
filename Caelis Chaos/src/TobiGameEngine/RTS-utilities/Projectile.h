#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();

	virtual ~Projectile() = default;

public:

	int nTargetID;

protected:

};

#endif
