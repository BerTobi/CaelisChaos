#ifndef MOVEMENTTRIGGER_H
#define MOVEMENTTRIGGER_H

#include "Trigger.h"

class MovementTrigger : public Trigger
{
public:

	MovementTrigger();

	virtual void setNewTarget(Vector2D target);

	virtual void activate(Unit* unit);

	Vector2D newTarget;


};

#endif