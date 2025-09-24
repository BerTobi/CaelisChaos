/*
Caelis Chaos

Copyright (c) Tobias Bersia

All rights reserved.
*/

#define GAME_VERSION_STRING "0.1.1";

#include "CaelisEngine/CaelisEngine.h"
#include "CaelisEngine/GameStates/MainMenu.h"

class CaelisChaos : public CaelisEngine
{
public:
	CaelisChaos()
	{
		std::string windowTitle = "Caelis Chaos ";
		windowTitle += GAME_VERSION_STRING;
		createWindow(windowTitle);
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
