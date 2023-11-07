#ifndef PLAYER_H
#define PLAYER_H

#include "Building.h"
#include "Unit.h"
#include <unordered_map>

class Player
{
public:

	std::vector<Building*> teamBuildings;
	std::vector<Unit*> teamUnits;

	Player();
	
	int getTeam();

	void setTeam(int newTeam);

	float getCameraX();

	float getCameraY();

	void setCamera(float nX, float nY);

	bool getStatus();

	void setStatus(bool nStatus);

	int getGold();
	
	void setGold(int gold);

private:

	int nGold;
	int nTeam;

	float fCameraX;
	float fCameraY;

	bool spectator;
};

#endif