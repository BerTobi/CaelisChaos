#include "Player.h"

Player::Player()
{
	fCameraX = 0;
	fCameraY = 0;

	nTeam = 0;
	nGold = 0;
	nPassiveGold = 0;

	selectedBuildingID = -1;
	lockKnight = true;
	lockCannon = true;

	lockTremendinius = true;
	tremendiniusAlive = false;

	lockKatyusha = true;
	KatyushaAlive = false;

	healthModifier = 1.0f;

	spawnUnitCooldown = 30;
	AI = false;

	spectator = false;
	defeated = false;
	alive = true;

	sRace = "NONE";
}

int Player::getTeam()
{
	return nTeam;
}

void Player::setTeam(int newTeam)
{
	nTeam = newTeam;
}

void Player::setCamera(Vector2D nPosition)
{
	fCameraX = nPosition.x;
	fCameraY = nPosition.y;
}

float Player::getCameraX()
{
	return fCameraX;
}

float Player::getCameraY()
{
	return fCameraY;
}

bool Player::getStatus()
{
	return spectator;
}

void Player::setStatus(bool nStatus)
{
	spectator = nStatus;
}

int Player::getGold()
{
	return nGold;
}

void Player::setGold(int gold)
{
	nGold = gold;
}

void Player::addGold(int gold)
{
	nGold += gold;
}

void Player::unlockKnight() {
	lockKnight = false;
}

void Player::unlockTremendinius() {
	lockTremendinius = false;
}

void Player::unlockCannon() {
	lockCannon = false;
}

void Player::unlockKatyusha() {
	lockKatyusha = false;
}

void Player::setHealthModifier(float newMod)
{
	healthModifier = newMod;
}

void Player::switchAI()
{
	AI = !AI;
};

bool Player::isAI()
{
	return AI;
};

Building* Player::selectedBuilding()
{
	if (selectedBuildingID != -1)
		return teamBuildings[selectedBuildingID];
	else
		return NULL;
}

void Player::researchUpgrade(std::string type)
{
	for (int i = 0; i < upgrades[type].size(); i++)
	{
		if (!upgrades[type][i].bResearched && this->getGold() > upgrades[type][i].nPrice)
		{
			upgrades[type][i].bResearched = true;
			addGold(-(upgrades[type][i].nPrice));
			for (int j = 0; j < teamUnits.size(); j++)
			{
				if (upgrades[type][i].EntitiesAffected.find(teamUnits[j]->sSubClass) != upgrades[type][i].EntitiesAffected.end())
					upgrades[type][i].activateEntityEffects(teamUnits[j], this);
			}

			for (int j = 0; j < teamBuildings.size(); j++)
			{
				if (upgrades[type][i].EntitiesAffected.find(teamBuildings[j]->sSubClass) != upgrades[type][i].EntitiesAffected.end())
					upgrades[type][i].activateEntityEffects(teamBuildings[j], this);
			}
			for (auto& prototype : unitPrototypes)
				if (upgrades[type][i].EntitiesAffected.find(prototype.first) != upgrades[type][i].EntitiesAffected.end())
					upgrades[type][i].activateEntityEffects(&prototype.second, this);

			for (auto& prototype : buildingPrototypes)
				if (upgrades[type][i].EntitiesAffected.find(prototype.first) != upgrades[type][i].EntitiesAffected.end())
					upgrades[type][i].activateEntityEffects(&prototype.second, this);

			upgrades[type][i].activatePlayerEffects(this);

			return;
		}
	}
	
	
}

//void Player::passiveGoldUpgrade() {
//	if (nGold >= 500 + (300 * upgrades["passiveGold"]) && upgrades["passiveGold"] < 4)
//	{
//		nGold -= 500 + (300 * upgrades["passiveGold"]);
//		upgrades["passiveGold"]++;
//		nPassiveGold += 150;
//
//		for (auto building : teamBuildings)
//		{
//			building->addMaxHealth(500);
//			building->addHealth(500);
//		}
//	}
//}
