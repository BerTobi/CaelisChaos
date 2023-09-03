/*
Caelis Chaos development build

Version 0.1b

*/

#include <iostream>
#include <vector>
#include <thread>
#include "TobiGameEngine.h"
#include "Sprite.h"
#include "Unit.h"
#include "Building.h"

class Footman : public Unit
{
public:
    Footman()
    {
        nHealth = 100;
        fSpeed = 0.03;
        fX = 0;
        fY = 0;
        nAttack = 5;
        nAttackSpeed = 1;
        nDefaultAttackCooldown = 30;
        fAttackRange = 0.2;
        fAttackDistance = 5;
        Sprite footmanSprite;

        footmanSprite.sprite.append(L"  █  ");
        footmanSprite.sprite.append(L"█████");
        footmanSprite.sprite.append(L" ███ ");
        footmanSprite.sprite.append(L" █ █ ");
        footmanSprite.sprite.append(L" █ █ ");
        footmanSprite.nSize = 5;

        setSprite(footmanSprite);
    }
};

class Knight : public Unit
{
public:
    Knight()
    {
        nHealth = 1000;
        fSpeed = 0.03;
        fX = 0;
        fY = 0;
        nAttack = 25;
        nAttackSpeed = 3;
        nDefaultAttackCooldown = 30;
        fAttackRange = 0.2;
        fAttackDistance = 10;
        Sprite knightSprite;

        knightSprite.sprite.append(L"        █     █ ");
        knightSprite.sprite.append(L"       ██     ██");
        knightSprite.sprite.append(L"       █████████");
        knightSprite.sprite.append(L"       █████████");
        knightSprite.sprite.append(L"█       ███████ ");
        knightSprite.sprite.append(L" █      ███████ ");
        knightSprite.sprite.append(L" ███    ███████ ");
        knightSprite.sprite.append(L"  ███    █████  ");
        knightSprite.sprite.append(L"   ███   ██████ ");
        knightSprite.sprite.append(L"    ███ ████████");
        knightSprite.sprite.append(L"     ███████████");
        knightSprite.sprite.append(L"      ██████████");
        knightSprite.sprite.append(L"         ███████");
        knightSprite.sprite.append(L"         ██████ ");
        knightSprite.sprite.append(L"         ██ ██  ");
        knightSprite.sprite.append(L"         █   █  ");
        knightSprite.nSize = 16;

        setSprite(knightSprite);
    }
};

class Fortress : public Building
{
public:
    Fortress()
    {
        nHealth = 1000;
        fX = 0;
        fY = 0;
        Sprite fortressSprite;

        fortressSprite.sprite.append(L"  █  ██  ██  █  ");
        fortressSprite.sprite.append(L"  ████████████  ");
        fortressSprite.sprite.append(L"  ██  ████  ██  ");
        fortressSprite.sprite.append(L"  ██  ████  ██  ");
        fortressSprite.sprite.append(L"  ████████████  ");
        fortressSprite.sprite.append(L"  ████████████  ");
        fortressSprite.sprite.append(L"█ ████████████ █");
        fortressSprite.sprite.append(L"█ ████████████ █");
        fortressSprite.sprite.append(L"████████████████");
        fortressSprite.sprite.append(L"████████████████");
        fortressSprite.sprite.append(L"████████████████");
        fortressSprite.sprite.append(L"███████  ███████");
        fortressSprite.sprite.append(L"██████    ██████");
        fortressSprite.sprite.append(L"██████    ██████");
        fortressSprite.sprite.append(L"██████    ██████");
        fortressSprite.sprite.append(L"██████    ██████");

        fortressSprite.nSize = 16;

        setSprite(fortressSprite);
    }

};

class Caelis_Chaos : public TobiGameEngine
{
public:

    Caelis_Chaos()
    {
        sConsoleTitle = L"Caelis Chaos";
        nScreenWidth = 800;
        nScreenHeight = 600;
    }

