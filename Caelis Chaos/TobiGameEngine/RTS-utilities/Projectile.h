#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();

	void move(float nX, float nY);

	void setTarget(float nX, float nY);

	virtual ~Projectile() = default;

public:

	float fTargetX;
	float fTargetY;
	std::string sName;
	Entity* targetEntity;

protected:

	float fSpeed;

};

#endif
