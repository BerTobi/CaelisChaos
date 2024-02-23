#include "Player.h"

Player::Player()
{
	fCameraX = 0;
	fCameraY = 0;

	nTeam = 0;
	nGold = 100000;
	nPassiveGold = 0;

	selectedBuildingID = 0;
	lockKnight = true;
	lockCannon = true;

	lockTremendinius = true;
	tremendiniusAlive = false;

	lockMinigun = true;
	minigunAlive = false;

	healthModifier = 1.0f;
	upgrades["passiveGold"] = 0;

	spawnUnitCooldown = 30;
	AI = false;
}

int Player::getTeam()
{
	return nTeam;
}

void Player::setTeam(int newTeam)
{
	nTeam = newTeam;
}

void Player::setCamera(float nX, float nY)
{
	fCameraX = nX;
	fCameraY = nY;
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

void Player::unlockMinigun() {
	lockMinigun = false;
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
	return teamBuildings[selectedBuildingID];
}

void Player::passiveGoldUpgrade() {
	if (nGold >= 500 + (300 * upgrades["passiveGold"]) && upgrades["passiveGold"] < 4)
	{
		nGold -= 500 + (300 * upgrades["passiveGold"]);
		upgrades["passiveGold"]++;
		nPassiveGold += 100;
	}
}
