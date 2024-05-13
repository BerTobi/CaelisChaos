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
    sClass = "BUILDING";
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
    fWidth = 0;
    fHeight = 0;
    bSelected = false;
    selectionBox = NULL;
    isCollidable = true;
}

void Building::setLevel(int newLevel)
{
    nLevel = newLevel;
}

int Building::getLevel()
{
    return nLevel;
}

std::vector<Unit*> Building::spawnWave(std::vector<Unit*> wave)
{
    for (int a = 0; a < (int)wave.size(); a++)
    {
        wave[a]->setTeam(nTeam);
        if(mPosition.x == 24 || mPosition.y == -24)
            wave[a]->setCoords(mPosition.x, mPosition.y + (a * 0.3f) - ((float)wave.size() / 2) * 0.3f) ;
        else 
            wave[a]->setCoords(mPosition.x + (a * 0.3f) - ((float)wave.size() / 2) * 0.3f, mPosition.y);

        if (mPosition.x == -5)
        {
            wave[a]->setDefaultTarget(mPosition.x - 32, (mPosition.y > 0) ? mPosition.y - 30 : mPosition.y + 30);
        }
        else if (mPosition.x == 5)
        {
            wave[a]->setDefaultTarget(mPosition.x + 32, (mPosition.y > 0) ? mPosition.y - 30 : mPosition.y + 30);
        }
        else if (mPosition.y == -5)
        {
            wave[a]->setDefaultTarget((mPosition.x > 0) ? mPosition.x - 30 : mPosition.x + 30, mPosition.y - 32);
        }
        else if (mPosition.y == 5)
        {
            wave[a]->setDefaultTarget((mPosition.x > 0) ? mPosition.x - 30 : mPosition.x + 30, mPosition.y + 32);
        }
        else
        {
            wave[a]->setDefaultTarget((mPosition.x == 0) ? 0 : (mPosition.x > 0) ? -28 : 28, (mPosition.y == 0) ? 0 : (mPosition.y > 0) ? -28 : 28);
        }
        
    }

    return wave;
}

void Building::upgrade(Player* player)
{

}

void Building::select()
{
    bSelected = !bSelected;
}

void Building::setTargetUnit(int index)
{
    nTargetUnit = index;
}

int Building::getTargetUnit()
{
    return nTargetUnit;
}

std::string Building::attack(Entity* target)
{
    if (nAttackCooldown <= 0)
    {
        if (target->getLastHitID() == -1 && (target->nHealth - nAttack) <= 0) target->setLastHitID(this->getTeam());
        nAttackCooldown = nDefaultAttackCooldown / nAttackSpeed;
        return sProjectile;
    }
    else
        nAttackCooldown -= 1;

    return "NONE";
}