    int start()
    {
        int a = createConsole(L"Caelis Chaos", nScreenWidth, nScreenHeight, 8, 8);
        setCursorVisibility(false);

        bool bGameOver = false;
        bool bKey[9];
        bool bHoldKey[9] = { false };
        bool bShowGrid = true;

        float fCameraX = 16;
        float fCameraY = 0;

        float enemyX = 3;
        float enemyY = 3;

        float enemyXb = 2;
        float enemyYb = 2;

        int nMoveTimer = 0;
        int nEntities = 0;

        float fScreenRatio = (float)nScreenWidth / (float)nScreenHeight;
        int nTileSize = 16;
        float fVerticalTilesInScreen = (float)nScreenHeight / (float)nTileSize;
        float fHorizontalTilesInScreen = (float)nScreenWidth / (float)nTileSize;
        float fScale = 1;
        int infoIndex = 0;
        
        int footmanTimer = 0;

        createMap();

        // Game Loop
        while (!bGameOver)
        {
            // GAME TIMING  ============================================

            setGameTick(16);

            // INPUT ============================================

            for (int k = 0; k < 9; k++)
                bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x26ZXCGD"[k]))) != 0;

            // CAMERA MOVEMENT
                
            fCameraX += bKey[0] ? (0.3f / fScale) : 0;
            fCameraX += bKey[1] ? (-0.3f / fScale) : 0;
            fCameraY += bKey[2] ? (0.3f / fScale) : 0;
            fCameraY += bKey[3] ? (-0.3f / fScale) : 0;

            if (bKey[4])
            {
                nTileSize += (!bHoldKey[4] && bKey[4]) ? 1 : 0;
                bHoldKey[4] = true;
            }
            else
                bHoldKey[4] = false;

            if (bKey[5])
            {
                nTileSize -= (!bHoldKey[5] && bKey[5]) ? 1 : 0;
                bHoldKey[5] = true;
            }
            else
                bHoldKey[5] = false;

            if (bKey[6])
            {
                if (!bHoldKey[6]) bShowGrid = !bShowGrid;
                bHoldKey[6] = true;
            }
            else
                bHoldKey[6] = false;

            if (bKey[7])
            {
                if (!bHoldKey[7]) 
                {
                    units.push_back(new Footman());
                    units.back()->setTarget(rand() % 20 - 10, rand() % 50 - 25);
                    units.back()->setTeam(rand() % 4);
                };
                bHoldKey[7] = true;
            }
            else
                bHoldKey[7] = false;

            if (bKey[8])
            {
                if (!bHoldKey[8])
                {
                    if (infoIndex == 0) infoIndex = 1;
                    else infoIndex = 0;
                };
                bHoldKey[8] = true;
            }
            else
                bHoldKey[8] = false;

            // GAME LOGIC ============================================

            footmanTimer++;

            if (units.size() < 200 && footmanTimer % 300 == 0)
            {
                for (int a = 0; a < (int)buildings.size(); a++)
                {
                    vector<Unit*> wave;
                    wave.push_back(new Footman());
                    wave.push_back(new Footman());
                    wave.push_back(new Footman());

                    // Unbalanced on purpose for testing reasons
                    if (buildings[a]->getTeam() == 2)
                        wave.push_back(new Knight());

                    wave = buildings[a]->spawnWave(wave);

                    if (buildings[a]->getTeam() == 4)
                    {
                        for (int b = 0; b < (int)wave.size(); b++)
                        {
                            wave[b]->setHealth(200);
                            wave[b]->setAttack(12);
                            wave[b]->setAttackSpeed(2);
                        }
                    }

                    for (int b = 0; b < (int)wave.size(); b++)
                        units.push_back(wave[b]);
                }
                

                
            }

            // UNIT AI

            if (units.size() >= 1)
            { 

                for (int a = 0; a < (int)units.size(); a++)
                {
                    if (units[a]->fX != units[a]->fTargetX || units[a]->fY != units[a]->fTargetY)
                        units[a]->move(units[a]->fTargetX, units[a]->fTargetY);

                    for (int b = 0; b < (int)units.size(); b++)
                    {
                        if (units[a] != units[b])
                        {
                            if (cDistance(units[a]->fX, units[a]->fY, units[b]->fX, units[b]->fY) < units[a]->fAttackDistance && units[a]->getTeam() != units[b]->getTeam() && units[a]->getTargetUnit() == -1)
                            {
                                units[a]->setTargetUnit(b);
                            }
                        }
                    }

                    //if (units[a]->getTargetUnit() >= 0 && units[a]->getTargetUnit() < (int)units.size())
                    if (units[a]->getTargetUnit() != -1)
                    {
                        // Small guards, activate them if you think TargetUnits are getting out of range.
                        /*if ((int)units.size() >= 1 && (units[a]->getTargetUnit() > (int)units.size() || units[a]->getTargetUnit() < -1))
                        {
                            int leng;
                            leng = snprintf(NULL, 0, "Unit Target %i: %i", unitIndex, units[unitIndex]->getTargetUnit());
                            swprintf_s(&bfScreen[nScreenWidth * 8], leng + 1, L"Unit Target %i: %i", unitIndex, units[unitIndex]->getTargetUnit());
                            leng = snprintf(NULL, 0, "Units Size: %i", (int)units.size());
                            swprintf_s(&bfScreen[nScreenWidth * 9], leng + 1, L"Units Size: %i", (int)units.size());
                            writeToScreen(bfScreen, nScreenWidth * nScreenHeight);
                            this_thread::sleep_for(10000ms);
                        }*/
                        units[a]->setTarget(units[units[a]->getTargetUnit()]->fX, units[units[a]->getTargetUnit()]->fY);

                        if (cDistance(units[a]->fX, units[a]->fY, units[a]->fTargetX, units[a]->fTargetY) < units[a]->fAttackRange)
                        {
                            units[a]->attack(units[units[a]->getTargetUnit()]);
                        }
                    }
                    else
                    {
                        // Small guards, activate them if you think TargetUnits are getting out of range.
                        /*if ((int)units.size() >= 1 && (units[a]->getTargetUnit() > (int)units.size() || units[a]->getTargetUnit() < -1))
                        {
                            int leng;
                            leng = snprintf(NULL, 0, "Unit Target %i: %i", unitIndex, units[unitIndex]->getTargetUnit());
                            swprintf_s(&bfScreen[nScreenWidth * 8], leng + 1, L"Unit Target %i: %i", unitIndex, units[unitIndex]->getTargetUnit());
                            leng = snprintf(NULL, 0, "Units Size: %i", (int)units.size());
                            swprintf_s(&bfScreen[nScreenWidth * 9], leng + 1, L"Units Size: %i", (int)units.size());
                            writeToScreen(bfScreen, nScreenWidth * nScreenHeight);
                            this_thread::sleep_for(10000ms);
                        }*/
                        if (units[a]->getTargetBuilding() >= 0 && units[a]->getTargetBuilding() < (int)buildings.size())
                        {
                            units[a]->setTarget(buildings[units[a]->getTargetBuilding()]->fX, buildings[units[a]->getTargetBuilding()]->fY);

                            if (cDistance(units[a]->fX, units[a]->fY, units[a]->fTargetX, units[a]->fTargetY) < units[a]->fAttackRange)
                            {
                                units[a]->attack(buildings[units[a]->getTargetBuilding()]);
                            }
                        }
                        else
                        {
                            for (int b = 0; b < (int)buildings.size(); b++)
                            {
                                if (units[a]->getTeam() != buildings[b]->getTeam())
                                {
                                    if (cDistance(units[a]->fX, units[a]->fY, buildings[b]->fX, buildings[b]->fY) < units[a]->fAttackDistance && units[a]->getTargetBuilding() == -1)
                                    {
                                        units[a]->setTargetBuilding(b);
                                    }
                                }
                            }
                        }
                    }
                }

                
                bool bUnitKilled = true;
                while (bUnitKilled)
                {
                    bUnitKilled = false;
                    for (int a = 0; a < (int)units.size(); a++)
                    {
                        if (units[a]->nHealth <= 0)
                        {
                            bUnitKilled = true;
                            delete units[a];
                            units.erase(units.begin() + a);
                            for (int b = 0; b < (int)units.size(); b++)
                            {
                                if (units[b]->getTargetUnit() == a)
                                    units[b]->setTargetUnit(-1);
                                else if (units[b]->getTargetUnit() > a)
                                    units[b]->setTargetUnit(units[b]->getTargetUnit() - 1);
                            }
                            break;
                        }
                    }                      
                }
                
            }

            bool bBuildingDestroyed = true;
            while (bBuildingDestroyed)
            {
                bBuildingDestroyed = false;

                for (int a = 0; a < (int)buildings.size(); a++)
                {
                    if (buildings[a]->getHealth() <= 0)
                    {
                        bBuildingDestroyed = true;
                        for (int b = 0; b < (int)units.size(); b++)
                        {
                            if (units[b]->getTargetBuilding() == a) units[b]->setTargetBuilding(-1);
                        }
                        delete buildings[a];
                        buildings.erase(buildings.begin() + a);
                        break;
                    }
                }
                    

            }



            // RENDER OUTPUT ============================================

            // clear screen
            for (int i = 0; i < nScreenWidth * nScreenHeight; i++) bfScreen[i] = ' ';

            fVerticalTilesInScreen = (float)nScreenHeight / (float)nTileSize;
            fHorizontalTilesInScreen = (float)nScreenWidth / (float)nTileSize;

            // Draw grid

            if (bShowGrid)
            {
                for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
                {
                    float fPixelX = (float)(i % nScreenWidth) / nTileSize - (fHorizontalTilesInScreen / 2) + fCameraX;
                    float fPixelY = (float)(i / nScreenWidth) / nTileSize - (fVerticalTilesInScreen / 2) + fCameraY;
                    float fRemainderX = fmod(fPixelX, 1.0);
                    float fRemainderY = fmod(fPixelY, 1.0);
                    if (fRemainderX < 0) fRemainderX += 1;
                    if (fRemainderY < 0) fRemainderY += 1;
                    if (fRemainderX >= 0 && fRemainderX < (1.0 / (float)nTileSize)) bfScreen[i] = 0x2588;
                    if (fRemainderY >= 0 && fRemainderY < (1.0 / (float)nTileSize)) bfScreen[i] = 0x2588;
                }
            }

            fScale = (float)nTileSize / (float)16;

            // Calculate screen coordinates

            float fScreenLeftBorder = fCameraX - (fHorizontalTilesInScreen / 2);
            float fScreenRightBorder = fCameraX + (fHorizontalTilesInScreen / 2);
            float fScreenTopBorder = fCameraY - (fVerticalTilesInScreen / 2);
            float fScreenBottomBorder = fCameraY + (fVerticalTilesInScreen / 2);


            for (int a = 0; a < (int)units.size(); a++)
            {
                if ((units[a]->fX > fScreenLeftBorder && units[a]->fX < fScreenRightBorder) && (units[a]->fY > fScreenTopBorder && units[a]->fY < fScreenBottomBorder))
                {
                    int enemyScreenLocationX = (units[a]->fX - fCameraX) * nTileSize + (fHorizontalTilesInScreen / 2) * nTileSize;
                    int enemyScreenLocationY = (units[a]->fY - fCameraY) * nTileSize + (fVerticalTilesInScreen / 2) * nTileSize;

                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(units[a]->sprite, (int)(units[a]->sprite.nSize * fScale)));
                }
            }

            for (int a = 0; a < (int)buildings.size(); a++)
            {
                if ((buildings[a]->fX > fScreenLeftBorder && buildings[a]->fX < fScreenRightBorder) && (buildings[a]->fY > fScreenTopBorder && buildings[a]->fY < fScreenBottomBorder))
                {
                    int enemyScreenLocationX = (buildings[a]->fX - fCameraX) * nTileSize + (fHorizontalTilesInScreen / 2) * nTileSize;
                    int enemyScreenLocationY = (buildings[a]->fY - fCameraY) * nTileSize + (fVerticalTilesInScreen / 2) * nTileSize;

                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(buildings[a]->sprite, (int)(buildings[a]->sprite.nSize * fScale)));
                }
            }
            
