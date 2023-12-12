#include "Building.h"
#include "Entity.h"
#include "Unit.h"
#include "Player.h"
#include <vector>

Building::Building()
{
	nHealth = 0;
	nTeam = 0;
    sName = "NONE";
    sProjectile = "NONE";
    nLevel = 0;
    lastHitID = -1;
    nAttack = 0;
    nAttackSpeed = 0;
    nAttackCooldown = 0;
    nDefaultAttackCooldown = 0;
    nTargetUnit = -1;
    fAttackRange = 0;
    fAttackDistance = 0;
    nArmour = 50;
}

void Building::setHealth(int newHealth)
{
	nHealth = newHealth;
}

int Building::getHealth()
{
	return nHealth;
}

void Building::addHealth(int health)
{
    nHealth += health;
}

void Building::setLevel(int newLevel)
{
    nLevel = newLevel;
}

int Building::getLevel()
{
    return nLevel;
}

int Building::getArmour() {
    return nArmour;
}

int Building::getLastHitID()
{
    return lastHitID;
}

void Building::setLastHitID(int id)
{
    lastHitID = id;
}

std::vector<Unit*> Building::spawnWave(std::vector<Unit*> wave)
{
    for (int a = 0; a < (int)wave.size(); a++)
    {
        wave[a]->setTeam(nTeam);
        if(fX == 32 || fX == -32)
            wave[a]->setCoords(fX, fY + (a * 0.3f) - ((float)wave.size() / 2) * 0.3f) ;
        else 
            wave[a]->setCoords(fX + (a * 0.3f) - ((float)wave.size() / 2) * 0.3f, fY);

        if (fX == -3)
        {
            wave[a]->setDefaultTarget(fX - 29, (fY > 0) ? fY - 27 : fY + 27);
        }
        else if (fX == 3)
        {
            wave[a]->setDefaultTarget(fX + 29, (fY > 0) ? fY - 27 : fY + 27);
        }
        else if (fY == -3)
        {
            wave[a]->setDefaultTarget((fX > 0) ? fX - 29 : fX + 29, fY - 32);
        }
        else if (fY == 3)
        {
            wave[a]->setDefaultTarget((fX > 0) ? fX - 29 : fX + 29, fY + 32);
        }
        else
        {
            wave[a]->setDefaultTarget((fX == 0) ? 0 : (fX > 0) ? -29 : 29, (fY == 0) ? 0 : (fY > 0) ? -29 : 29);
        }
        
    }

    return wave;
}

void Building::upgrade(Player* player)
{

}

void Building::select(bool selected)
{

}

void Building::setTargetUnit(int index)
{
    nTargetUnit = index;
}

int Building::getTargetUnit()
{
    return nTargetUnit;
}

std::string Building::attack(Unit* target)
{
    if (nAttackCooldown <= 0)
    {
        if (target->getLastHitID() == -1 && (target->nHealth - nAttack) <= 0) target->setLastHitID(this->getTeam());
        target->addHealth(0 - (nAttack * (1.0f - (float)target->getArmour() / 100.0f)));
        nAttackCooldown = nDefaultAttackCooldown / nAttackSpeed;
        return sProjectile;
    }
    else
        nAttackCooldown -= 1;

    return "NONE";
}