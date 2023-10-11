#include "Building.h"
#include "Entity.h"
#include "Unit.h"
#include <vector>

Building::Building()
{
	nHealth = 0;
	nTeam = 0;
}

void Building::setHealth(int newHealth)
{
	nHealth = newHealth;
}

int Building::getHealth()
{
	return nHealth;
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
        wave[a]->setTarget(abs(fX - 32), abs(fY - 32));
    }

    return wave;
}