            // Print Info

            int len = snprintf(NULL, 0, "Camera X: %.1f", fCameraX);
            swprintf_s(&bfScreen[0], len+1, L"Camera X: %.1f", fCameraX);
            len = snprintf(NULL, 0, "Camera Y: %.1f", fCameraY);
            swprintf_s(&bfScreen[nScreenWidth], len+1, L"Camera Y: %.1f", fCameraY);
            len = snprintf(NULL, 0, "Tile Size: %i", nTileSize);
            swprintf_s(&bfScreen[nScreenWidth * 2], len + 1, L"Tile Size: %i", nTileSize);
            len = snprintf(NULL, 0, "Entities: %i", (int)units.size());
            swprintf_s(&bfScreen[nScreenWidth * 3], len + 1, L"Entities: %i", (int)units.size());
            if (infoIndex == 0)
            {
                for(int a = 0; a < (int)buildings.size(); a++)
                {
                    len = snprintf(NULL, 0, "Fortress %i HP: %i", buildings[a]->getTeam(), buildings[a]->getHealth());
                    swprintf_s(&bfScreen[nScreenWidth * (4 + a)], len + 1, L"Fortress %i HP: %i", buildings[a]->getTeam(), buildings[a]->getHealth());
                }
            }
            else
            {
                for (int i = 1; i < 5; i++)
                {
                    int teamUnits = 0;
                    for (int a = 0; a < (int)units.size(); a++)
                    {
                        if (units[a]->getTeam() == i) teamUnits++;
                    }
                    len = snprintf(NULL, 0, "Team %i Units: %i", i, teamUnits);
                    swprintf_s(&bfScreen[nScreenWidth * (4 + i - 1)], len + 1, L"Team %i Units: %i", i, teamUnits);
                }
            }
            
            writeToScreen(bfScreen, nScreenWidth * nScreenHeight);
        }

        return 0;
    }

private:

    // Generate Base Map

    void createMap()
    {
        buildings.push_back(new Fortress());
        buildings[0]->setCoords(16, 0);
        buildings[0]->setTeam(1);
        buildings.push_back(new Fortress());
        buildings[1]->setCoords(0, 16);
        buildings[1]->setTeam(2);
        buildings.push_back(new Fortress());
        buildings[2]->setCoords(16, 32);
        buildings[2]->setTeam(3);
        buildings.push_back(new Fortress());
        buildings[3]->setCoords(32, 16);
        buildings[3]->setTeam(4);
    }

protected:

    Sprite sprites[2];
    vector<Unit*> units;
    vector<Building*> buildings;

};

int main()
{
    Caelis_Chaos game;
    game.start();

    return 0;
}