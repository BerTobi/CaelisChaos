#ifndef PLAYER_H
#define PLAYER_H

#include "Building.h"
#include "Unit.h"
#include <unordered_map>

class Building;
class Unit;

class Player
{
public:

	std::vector<Building*> teamBuildings;
	std::vector<Unit*> teamUnits;

	int selectedBuildingID;
	bool lockKnight;
	float healthModifier;
	int spawnUnitCooldown;

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
	void addGold(int gold);

	void unlockKnight();

	void setHealthModifier(float newMod);
	void switchAI();
	bool isAI();

	// Returns a pointer to the current selected building
	Building* selectedBuilding();


private:

	int nGold;
	int nTeam;

	
	float fCameraX;
	float fCameraY;

	bool spectator;
	bool AI;
	
};

#endif