#ifndef TRIGGER_H
#define TRIGGER_H

#include "Unit.h"
#include <set>

class Trigger
{
	public:

		Trigger();

		void setCoords(Vector2D upper, Vector2D lower);

		void setValidTeams(std::set<int> teams);

		virtual void setNewTarget(Vector2D target);

		virtual void activate(Unit* unit);

		void enable(bool enable);

		Vector2D UpperLeftCorner;
		Vector2D LowerRightCorner;

		std::set<int> validTeams;
		bool bEnabled;
		std::vector<bool*> conditions;

		virtual ~Trigger() = default;
		
};

#endif