/*
Caelis Chaos

Copyright (c) Tobias Bersia

All rights reserved.
*/

constexpr auto GAME_VERSION_STRING = "0.4.0 DevBuild 3 (Refactor)";

#include "CaelisEngine/CaelisEngine.h"
#include "CaelisEngine/GameStates/MainMenu.h"

class CaelisChaos : public CaelisEngine
{
public:
	CaelisChaos()
	{
		setGameState(new MainMenu);
	}

private:



};

int main(int argc, char* args[])
{
	CaelisChaos game;
	game.start();
	return 0;
}
