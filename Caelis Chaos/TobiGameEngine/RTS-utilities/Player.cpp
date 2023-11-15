#include "Player.h"

Player::Player()
{
	fCameraX = 0;
	fCameraY = 0;

	nTeam = 0;
	nGold = 20000;

	selectedBuildingID = 0;
	lockKnight = true;
	healthModifier = 1.0f;

	spawnUnitCooldown = 30;
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

void Player::setHealthModifier(float newMod)
{
	healthModifier = newMod;
}

Building* Player::selectedBuilding()
{
	return teamBuildings[selectedBuildingID];
}