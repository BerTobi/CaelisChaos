#include "MovementTrigger.h"

MovementTrigger::MovementTrigger()
{
	UpperLeftCorner = { 0, 0 };
	LowerRightCorner = { 0, 0 };
}

void MovementTrigger::setNewTarget(Vector2D target)
{
	newTarget = target;
}

void MovementTrigger::activate(Unit* unit)
{
	bEnabled = true;
	for (int i = 0; i < conditions.size(); i++)
	{
		if (*conditions[i] == false) bEnabled = false;
	}
	if (bEnabled)
	{
		if (validTeams.find(unit->getTeam()) != validTeams.end())
		{
			if (unit->mPosition.x > UpperLeftCorner.x && unit->mPosition.x < LowerRightCorner.x && unit->mPosition.y < UpperLeftCorner.y && unit->mPosition.y > LowerRightCorner.y)
			{
				unit->setDefaultTarget(newTarget);
			}
		}
	}


}