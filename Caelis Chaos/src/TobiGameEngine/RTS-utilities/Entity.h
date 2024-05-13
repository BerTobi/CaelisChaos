#ifndef ENTITY_H
#define ENTITY_H

#include <TMath.h>
#include <GUI/Button.h>
#include <unordered_map>
#include <iostream>
#include <string>

class Entity
{
public:

	Entity();

	void setSprite(std::string newSprite);

	void setCoords(float nX, float nY);

	void setCoords(Vector2D nPosition);

	void move(Vector2D nCoordinate);

	void move(Vector2D nCoordinate, float fSpeed);

	bool checkCollition(std::unordered_map<int, Entity*>& entityList);

	void setTeam(int team);

	int getTeam();

	int getID();

	void setID(int nID);

	virtual void setTargetPosition(float nX, float nY);

	virtual void setTargetPosition(Vector2D targetPosition);

	//Statistic methods

	void setHealth(int newHealth);

	void setMaxHealth(int newMaxHealth);

	void addHealth(int health);

	void addMaxHealth(int health);

	int getArmour();

	void setArmour(int newArmour);

	int getLastHitID();

	void setLastHitID(int id);
	

	virtual ~Entity() = default;

	
    
	//Entity attributes

	Vector2D mPosition;
	Vector2D mTargetPosition;

	std::string pSprite;
	std::string sName;
	std::string sClass;
	float fHeight;
	float fWidth;
	float fMovementAngle;

	//Entity statistics

	int nKillReward;
	int nMaxHealth;
	int nHealth;
	int nAttack;
	int nAttackSpeed;
	float fSplashArea;
	float fMovementSpeed;
	int nArmour;

	bool isCollidable;

	Button* selectionBox;

protected:

	int nTeam;
	int lastHitID;

private:

	int ID;
	
};

#endif
