#ifndef CAELISCHAOS_H
#define CAELISCHAOS_H

#define VERSION_STRING "0.4.0 DevBuild 1 (Refactor)"

/*
Caelis Chaos

Copyright (c) Tobias Bersia

All rights reserved.
*/

#include "CaelisEngine/CaelisEngine.h"

class CaelisChaos : public CaelisEngine
{
public:
	CaelisChaos()
	{

	}

private:


};

int main(int argc, char* args[])
{
	CaelisChaos game;
	game.start();
	return 0;
}

#endif