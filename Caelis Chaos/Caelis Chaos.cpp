/*
Caelis Chaos development build

Version 0.1c

Copyright (c) Tobias Bersia

All rights reserved.
*/

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <map>
#include <enet/enet.h>
#include "TobiGameEngine/TobiGameEngine.h"
#include "TobiGameEngine/RTS-utilities/Sprite.h"
#include "TobiGameEngine/RTS-utilities/Unit.h"
#include "TobiGameEngine/RTS-utilities/Building.h"
#include "TobiGameEngine/RTS-utilities/Player.h"

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

        teamColors[0] = 0x0001;
        teamColors[1] = 0x0004;
        teamColors[2] = 0x000B;
        teamColors[3] = 0x0006;
    }

private:

    Sprite sprites[2];
    unordered_map<int, Unit*> units;
    unordered_map<int, Building*> buildings;
    vector<Player*> players;

    bool bGameOver = false;
    bool bKey[10];
    bool bHoldKey[10] = { false };
    bool bShowGrid = true;

    Player* currentPlayer;

    int nMoveTimer = 0;
    int nEntities = 0;

    float fScreenRatio = (float)nScreenWidth / (float)nScreenHeight;
    int nTileSize = 16;
    float fVerticalTilesInScreen = (float)nScreenHeight / (float)nTileSize;
    float fHorizontalTilesInScreen = (float)nScreenWidth / (float)nTileSize;
    float fScale = 1;
    int infoIndex = 0;

    int waveTimer = 0;
    int teamColors[4];

