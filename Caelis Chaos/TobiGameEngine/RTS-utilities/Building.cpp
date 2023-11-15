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
    nLevel = 0;
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

std::vector<Unit*> Building::spawnWave(std::vector<Unit*> wave)
{
    for (int a = 0; a < (int)wave.size(); a++)
    {
        wave[a]->setTeam(nTeam);
        if(fX == 32 || fX == 0)
            wave[a]->setCoords(fX, fY + (a * 0.3f) - ((float)wave.size() / 2) * 0.3f) ;
        else 
            wave[a]->setCoords(fX + (a * 0.3f) - ((float)wave.size() / 2) * 0.3f, fY);

        if (fX == 14)
        {
            wave[a]->setDefaultTarget(fX - 14, abs(fY - 16));
        }
        else if (fX == 18)
        {
            wave[a]->setDefaultTarget(fX + 14, abs(fY - 16));
        }
        else if (fY == 14)
        {
            wave[a]->setDefaultTarget(abs(fX - 16), fY - 14);
        }
        else if (fY == 18)
        {
            wave[a]->setDefaultTarget(abs(fX - 16), fY + 14);
        }
        else
        {
            wave[a]->setDefaultTarget(abs(fX - 32), abs(fY - 32));
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