#ifndef PLAYER_H
#define PLAYER_H

#include "Building.h"
#include "Unit.h"
#include "Upgrade.h"
#include <unordered_map>
#include <string>

class Building;
class Unit;
class Upgrade;

class Player
{
public:

	std::vector<Building*> teamBuildings;
	std::vector<Unit*> teamUnits;

	std::unordered_map<std::string, Unit> unitPrototypes;
	std::unordered_map<std::string, Building> buildingPrototypes;

	std::string sRace;

	int selectedBuildingID;
	bool lockKnight;
	bool lockCannon;

	bool lockTremendinius;
	bool tremendiniusAlive;

	bool lockKatyusha;
	bool KatyushaAlive;

	float healthModifier;
	int spawnUnitCooldown;

	int nPassiveGold;
	bool defeated;
	bool alive;

	std::unordered_map<std::string, std::vector<Upgrade>> upgrades;

	Player();
	
	int getTeam();

	void setTeam(int newTeam);

	float getCameraX();
	float getCameraY();
	void setCamera(Vector2D nPosition);

	bool getStatus();
	void setStatus(bool nStatus);

	int getGold();
	void setGold(int gold);
	void addGold(int gold);

	void unlockKnight();
	void unlockTremendinius();
	void unlockCannon();
	void unlockKatyusha();

	void researchUpgrade(std::string upgrade);

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