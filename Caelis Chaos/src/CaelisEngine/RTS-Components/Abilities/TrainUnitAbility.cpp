#include "RTS-Components/Ability.h"

class TrainUnitAbility : public Ability {

	std::string m_sUnitType;

public:

	TrainUnitAbility(Match* gameState, std::string sUnitType) : Ability(gameState, "Train" + sUnitType)
	{
		m_sUnitType = sUnitType;
	}

	void Execute()
	{
		m_gameState->createUnit("footman", SDLFPoint((float)(rand() % 200 - 100), (float)(rand() % 200 - 100)));
	}
};