#include "Trigger.h"

Trigger::Trigger()
{
	UpperLeftCorner = { 0, 0 };
	LowerRightCorner = { 0, 0 };
	bEnabled = true;
}

void Trigger::setCoords(Vector2D upper, Vector2D lower)
{
	UpperLeftCorner = upper;
	LowerRightCorner = lower;
}

void Trigger::setValidTeams(std::set<int> teams)
{
	validTeams = teams;
}

//From MovementTrigger

void Trigger::setNewTarget(Vector2D target)
{

}

void Trigger::activate(Unit* unit)
{

}

void Trigger::enable(bool enable)
{
	bEnabled = enable;
}