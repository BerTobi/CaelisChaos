#ifndef PLAYER_H
#define PLAYER_H

#include "Building.h"
#include "Unit.h"
#include <unordered_map>
#include <string>

class Building;
class Unit;

class Player
{
public:

	std::vector<Building*> teamBuildings;
	std::vector<Unit*> teamUnits;

	int selectedBuildingID;
	bool lockKnight;
	bool lockTremendinius;
	bool lockCannon;
	bool tremendiniusAlive;
	float healthModifier;
	int spawnUnitCooldown;

	int nPassiveGold;

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
	void unlockTremendinius();
	void unlockCannon();

	void setHealthModifier(float newMod);
	void switchAI();
	bool isAI();
	
	void passiveGoldUpgrade();

	// Returns a pointer to the current selected building
	Building* selectedBuilding();


private:

	int nGold;
	int nTeam;
	std::unordered_map<std::string, int> upgrades;
	
	float fCameraX;
	float fCameraY;

	bool spectator;
	bool AI;
	
};

#endif