public:

    virtual void Settings()
    {
        setGameTick(5);
    }

    virtual void Create()
    {
        createConsole(L"Caelis Chaos", nScreenWidth, nScreenHeight, 7, 7);
        setCursorVisibility(false);
        createMap();
        createPlayers();
        currentPlayer = players[0];
    }

    virtual void Update(float fElapsedTime)
    {      
            // INPUT ============================================

            for (int k = 0; k < 10; k++)
                bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x26ZXCGDS"[k]))) != 0;

            // CAMERA MOVEMENT

            if (bKey[0]) currentPlayer->setCamera(currentPlayer->getCameraX() + (0.3f / fScale), currentPlayer->getCameraY());
            if (bKey[1]) currentPlayer->setCamera(currentPlayer->getCameraX() + (-0.3f / fScale), currentPlayer->getCameraY());
            if (bKey[2]) currentPlayer->setCamera(currentPlayer->getCameraX(), currentPlayer->getCameraY() + (0.3f / fScale));
            if (bKey[3]) currentPlayer->setCamera(currentPlayer->getCameraX(), currentPlayer->getCameraY() + (-0.3f / fScale));

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
                    //units.push_back(new Footman());
                    //units.back()->setTarget(rand() % 20 - 10, rand() % 50 - 25);
                    //units.back()->setTeam(currentPlayer->getTeam());
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

            if (bKey[9])
            {
                if (!bHoldKey[9])
                {
                    if (currentPlayer->getTeam() < 4) currentPlayer = players[currentPlayer->getTeam()];
                    else currentPlayer = players[0];
                };
                bHoldKey[9] = true;
            }
            else
                bHoldKey[9] = false;

            // GAME LOGIC ============================================

            waveTimer++;

            if (units.size() < 200 && waveTimer % 300 == 0)
            {
                for (int i = 0; i < (int)players.size(); i++)
                {
                    for (int a = 0; a < (int)players[i]->teamBuildings.size(); a++)
                    { 
                        vector<Unit*> wave;
                        wave.push_back(new Footman());
                        wave.push_back(new Footman());
                        wave.push_back(new Footman());

                        // Unbalanced on purpose for testing reasons
                        if (players[i]->getTeam() == 2)
                            wave.push_back(new Knight());

                        wave = players[i]->teamBuildings[a]->spawnWave(wave);

                        if (players[i]->getTeam() == 4)
                        {
                            for (int b = 0; b < (int)wave.size(); b++)
                            {
                                wave[b]->setHealth(200);
                                wave[b]->setAttack(12);
                                wave[b]->setAttackSpeed(2);
                            }
                        }

                        for (int b = 0; b < (int)wave.size(); b++)
                        {
                            int ID = createEntity(wave[b]);
                            players[wave[b]->getTeam() - 1]->teamUnits.push_back(wave[b]);
                            units[ID] = wave[b];
                        }
                            
                            

                    }
                }



            }

            // UNIT AI

            if (units.size() >= 1)
            {

                for (auto& unit : units)
                {
                    if (unit.second->fX != unit.second->fTargetX || unit.second->fY != unit.second->fTargetY)
                        unit.second->move(unit.second->fTargetX, unit.second->fTargetY);

                    for (auto& unit2 : units)
                    {
                        if (unit.second->getID() != unit2.second->getID())
                        {
                            if (cDistance(unit.second->fX, unit.second->fY, unit2.second->fX, unit2.second->fY) < unit.second->fAttackDistance && unit.second->getTeam() != unit2.second->getTeam() && unit.second->getTargetUnit() == -1)
                            {
                                unit.second->setTargetUnit(unit2.second->getID());
                            }
                        }
                    }

                    //if (units[a]->getTargetUnit() >= 0 && units[a]->getTargetUnit() < (int)units.size())
                    if (unit.second->getTargetUnit() != -1)
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
                        unit.second->setTarget(units[unit.second->getTargetUnit()]->fX, units[unit.second->getTargetUnit()]->fY);

                        if (cDistance(unit.second->fX, unit.second->fY, unit.second->fTargetX, unit.second->fTargetY) < unit.second->fAttackRange)
                        {
                            unit.second->attack(units[unit.second->getTargetUnit()]);
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
                        if (unit.second->getTargetBuilding() >= 0 && unit.second->getTargetBuilding() < (int)buildings.size())
                        {
                            unit.second->setTarget(buildings[unit.second->getTargetBuilding()]->fX, buildings[unit.second->getTargetBuilding()]->fY);

                            if (cDistance(unit.second->fX, unit.second->fY, unit.second->fTargetX, unit.second->fTargetY) < unit.second->fAttackRange)
                            {
                                unit.second->attack(buildings[unit.second->getTargetBuilding()]);
                            }
                        }
                        else
                        {
                            for (auto& building : buildings)
                            {
                                if (unit.second->getTeam() != building.second->getTeam())
                                {
                                    if (cDistance(unit.second->fX, unit.second->fY, building.second->fX, building.second->fY) < unit.second->fAttackDistance && unit.second->getTargetBuilding() == -1)
                                    {
                                        unit.second->setTargetBuilding(building.second->getID());
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
                    for (auto& unit : units)
                    {
                        if (unit.second->nHealth <= 0)
                        {
                            bUnitKilled = true;
                            for (auto& unit2 : units)
                            {
                                if (unit2.second->getTargetUnit() == unit.second->getID())
                                    unit2.second->setTargetUnit(-1);
                            }
                            destroyEntity(unit.second->getID());
                            break;
                        }
                    }
                }

            }

            bool bBuildingDestroyed = true;
            while (bBuildingDestroyed)
            {
                bBuildingDestroyed = false;

                for (auto& building : buildings)
                {
                    if (building.second->getHealth() <= 0)
                    {
                        bBuildingDestroyed = true;
                        for (auto& unit : units)
                        {
                            if (unit.second->getTargetBuilding() == building.second->getID()) unit.second->setTargetBuilding(-1);
                        }
                        destroyEntity(building.second->getID());
                        break;
                    }
                }


            }
    }

    virtual void Render()
    {
        // RENDER OUTPUT ============================================

        // clear screen
        for (int i = 0; i < nScreenWidth * nScreenHeight; i++) 
        { 
            bfScreen[i].Char.UnicodeChar = '#';
            bfScreen[i].Attributes = 0x0002;
        }

        fVerticalTilesInScreen = (float)nScreenHeight / (float)nTileSize;
        fHorizontalTilesInScreen = (float)nScreenWidth / (float)nTileSize;

        // Draw grid

        if (bShowGrid)
        {
            for (int i = 0; i < nScreenWidth; i++)
            {
                float fPixelX = (float)i / nTileSize - (fHorizontalTilesInScreen / 2) + currentPlayer->getCameraX();
                float fRemainderX = fPixelX - (int)fPixelX;
                if (fRemainderX < 0) fRemainderX += 1;
                if (fRemainderX >= 0 && fRemainderX < (1.0 / (float)nTileSize))
                {
                    for (int x = 0; x < nScreenHeight; x++)
                    {
                        bfScreen[x * nScreenWidth + i].Char.UnicodeChar = 0x2588;
                        //bfScreen[x * nScreenWidth + i].Attributes = 0x000F;
                    }
                    
                }
            }
            for (int i = 0; i < nScreenHeight; i++)
            {
                float fPixelY = (float)i / nTileSize - (fVerticalTilesInScreen / 2) + currentPlayer->getCameraY();
                float fRemainderY = fPixelY - (int)fPixelY;
                if (fRemainderY < 0) fRemainderY += 1;
                if (fRemainderY >= 0 && fRemainderY < (1.0 / (float)nTileSize))
                {
                    for (int y = 0; y < nScreenWidth; y++)
                    {
                        bfScreen[y + i * nScreenWidth].Char.UnicodeChar = 0x2588;
                        //bfScreen[y + i * nScreenWidth].Attributes = 0x000F;
                    }
                }
            }
            
        }

        fScale = (float)nTileSize / (float)16;

        // Calculate screen coordinates

        float fScreenLeftBorder = currentPlayer->getCameraX() - (fHorizontalTilesInScreen / 2);
        float fScreenRightBorder = currentPlayer->getCameraX() + (fHorizontalTilesInScreen / 2);
        float fScreenTopBorder = currentPlayer->getCameraY() - (fVerticalTilesInScreen / 2);
        float fScreenBottomBorder = currentPlayer->getCameraY() + (fVerticalTilesInScreen / 2);


        /*for (int a = 0; a < (int)units.size(); a++)
        {
            if ((units[a]->fX > fScreenLeftBorder && units[a]->fX < fScreenRightBorder) && (units[a]->fY > fScreenTopBorder && units[a]->fY < fScreenBottomBorder))
            {
                int enemyScreenLocationX = (units[a]->fX - currentPlayer->getCameraX()) * nTileSize + (fHorizontalTilesInScreen / 2) * nTileSize;
                int enemyScreenLocationY = (units[a]->fY - currentPlayer->getCameraY()) * nTileSize + (fVerticalTilesInScreen / 2) * nTileSize;

                if(units[a]->getTeam() == 1)
                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(units[a]->sprite, (int)(units[a]->sprite.nSize * fScale)), 0x0001);
                else if (units[a]->getTeam() == 2)
                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(units[a]->sprite, (int)(units[a]->sprite.nSize * fScale)), 0x0004);
                else if (units[a]->getTeam() == 3)
                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(units[a]->sprite, (int)(units[a]->sprite.nSize * fScale)), 0x000B);
                else if (units[a]->getTeam() == 4)
                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(units[a]->sprite, (int)(units[a]->sprite.nSize * fScale)), 0x0006);
            }
        }

        for (int a = 0; a < (int)buildings.size(); a++)
        {
            if ((buildings[a]->fX > fScreenLeftBorder && buildings[a]->fX < fScreenRightBorder) && (buildings[a]->fY > fScreenTopBorder && buildings[a]->fY < fScreenBottomBorder))
            {
                int enemyScreenLocationX = (buildings[a]->fX - currentPlayer->getCameraX()) * nTileSize + (fHorizontalTilesInScreen / 2) * nTileSize;
                int enemyScreenLocationY = (buildings[a]->fY - currentPlayer->getCameraY()) * nTileSize + (fVerticalTilesInScreen / 2) * nTileSize;

                if (buildings[a]->getTeam() == 1)
                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(buildings[a]->sprite, (int)(buildings[a]->sprite.nSize * fScale)), 0x0001);
                else if (buildings[a]->getTeam() == 2)
                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(buildings[a]->sprite, (int)(buildings[a]->sprite.nSize * fScale)), 0x0004);
                else if (buildings[a]->getTeam() == 3)
                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(buildings[a]->sprite, (int)(buildings[a]->sprite.nSize * fScale)), 0x000B);
                else if (buildings[a]->getTeam() == 4)
                    drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(buildings[a]->sprite, (int)(buildings[a]->sprite.nSize * fScale)), 0x0006);
            }
        }*/

        for (auto& entity : entityList)
        {
            if ((entity.second->fX > fScreenLeftBorder && entity.second->fX < fScreenRightBorder) && (entity.second->fY > fScreenTopBorder && entity.second->fY < fScreenBottomBorder))
            {
                int enemyScreenLocationX = (entity.second->fX - currentPlayer->getCameraX()) * nTileSize + (fHorizontalTilesInScreen / 2) * nTileSize;
                int enemyScreenLocationY = (entity.second->fY - currentPlayer->getCameraY()) * nTileSize + (fVerticalTilesInScreen / 2) * nTileSize;

                drawSprite(enemyScreenLocationX, enemyScreenLocationY, scaleSprite(entity.second->sprite, (int)(entity.second->sprite.nSize * fScale)), teamColors[entity.second->getTeam()-1]);

            }
        }

        // Print Info
        /*
        int len = snprintf(NULL, 0, "Camera X: %.1f", fCameraX);
        swprintf_s(&bfScreen[0].Char.UnicodeChar, len + 1, L"Camera X: %.1f", fCameraX);
        len = snprintf(NULL, 0, "Camera Y: %.1f", fCameraY);
        swprintf_s(&bfScreen[nScreenWidth].Char.UnicodeChar, len + 1, L"Camera Y: %.1f", fCameraY);
        len = snprintf(NULL, 0, "Tile Size: %i", nTileSize);
        swprintf_s(&bfScreen[nScreenWidth * 2].Char.UnicodeChar, len + 1, L"Tile Size: %i", nTileSize);
        len = snprintf(NULL, 0, "Entities: %i", (int)units.size());
        swprintf_s(&bfScreen[nScreenWidth * 3].Char.UnicodeChar, len + 1, L"Entities: %i", (int)units.size());
        if (infoIndex == 0)
        {
            for (int a = 0; a < (int)buildings.size(); a++)
            {
                len = snprintf(NULL, 0, "Fortress %i HP: %i", buildings[a]->getTeam(), buildings[a]->getHealth());
                swprintf_s(&bfScreen[nScreenWidth * (4 + a)].Char.UnicodeChar, len + 1, L"Fortress %i HP: %i", buildings[a]->getTeam(), buildings[a]->getHealth());
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
                swprintf_s(&bfScreen[nScreenWidth * (4 + i - 1)].Char.UnicodeChar, len + 1, L"Team %i Units: %i", i, teamUnits);
            }
        }*/
    }

private:

    // Generate Base Map

    void createMap()
    {
        Fortress* Fortress1 = new Fortress();
        int fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(16, 0);
        entityList[fortressID]->setTeam(1);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(0, 16);
        entityList[fortressID]->setTeam(2);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(16, 32);
        entityList[fortressID]->setTeam(3);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(32, 16);
        entityList[fortressID]->setTeam(4);

    }

    void createPlayers()
    {
        players.push_back(new Player());
        players[0]->setCamera(16, 0);
        players[0]->setTeam(1);
        players.push_back(new Player());
        players[1]->setCamera(0, 16);
        players[1]->setTeam(2);
        players.push_back(new Player());
        players[2]->setCamera(16, 32);
        players[2]->setTeam(3);
        players.push_back(new Player());
        players[3]->setCamera(32, 16);
        players[3]->setTeam(4);

        for (int i = 0; i < (int)players.size(); i++)
        {
            for (auto& building : buildings)
                if (building.second->getTeam() == players[i]->getTeam()) players[i]->teamBuildings.push_back(building.second);
        }
    }

    int createEntity(Entity* entity)
    {
        int i = 0;
        while (entityList.find(i) != entityList.end())
        {
            i++;
        }
        entity->setID(i);
        entityList[entity->getID()] = entity;

        return i;
    }

    void destroyEntity(int ID)
    {
        int player = entityList[ID]->getTeam() - 1;
        for (int i = 0; i < (int)players[player]->teamBuildings.size(); i++)
        {
            if (ID == players[player]->teamBuildings[i]->getID()) players[player]->teamBuildings.erase(players[player]->teamBuildings.begin() + i);
        }
        for (int i = 0; i < (int)players[player]->teamUnits.size(); i++)
        {
            if (ID == players[player]->teamUnits[i]->getID()) players[player]->teamUnits.erase(players[player]->teamUnits.begin() + i);
        }
        delete entityList[ID];
        entityList.erase(ID);
        if (units.find(ID) != units.end()) units.erase(ID);
        if (buildings.find(ID) != buildings.end()) buildings.erase(ID);
    }

protected:

};

class ClientData
{
private:
    int m_id;
    string m_username;

public:
    ClientData(int id) : m_id(id) {}

    void SetUsername(string username) { m_username = username; }

    int GetID() { return m_id; }
    string GetUsername() { return m_username; }
};

map<int, ClientData*> client_map;
static int CLIENT_ID = -1;

void SendPacket(ENetPeer* peer, const char* data)
{
    ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}

void BroadcastPacket(ENetHost* server, const char* data)
{
    ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(server, 0, packet);
}

void ParseData(ENetHost* server, int id, byte* data)
{
    cout << "PARSE: " << data << "\n";

    int data_type;
    char* cData = (char*)data;
    sscanf_s(cData, "%d|", &data_type);

    switch (data_type)
    {
        case 1:
        {
            char msg[80];
            sscanf_s(cData, "%*d|%[^\n]", &msg, sizeof(msg));

            char send_data[1024] = { '\0' };
            sprintf_s(send_data, "1|%d|%s", id, msg);
            BroadcastPacket(server, send_data);
            break;
        }
        case 2:
        {
            char username[80];
            sscanf_s(cData, "2|%[^\n]", &username, sizeof(username));

            char send_data[1024] = { '\0' };
            sprintf_s(send_data, "2|%d|%s", id, username);

            BroadcastPacket(server, send_data);
            client_map[id]->SetUsername(username);

            break;
        }
    }
}

void ParseDataClient(byte* data)
{
    int data_type;
    int id;
    char* cData = (char*)data;
    sscanf_s(cData, "%d|%d", &data_type, &id);

    switch (data_type)
    {
    case 1:
        if (id != CLIENT_ID)
        {
            char msg[80];
            sscanf_s(cData, "%*d|%*d|%[^|]", &msg, sizeof(msg));
            cout << client_map[id]->GetUsername().c_str() << ": " << msg << endl;
        }
        break;

    case 2:
        if (id != CLIENT_ID)
        {
            char username[80];
            sscanf_s(cData, "%*d|%*d|%[^|]", &username, sizeof(username));

            client_map[id] = new ClientData(id);
            client_map[id]->SetUsername(username);
        }
        break;

    case 3:
        CLIENT_ID = id;
        break;
    }
}

void* MsgLoop(ENetHost* client)
{
    while (true)
    {
        ENetEvent event;
        while (enet_host_service(client, &event, 0) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:

                ParseDataClient(event.packet->data);
                enet_packet_destroy(event.packet);

                break;
            }
        }
    }
}

int main()
{
    //Caelis_Chaos game;
    //game.Start();

    bool client = false;
    bool server = false;
    char option;

    cout << "Start server(s) or client(c)?" << endl;
    cin >> option;

    if (option == 'c') client = true;
    else if (option == 's') server = true;

    if (client)
    {
        printf("Please enter your username?\n");
        char username[80];
        cin >> username;
        cin.ignore();

        const char* ip = "181.44.58.132";

        if (enet_initialize() != 0)
        {
            fprintf(stderr, "An error occurred while initializing ENet!\n");
            return EXIT_FAILURE;
        }
        atexit(enet_deinitialize);

        ENetHost* client;
        client = enet_host_create(NULL, 1, 1, 0, 0);

        if (client == NULL)
        {
            fprintf(stderr, "An error occurred while trying to create an ENet client host!\n");
            return EXIT_FAILURE;
        }
        ENetAddress address;
        ENetEvent event;
        ENetPeer* peer;

        enet_address_set_host(&address, ip);
        address.port = 7777;

        peer = enet_host_connect(client, &address, 1, 0);
        if (peer == NULL)
        {
            fprintf(stderr, "No available peers for initiating an ENet connection\n");
            return EXIT_FAILURE;
        }

        if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
        {
            puts("Connection to 181.44.58.132 succeeded.");
        }
        else
        {
            enet_peer_reset(peer);
            puts("Connection to 181.44.58.132 failed.");
            return EXIT_SUCCESS;
        }

        // Send the server the user's username
        char str_data[80] = "2|";
        strcat_s(str_data, username);
        SendPacket(peer, str_data);

        // GAME LOOP START

        bool running = true;

        thread chatThread(MsgLoop, client);

        while (running)
        {
            string content;
            getline(cin, content);
            char message_data[80] = "1|";
            strcat_s(message_data, content.c_str());
            SendPacket(peer, message_data);
            content = "";
        }

        // GAME LOOP END

        chatThread.join();

        enet_peer_disconnect(peer, 0);

        while (enet_host_service(client, &event, 3000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");
                break;
            }
        }

        return EXIT_SUCCESS;
    }

    if (server)
    {
        if (enet_initialize() != 0)
        {
            fprintf(stderr, "An error occurred while initializing ENet!\n");
            return EXIT_FAILURE;
        }
        atexit(enet_deinitialize);

        ENetAddress address;
        ENetHost* server;
        ENetEvent event;

        address.host = ENET_HOST_ANY;
        address.port = 7777;

        server = enet_host_create(&address, 4, 1, 0, 0);

        if (server == NULL)
        {
            fprintf(stderr, "An error occurred while trying to create an ENet server host!\n");
            return EXIT_FAILURE;
        }

        // GAME LOOP START

        int new_player_id = 0;

        while (true)
        {
            while (enet_host_service(server, &event, 1000) > 0)
            {
                switch (event.type)
                {
                    case ENET_EVENT_TYPE_CONNECT:
                    {
                        printf("A new client connected from %x:%u.\n",
                            event.peer->address.host,
                            event.peer->address.port);

                        for (auto const& x : client_map)
                        {
                            char send_data[1024] = { '\0' };
                            sprintf_s(send_data, "2|%d|%s", x.first, x.second->GetUsername().c_str());
                            BroadcastPacket(server, send_data);
                        }

                        new_player_id++;
                        client_map[new_player_id] = new ClientData(new_player_id);
                        event.peer->data = client_map[new_player_id];

                        char data_to_send[126] = { '\0' };
                        sprintf_s(data_to_send, "3|%d", new_player_id);
                        SendPacket(event.peer, data_to_send);

                        break;
                    }
                    case ENET_EVENT_TYPE_RECEIVE:
                    {
                        printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
                            event.packet->dataLength,
                            event.packet->data,
                            event.peer->address.host,
                            event.peer->address.port,
                            event.channelID);

                        ParseData(server, static_cast<ClientData*>(event.peer->data)->GetID(), event.packet->data);
                        enet_packet_destroy(event.packet);
                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT:
                    {
                        printf("%x:%u disconnected.\n",
                            event.peer->address.host,
                            event.peer->address.port);

                        char disconnected_data[126] = { '\0' };
                        sprintf_s(disconnected_data, "4|%d", static_cast<ClientData*>(event.peer->data)->GetID());
                        BroadcastPacket(server, disconnected_data);


                        event.peer->data = NULL;
                        break;
                    }
                }
            }
        }

        // GAME LOOP END

        enet_host_destroy(server);

        return EXIT_SUCCESS;
    }

    return 0;
}