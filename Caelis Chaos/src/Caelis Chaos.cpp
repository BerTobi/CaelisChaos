#ifndef CAELISCHAOS_H
#define CAELISCHAOS_H

/*
Caelis Chaos

Version 0.3.0 - Release Candidate 1

Copyright (c) Tobias Bersia

All rights reserved.
*/

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <map>
#include <functional>
#include <queue>
#include <enet/enet.h>
#include "TobiGameEngine/TobiGameEngine.h"
#include "TobiGameEngine/RTS-utilities/Sprite.h"
#include "TobiGameEngine/RTS-utilities/Unit.h"
#include "TobiGameEngine/RTS-utilities/Building.h"
#include "TobiGameEngine/RTS-utilities/Player.h"
#include "TobiGameEngine/RTS-utilities/Projectile.h"

using namespace std;

class Arrow : public Projectile
{
public:
    Arrow()
    {
        fMovementSpeed = 0.3;
        sName = "Arrow";

        pSprite = "res/textures/Arrow.png";
        fWidth = 0.3f;
        fHeight = 0.2f;

    }
};

class Fireball : public Projectile
{
public:
    Fireball()
    {
        fMovementSpeed = 0.2;
        fSplashArea = 0.5f;
        sName = "Fireball";

        Sprite fireballSprite;

        pSprite = "res/textures/Fireball.png";
        fWidth = 0.3f;
        fHeight = 0.3f;
    }
};

class Cannonball : public Projectile
{
public:
    Cannonball()
    {
        fMovementSpeed = 0.4;
        fSplashArea = 1.0f;
        sName = "Cannonball";

        pSprite = "res/textures/Cannonball.png";
        fWidth = 0.3f;
        fHeight = 0.3f;
    }
};

class BulletMG : public Projectile
{
public:
    BulletMG()
    {
        fMovementSpeed = 0.5;
        sName = "BulletMG";

        pSprite = "res/textures/Bullet.png";
        fWidth = 0.1f;
        fHeight = 0.1f;
    }
};

class Footman : public Unit
{
public:
    Footman()
    {
        nHealth = 150;
        nMaxHealth = 150;
        fMovementSpeed = 0.0375;
        nAttack = 15;
        nAttackSpeed = 1000;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 0.5f;
        fAttackDistance = 3;
        sName = "Footman";
        nArmour = 20;

        nKillReward = 25;
        nTrainingCost = 100;

        pSprite = "res/textures/Footman.png";
        fWidth = 1;
        fHeight = 1;
    }
};

class Knight : public Unit
{
public:
    Knight()
    {
        nHealth = 1500;
        nMaxHealth = 1500;
        fMovementSpeed = 0.0375;
        nAttack = 50;
        nAttackSpeed = 2000;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 0.5f;
        fAttackDistance = 4;
        sName = "Knight";
        nArmour = 30;

        nKillReward = 150;
        nTrainingCost = 1000;

        pSprite = "res/textures/Knight.png";
        fWidth = 1.5f;
        fHeight = 1.5f;

    }
};

class Mage : public Unit
{
public:
    Mage()
    {
        nHealth = 120;
        nMaxHealth = 120;
        fMovementSpeed = 0.03;
        nAttack = 50;
        nAttackSpeed = 500;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 3.5;
        fAttackDistance = 5;
        sName = "Mage";
        sProjectile = "Fireball";
        nArmour = 0;
        fSplashArea = 0.5f;

        nKillReward = 100;
        nTrainingCost = 600;

        pSprite = "res/textures/Mage.png";
        fWidth = 1;
        fHeight = 1;
    }
};

class Archer : public Unit
{
public:
    Archer()
    {
        nHealth = 80;
        nMaxHealth = 80;
        fMovementSpeed = 0.03375;
        nAttack = 10;
        nAttackSpeed = 1000;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 2.5;
        fAttackDistance = 5;
        sName = "Archer";
        sProjectile = "Arrow";
        nArmour = 10;

        nKillReward = 50;
        nTrainingCost = 200;

        pSprite = "res/textures/Archer.png";
        fWidth = 1;
        fHeight = 1;
    }
};

class Tremendinius : public Unit
{
public:
    Tremendinius()
    {
        nHealth = 10000;
        nMaxHealth = 10000;
        fMovementSpeed = 0.025;
        nAttack = 1300;
        nAttackSpeed = 500;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 1.0f;
        fAttackDistance = 4;
        sName = "Tremendinius";
        nArmour = 50;

        nKillReward = 500;
        nTrainingCost = 4000;

        pSprite = "res/textures/Tremendinius.png";
        fWidth = 2.5f;
        fHeight = 2.5f;
    }
};

class BigBird : public Unit
{
public:
    BigBird()
    {
        nHealth = 700;
        nMaxHealth = 700;
        fMovementSpeed = 0.04;
        nAttack = 50;
        nAttackSpeed = 1500;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 0.5f;
        fAttackDistance = 4;
        sName = "BigBird";
        nArmour = 0;

        nKillReward = 35;
        nTrainingCost = 350;

        pSprite = "res/textures/BigBird.png";
        fWidth = 1;
        fHeight = 1;
    }
};

class Cannon : public Unit
{
public:
    Cannon()
    {
        nHealth = 200;
        nMaxHealth = 200;
        fMovementSpeed = 0.025;
        nAttack = 270;
        nAttackSpeed = 333;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 4.5;
        fAttackDistance = 6;
        sName = "Cannon";
        sProjectile = "Cannonball";
        nArmour = 10;
        fSplashArea = 1.0f;


        nKillReward = 150;
        nTrainingCost = 1000;

        pSprite = "res/textures/Cannon.png";
        fWidth = 1.4f;
        fHeight = 1.4f;
    }
};

class Minigun : public Unit
{
public:
    Minigun()
    {
        nHealth = 3000;
        nMaxHealth = 3000;
        fMovementSpeed = 0.02;
        nAttack = 15;
        nAttackSpeed = 30000;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 4;
        fAttackDistance = 5.5;
        sName = "Minigun";
        sProjectile = "BulletMG";
        nArmour = 20;


        nKillReward = 500;
        nTrainingCost = 4000;

        pSprite = "res/textures/Minigun.png";
        fWidth = 2;
        fHeight = 2;
    }
};

class Fortress : public Building
{
public:

    string pSprites[3];

    Fortress()
    {
        nHealth = 2000;
        nMaxHealth = 2000;
        nLevel = 1;
        sName = "Fortress";
        pSprite = "res/textures/FortressLevel_1.png";
        fHeight = 3;
        fWidth = 3;
        nKillReward = 1000;

        pSprites[0] = "res/textures/FortressLevel_1.png";
        pSprites[1] = "res/textures/FortressLevel_2.png";
        pSprites[2] = "res/textures/FortressLevel_3.png";

    }

    void upgrade(Player* player) override {
        if (player->getGold() >= 3000 && nLevel == 1)
        {
            setLevel(2);
            addHealth(1000);
            setMaxHealth(3000);
            player->addGold(-3000);
            player->unlockKnight();
            player->setHealthModifier(1.1f);
            setSprite(pSprites[1]);
        }
        else if (player->getGold() >= 5000 && nLevel == 2)
        {
            setLevel(3);
            addHealth(1500);
            setMaxHealth(4500);
            player->addGold(-5000);
            player->unlockTremendinius();
            player->unlockCannon();
            player->unlockMinigun();
            player->setHealthModifier(1.2f);
            setSprite(pSprites[2]);
        }
    }

};

//class upgrades
//{
//public:
//
//    void passiveGoldUpgrade(Player* player) override {
//        if (player->getGold() >= 3000 && nLevel == 1)
//        {
//            setLevel(2);
//            addHealth(1000);
//            player->addGold(-3000);
//            player->unlockKnight();
//            player->setHealthModifier(1.1f);
//            setSprite(fortressSprite[1]);
//        }
//        else if (player->getGold() >= 5000 && nLevel == 2)
//        {
//            setLevel(3);
//            addHealth(1500);
//            player->addGold(-5000);
//            player->unlockTremendinius();
//            player->setHealthModifier(1.2f);
//            setSprite(fortressSprite[2]);
//        }
//    }
//};

class Barracks : public Building
{
public:

    string pSprites[4];

    Barracks()
    {
        nHealth = 1200;
        nMaxHealth = 1200;
        sName = "Barracks";
        nLevel = 1;
        nKillReward = 500;

        pSprite = "res/textures/BarracksLevel_1.png";
        fHeight = 1.5f;
        fWidth = 1.5f;
        
        pSprites[0] = "res/textures/BarracksLevel_1.png";
        pSprites[1] = "res/textures/BarracksLevel_2.png";
        pSprites[2] = "res/textures/BarracksLevel_3.png";
        pSprites[3] = "res/textures/BarracksLevel_4.png";
    }

    void upgrade(Player* player) override{
        if (player->getGold() >= 2000 && nLevel == 1)
        {
            setLevel(2);
            addHealth(300);
            setMaxHealth(1500);
            player->addGold(-2000);
            setSprite(pSprites[1]);
        }
        else if (player->getGold() >= 3000 && nLevel == 2)
        {
            setLevel(3);
            addHealth(300);
            setMaxHealth(1800);
            player->addGold(-3000);
            setSprite(pSprites[2]);
        }
        else if (player->getGold() >= 4000 && nLevel == 3)
        {
            setLevel(4);
            addHealth(500);
            setMaxHealth(2300);
            player->addGold(-4000);
            setSprite(pSprites[3]);
        }
    }

};

class Tower : public Building
{
public:

    Sprite TowerSprite[1];

    Tower()
    {
        nHealth = 2000;
        nMaxHealth = 2000;
        sName = "Tower";
        sProjectile = "Arrow";
        nLevel = 1;
        nKillReward = 250;

        nAttack = 75;
        nAttackSpeed = 1000;
        nDefaultAttackCooldown = 30000;
        fAttackRange = 6;
        fAttackDistance = 6;

        pSprite = "res/textures/Tower.png";
        fHeight = 2.0f;
        fWidth = 1.5f;
    }

};

class ClientData
{
private:
    int m_id;
    string m_username;
    int m_turn;
    int m_lastAction;
    

public:
    queue<pair<int, int>> m_actionQueue;
    bool m_mapCreated;

    ClientData(int id){
        m_id = id;
        m_turn = 0;
        m_lastAction = 0;
        m_mapCreated = false;
    }

    void SetUsername(string username) { m_username = username; }

    int GetID() { return m_id; }
    string GetUsername() { return m_username; }
    void SetTurn(int turn) { m_turn = turn; }
    int GetTurn() { return m_turn; }
    void SetAction(int action) { m_lastAction = action; }
    int GetAction() { return m_lastAction; }
};

class Caelis_Chaos : public TobiGameEngine
{
public:

    Caelis_Chaos()
    {
        m_sConsoleTitle = L"Caelis Chaos 0.3.0";
        m_nScreenWidth = 1600;
        m_nScreenHeight = 900;

        teamColors[0][0] = { 0, 0, 255, 0 };
        teamColors[0][1] = { 0, 0, 213, 0 };
        teamColors[0][2] = { 0, 0, 166, 0 };
        teamColors[0][3] = { 0, 0, 117, 0 };

        teamColors[1][0] = { 255, 0, 0, 0 };
        teamColors[1][1] = { 213, 0, 0, 0 };
        teamColors[1][2] = { 166, 0, 0, 0 };
        teamColors[1][3] = { 130, 0, 0, 0 };

        teamColors[2][0] = { 12, 241, 249, 0 };
        teamColors[2][1] = { 11, 215, 222, 0 };
        teamColors[2][2] = {  9, 183, 186, 0 };
        teamColors[2][3] = {  8, 153, 156, 0 };

        teamColors[3][0] = { 255, 216, 0, 0 };
        teamColors[3][1] = { 215, 182, 0, 0 };
        teamColors[3][2] = { 176, 148, 0, 0 };
        teamColors[3][3] = { 134, 113, 0, 0 };

        CLIENT_ID = -1;

        pause = false;

    }

private:

    //Match

    Sprite sprites[2];
    unordered_map<int, Unit*> units;
    unordered_map<int, Building*> buildings;
    unordered_map<int, Projectile*> projectiles;
    vector<Player*> players;

    bool bWin = false;
    bool bGameOver = false;
    bool bHoldKey[256] = { false };
    const Uint8* bKey = SDL_GetKeyboardState(NULL);
    bool bShowGrid = true;

    Player* currentPlayer;

    int nMoveTimer = 0;
    int nEntities = 0;

    float fScreenRatio = (float)m_nScreenWidth / (float)m_nScreenHeight;
    int nTileSize = 64;
    float fVerticalTilesInScreen = (float)m_nScreenHeight / (float)nTileSize;
    float fHorizontalTilesInScreen = (float)m_nScreenWidth / (float)nTileSize;
    float fScale = 1;
    int infoIndex = 0;
    int nTicksPerSecond = 30;

    int waveTimer = 0;
    SDL_Color teamColors[4][4];

    int lastAction = 0;

    bool log = false;

    int turn = 0;
    int nextTurn = 0;
    int ticksSinceLastTurn = 0;
    bool turnSent = false;

    bool textInputMode = false;
    string textInput;

    pair<int, int> playerActions[4];
    int randomSeed;
    queue<pair<int, int>> actionQueue;

    bool bDebugMode = false;


// Server attributes

    ENetAddress serverAddress;
    ENetHost* server;
    ENetEvent serverEvent;

    map<int, ClientData*> client_map;
    int CLIENT_ID;

    int new_player_id;
    

// Client attributes

    ENetHost* client;
    ENetAddress clientAddress;
    ENetEvent clientEvent;
    ENetPeer* peer;

    string IP;
    string Username;

public:

    virtual void CreateGUI()
    {
        if (m_nGameState == initializing)
        {
            createWindow("Caelis Chaos 0.3.0 Alpha");
            m_Font = TTF_OpenFont("res/fonts/PixeloidSans-mLxMm.ttf", 50);
            m_nGameState = startMenu;
        }

        if (m_nGameState == startMenu)
        {
            Menus["Start Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Start Menu"]->setPosition(0.3f, 0.2f);
            Menus["Start Menu"]->setSize(0.4f, 0.65f);
            Menus["Start Menu"]->setTableSize(4, 1);
            Menus["Start Menu"]->enable(true);
            if (mLanguage == "English")
            {
                Menus["Start Menu"]->addButton("1 Singleplayer", "Singleplayer");
                Menus["Start Menu"]->addButton("2 Multiplayer", "Multiplayer");
                Menus["Start Menu"]->addButton("3 Settings", "Settings");
                Menus["Start Menu"]->addButton("4 Exit", "Exit");
            }
            else if (mLanguage == "Spanish")
            {
                Menus["Start Menu"]->addButton("1 Singleplayer", "Un jugador");
                Menus["Start Menu"]->addButton("2 Multiplayer", "Multijugador");
                Menus["Start Menu"]->addButton("3 Settings", "Configuracion");
                Menus["Start Menu"]->addButton("4 Exit", "Salir");
            }
        }

        else if (m_nGameState == optionMenu)
        {
            Menus["Configuration Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Configuration Menu"]->setPosition(0.3f, 0.2f);
            Menus["Configuration Menu"]->setSize(0.4f, 0.45f);
            Menus["Configuration Menu"]->setTableSize(3, 1);
            Menus["Configuration Menu"]->enable(true);
            if (mLanguage == "English")
            {
                if (bFullscreen) Menus["Configuration Menu"]->addButton("1 Fullscreen", "Fullscreen");
                else Menus["Configuration Menu"]->addButton("1 Fullscreen", "Windowed");

                Menus["Configuration Menu"]->addButton("2 Resolution", to_string(m_nScreenHeight) + "p");
                Menus["Configuration Menu"]->addButton("3 Language", mLanguage);
                Menus["Configuration Menu"]->addButton("4 Exit", "Exit");
            }
            else if (mLanguage == "Spanish")
            {
                if (bFullscreen) Menus["Configuration Menu"]->addButton("1 Fullscreen", "Pantalla completa");
                else Menus["Configuration Menu"]->addButton("1 Fullscreen", "Ventana");

                Menus["Configuration Menu"]->addButton("2 Resolution", to_string(m_nScreenHeight) + "p");
                Menus["Configuration Menu"]->addButton("3 Language", mLanguage);
                Menus["Configuration Menu"]->addButton("4 Exit", "Salir");
            }
        }
        
        else if (m_nGameState == multiplayerMenu)
        {
            Menus["Multiplayer Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Multiplayer Menu"]->setPosition(0.3f, 0.2f);
            Menus["Multiplayer Menu"]->setSize(0.4f, 0.45f);
            Menus["Multiplayer Menu"]->setTableSize(3, 1);
            Menus["Multiplayer Menu"]->enable(true);
            if (mLanguage == "English")
            {
                Menus["Multiplayer Menu"]->addButton("1 Join", "Join");
                Menus["Multiplayer Menu"]->addButton("2 Host", "Host");
                Menus["Multiplayer Menu"]->addButton("3 Return", "Return");
            }
            else if (mLanguage == "Spanish")
            {
                Menus["Multiplayer Menu"]->addButton("1 Join", "Entrar");
                Menus["Multiplayer Menu"]->addButton("2 Host", "Alojar");
                Menus["Multiplayer Menu"]->addButton("3 Return", "Volver");
            }
        }

        else if (m_nGameState == IPscreen)
        {
            TextBoxes["Title"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Title"]->setPosition(0.25f, 0.1f);
            TextBoxes["Title"]->setSize(0.5f, 0.12f);
            TextBoxes["Title"]->setFontSize(50);
            TextBoxes["Title"]->setTextColor({ 0x00, 0x00, 0x00 });
            TextBoxes["Title"]->showBorder(false);
            TextBoxes["Title"]->setAlignment("CENTERED");
            TextBoxes["Title"]->editable(false);
            if (mLanguage == "English")
            {
                TextBoxes["Title"]->setText("Join Match");
            }
            else if (mLanguage == "Spanish")
            {
                TextBoxes["Title"]->setText("Entrar a la partida");
            }

            TextBoxes["IP"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["IP"]->setPosition(0.25f, 0.4f);
            TextBoxes["IP"]->setSize(0.5f, 0.12f);
            TextBoxes["IP"]->setFontSize(50);
            TextBoxes["IP"]->showBorder(true);
            TextBoxes["IP"]->editable(true);
            TextBoxes["IP"]->setLength(20);
            TextBoxes["IP"]->setAlignment("CENTERED");

            TextBoxes["IP2"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["IP2"]->setPosition(0.15f, 0.4f);
            TextBoxes["IP2"]->setSize(0.1f, 0.12f);
            TextBoxes["IP2"]->setFontSize(50);
            TextBoxes["IP2"]->setTextColor({ 0x00, 0x00, 0x00 });
            TextBoxes["IP2"]->showBorder(false);
            TextBoxes["IP2"]->setText("IP:");

            Menus["IP Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["IP Menu"]->setPosition(0.3f, 0.7f);
            Menus["IP Menu"]->setSize(0.4f, 0.15f);
            Menus["IP Menu"]->setTableSize(1, 2);
            Menus["IP Menu"]->enable(true);
            if (mLanguage == "English")
            {
                Menus["IP Menu"]->addButton("1 Join", "Join");
                Menus["IP Menu"]->addButton("2 Return", "Return");
            }
            else if (mLanguage == "Spanish")
            {
                Menus["IP Menu"]->addButton("1 Join", "Entrar");
                Menus["IP Menu"]->addButton("2 Return", "Volver");
            }
        }

        else if (m_nGameState == usernameInput)
        {
            TextBoxes["Username"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Username"]->setPosition(0.3f, 0.4f);
            TextBoxes["Username"]->setSize(0.4f, 0.1f);
            TextBoxes["Username"]->setFontSize(50);
            TextBoxes["Username"]->showBorder(true);
            TextBoxes["Username"]->editable(true);
            TextBoxes["Username"]->setAlignment("CENTERED");

            TextBoxes["Username2"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Username2"]->setPosition(0.2f, 0.2f);
            TextBoxes["Username2"]->setSize(0.6f, 0.1f);
            TextBoxes["Username2"]->setFontSize(50);
            TextBoxes["Username2"]->setTextColor({0x00, 0x00, 0x00});
            TextBoxes["Username2"]->showBorder(false);
            TextBoxes["Username2"]->setAlignment("CENTERED");
            if (mLanguage == "English")
                TextBoxes["Username2"]->setText("Please enter your username");
            else if (mLanguage == "Spanish")
                TextBoxes["Username2"]->setText("Por favor introduzca su nombre de usuario");

            Menus["Username Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Username Menu"]->setPosition(0.3f, 0.7f);
            Menus["Username Menu"]->setSize(0.4f, 0.15f);
            Menus["Username Menu"]->setTableSize(1, 2);
            Menus["Username Menu"]->enable(true);
            if (mLanguage == "English")
            {
                Menus["Username Menu"]->addButton("1 Join", "Join");
                Menus["Username Menu"]->addButton("2 Return", "Return");
            }
            else if (mLanguage == "Spanish")
            {
                Menus["Username Menu"]->addButton("1 Join", "Entrar");
                Menus["Username Menu"]->addButton("2 Return", "Volver");
            }
        }

        else if (m_nGameState == matchLobby)
        {
            TextBoxes["Title"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Title"]->setPosition(0.25f, 0.05f);
            TextBoxes["Title"]->setSize(0.5f, 0.12f);
            TextBoxes["Title"]->setFontSize(50);
            TextBoxes["Title"]->setTextColor({ 0x00, 0x00, 0x00 });
            TextBoxes["Title"]->showBorder(false);
            TextBoxes["Title"]->setAlignment("CENTERED");
            TextBoxes["Title"]->editable(false);
            if (mLanguage == "English")
            {
                TextBoxes["Title"]->setText("Match Lobby");
            }
            else if (mLanguage == "Spanish")
            {
                TextBoxes["Title"]->setText("Lobby de Partida");
            }

            Lists["Player list"] = new ListUI(m_Renderer, m_Window, m_Font);
            Lists["Player list"]->setPosition(0.05f, 0.25f);
            Lists["Player list"]->setSize(0.4f, 0.3);
            Lists["Player list"]->setFontSize(20);
            Lists["Player list"]->setTextColor({ 0xD4, 0xE9, 0xE2 });
            Lists["Player list"]->setBackgroundColor({ 0x00, 0x62, 0x41 });
            Lists["Player list"]->setTableSize(4, 1);

            for (auto const& x : client_map)
            {
                string name = "Player " + to_string(x.first);
                Lists["Player list"]->addItem(name, name + ": " + x.second->GetUsername());
            }

            Menus["Lobby Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Lobby Menu"]->setPosition(0.3f, 0.7f);
            Menus["Lobby Menu"]->setSize(0.4f, 0.15f);
            Menus["Lobby Menu"]->setTableSize(1, 1);
            Menus["Lobby Menu"]->enable(true);
            if (bServer)
            {
                Menus["Lobby Menu"]->setTableSize(1, 2);
                if (mLanguage == "English")
                {
                    Menus["Lobby Menu"]->addButton("1 Start", "Start");
                }
                else if (mLanguage == "Spanish")
                {
                    Menus["Lobby Menu"]->addButton("1 Start", "Empezar");
                }
            }
            if (mLanguage == "English")
            {
                Menus["Lobby Menu"]->addButton("2 Return", "Return");
            }
            else if (mLanguage == "Spanish")
            {
                Menus["Lobby Menu"]->addButton("2 Return", "Volver");
            }
        }
        
        else if (m_nGameState == inMatch)
        {
            Menus["Barracks"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Barracks"]->setPosition(0.76f, 0.74f);
            Menus["Barracks"]->setSize(0.24f, 0.26f);
            Menus["Barracks"]->setTableSize(3, 3);
            Menus["Barracks"]->enable(false);
            if (mLanguage == "English")
            {
                Menus["Barracks"]->addButton("1 Upgrade Building", "Upgrade");
                Menus["Barracks"]->addButton("2 Train Footman", "Footman");
                Menus["Barracks"]->addButton("3 Train Archer", "Archer");
                Menus["Barracks"]->addButton("4 Train Mage", "Mage");
                Menus["Barracks"]->addButton("5 Train Big Bird", "Big Bird");
                Menus["Barracks"]->addButton("6 Train Cannon", "Cannon");
                Menus["Barracks"]->addButton("7 Train Knight", "Knight");
                Menus["Barracks"]->addButton("8 Train Tremendinius", "Tremendinius");
                Menus["Barracks"]->addButton("9 Train Gatling Gun", "Gatling Gun");
            }
            else if (mLanguage == "Spanish")
            {
                Menus["Barracks"]->addButton("1 Upgrade Building", "Mejorar");
                Menus["Barracks"]->addButton("2 Train Footman", "Soldado");
                Menus["Barracks"]->addButton("3 Train Archer", "Arquera");
                Menus["Barracks"]->addButton("4 Train Mage", "Mago");
                Menus["Barracks"]->addButton("5 Train Big Bird", "Gran Ave");
                Menus["Barracks"]->addButton("6 Train Cannon", "Canon");
                Menus["Barracks"]->addButton("7 Train Knight", "Caballero");
                Menus["Barracks"]->addButton("8 Train Tremendinius", "Tremendinius");
                Menus["Barracks"]->addButton("9 Train Gatling Gun", "Gatling Gun");
            }

            TextBoxes["Gold"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Gold"]->setPosition(0.0f, 0.0f);
            TextBoxes["Gold"]->setSize(0.2f, 0.1f);
            TextBoxes["Gold"]->setFontSize(50);
            TextBoxes["Gold"]->setTextColor({ 0xFF, 0xD7, 0x00 });
            TextBoxes["Gold"]->showBorder(true);
            if (mLanguage == "English")
                TextBoxes["Gold"]->setText("Gold: ");
            else if (mLanguage == "Spanish")
                TextBoxes["Gold"]->setText("Oro: ");

            for (auto& building : buildings)
            {
                building.second->SelectionBox = new Button(m_Renderer, m_Window, m_Font);
                building.second->SelectionBox->setVisibility(false);
                building.second->SelectionBox->setLayer(1);
                Buttons[to_string(building.second->getID())] = building.second->SelectionBox;

                if (building.second->sName == "Barracks")
                {
                    building.second->Counter = new TextBox(m_Renderer, m_Window, m_Font);
                    building.second->Counter->showBorder(false);
                    building.second->Counter->setFontSize(40);
                    building.second->Counter->setLayer(1);
                    building.second->Counter->setTextColor({ 0xFF, 0xD7, 0x00 });
                    building.second->Counter->setAlignment("CENTERED");
                    TextBoxes[to_string(building.second->getID())] = building.second->Counter;
                }
            }

            Menus["Fortress"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Fortress"]->setPosition(0.75f, 0.7f);
            Menus["Fortress"]->setSize(0.25f, 0.3f);
            Menus["Fortress"]->setTableSize(2, 2);
            Menus["Fortress"]->enable(false);
            if (mLanguage == "English")
            {
                Menus["Fortress"]->addButton("Passive Gold", "Passive Gold");
                Menus["Fortress"]->addButton("Upgrade Building", "Upgrade");
            }
                
            else if (mLanguage == "Spanish")
            {
                Menus["Fortress"]->addButton("Passive Gold", "Oro pasivo");
                Menus["Fortress"]->addButton("Upgrade Building", "Mejorar");
            }
            Menus["Fortress"]->addButton("test3", "test3");
            Menus["Fortress"]->addButton("test4", "test4");

            TextBoxes["Victory"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Victory"]->setPosition(0.42f, 0.3f);
            TextBoxes["Victory"]->setSize(0.16f, 0.2f);
            TextBoxes["Victory"]->setFontSize(70);
            TextBoxes["Victory"]->showBorder(true);
            TextBoxes["Victory"]->enable(false);
            if (mLanguage == "English")
                TextBoxes["Victory"]->setText("Victory!");
            else if (mLanguage == "Spanish")
                TextBoxes["Victory"]->setText("¡Victoria!");

            Menus["Escape Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Escape Menu"]->setPosition(0.35f, 0.3f);
            Menus["Escape Menu"]->setSize(0.3f, 0.5f);
            Menus["Escape Menu"]->setTableSize(4, 1);
            Menus["Escape Menu"]->enable(false);
            if (mLanguage == "English")
            {
                Menus["Escape Menu"]->addButton("1 Return", "Return");
                Menus["Escape Menu"]->addButton("2 Pause", "Pause");
                Menus["Escape Menu"]->addButton("3 Settings", "Settings");
                Menus["Escape Menu"]->addButton("4 Exit", "Exit match");
            }
            else if (mLanguage == "Spanish")
            {
                Menus["Escape Menu"]->addButton("1 Return", "Volver");
                Menus["Escape Menu"]->addButton("2 Pause", "Pausar");
                Menus["Escape Menu"]->addButton("3 Settings", "Configuracion");
                Menus["Escape Menu"]->addButton("4 Exit", "Salir de partida");
            }

            Menus["Settings Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Settings Menu"]->setPosition(0.3f, 0.2f);
            Menus["Settings Menu"]->setSize(0.4f, 0.45f);
            Menus["Settings Menu"]->setTableSize(3, 1);
            Menus["Settings Menu"]->enable(false);
            if (mLanguage == "English")
            {
                if (bFullscreen) Menus["Settings Menu"]->addButton("1 Fullscreen", "Fullscreen");
                else Menus["Settings Menu"]->addButton("1 Fullscreen", "Windowed");

                Menus["Settings Menu"]->addButton("2 Resolution", to_string(m_nScreenHeight) + "p");
                Menus["Settings Menu"]->addButton("3 Language", mLanguage);
                Menus["Settings Menu"]->addButton("4 Exit", "Exit");
            }
            else if (mLanguage == "Spanish")
            {
                if (bFullscreen) Menus["Settings Menu"]->addButton("1 Fullscreen", "Pantalla completa");
                else Menus["Settings Menu"]->addButton("1 Fullscreen", "Ventana");

                Menus["Settings Menu"]->addButton("2 Resolution", to_string(m_nScreenHeight) + "p");
                Menus["Settings Menu"]->addButton("3 Language", mLanguage);
                Menus["Settings Menu"]->addButton("4 Exit", "Salir");
            }

            Buttons["Escape"] = new Button(m_Renderer, m_Window, m_Font);
            Buttons["Escape"]->setPosition(0.9f, 0.0f);
            Buttons["Escape"]->setSize(0.1f, 0.1f);
            Buttons["Escape"]->setText("Esc");
        }

    }

    virtual void UpdateMenu() {
            
        if (textInputMode)
        {
            SDL_StartTextInput();
        }

        while (SDL_PollEvent(&m_Event) != 0)
        {

            GUIInput();
            
            //User requests quit
            if (m_Event.type == SDL_QUIT)
            {
                close();
            }

            else if (m_Event.type == SDL_KEYDOWN || m_Event.type == SDL_KEYUP)
            {
            
                if (m_nGameState == IPscreen && textInputMode == true)
                {
            
                    if (bKey[SDL_SCANCODE_RETURN] && textInputMode)
                    {
                        if (!bHoldKey[SDL_SCANCODE_RETURN] && m_nGameState == IPscreen)
                        {
                            IP = TextBoxes["IP"]->mText;
                            DestroyGUI();
                            m_nGameState = matchLobby;
                            CreateGUI();
                            bHoldKey[SDL_SCANCODE_RETURN] = true;
                        }
                        else
                            bHoldKey[SDL_SCANCODE_RETURN] = false;
                    }
                }

                if (m_nGameState == matchLobby && textInputMode == true)
                {
                    if (bKey[SDL_SCANCODE_RETURN] && textInputMode)
                    {
                        if (!bHoldKey[SDL_SCANCODE_RETURN] && m_nGameState == matchLobby)
                        {
                            Username = TextBoxes["Username"]->mText.c_str();
                            textInputMode = false;
                            bHoldKey[SDL_SCANCODE_RETURN] = true;
                        }
                        else
                            bHoldKey[SDL_SCANCODE_RETURN] = false;
                    }
                }

            }
        }
        
        if (m_nGameState == startMenu)
        {
            if (Menus["Start Menu"]->Buttons["1 Singleplayer"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = inMatch;
                CreateGUI();
            }
            else if (Menus["Start Menu"]->Buttons["2 Multiplayer"]->bPressed)
            {
                DestroyGUI();
                bMultiplayer = true;
                m_nGameState = multiplayerMenu;
                CreateGUI();
            }
            else if (Menus["Start Menu"]->Buttons["3 Settings"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = optionMenu;
                CreateGUI();
            }
            else if (Menus["Start Menu"]->Buttons["4 Exit"]->bPressed)
            {
                close();
            }

        }

        else if (m_nGameState == optionMenu)
        {
            if (Menus["Configuration Menu"]->Buttons["1 Fullscreen"]->bPressed)
            {
                if (!bFullscreen)
                    SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                else
                    SDL_SetWindowFullscreen(m_Window, 0);

                SDL_GetWindowSize(m_Window, &m_nScreenWidth, &m_nScreenHeight);

                bFullscreen = !bFullscreen;

                DestroyGUI();
                CreateGUI();

                SetConfiguration();
            }
            else if (Menus["Configuration Menu"]->Buttons["2 Resolution"]->bPressed)
            {
                if (m_nScreenHeight == 720)
                {
                    m_nScreenWidth = 1600;
                    m_nScreenHeight = 900;
                }
                else if (m_nScreenHeight == 900)
                {
                    m_nScreenWidth = 1920;
                    m_nScreenHeight = 1080;
                }
                else if (m_nScreenHeight == 1080)
                {
                    m_nScreenWidth = 2560;
                    m_nScreenHeight = 1440;
                }
                else if (m_nScreenHeight == 1440)
                {
                    m_nScreenWidth = 3840;
                    m_nScreenHeight = 2160;
                }
                else if (m_nScreenHeight == 2160)
                {
                    m_nScreenWidth = 1280;
                    m_nScreenHeight = 720;
                }
                SDL_SetWindowSize(m_Window, m_nScreenWidth, m_nScreenHeight);
                DestroyGUI();
                CreateGUI();
            }
            else if (Menus["Configuration Menu"]->Buttons["3 Language"]->bPressed)
            {
                if (mLanguage == "English")
                    mLanguage = "Spanish";
                else mLanguage = "English";
                DestroyGUI();
                CreateGUI();
                SetConfiguration();
            }
            else if (Menus["Configuration Menu"]->Buttons["4 Exit"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = startMenu;
                CreateGUI();
            }
        }

        else if (m_nGameState == multiplayerMenu)
        {

            if (Menus["Multiplayer Menu"]->Buttons["1 Join"]->bPressed)
            {
                DestroyGUI();
                textInputMode = true;
                m_nGameState = IPscreen;
                CreateGUI();
            }
            else if (Menus["Multiplayer Menu"]->Buttons["2 Host"]->bPressed)
            {
                DestroyGUI();
                bServer = true;
                m_nGameState = matchLobby;
                CreateGUI();
            }
            else if (Menus["Multiplayer Menu"]->Buttons["3 Return"]->bPressed)
            {
                DestroyGUI();
                bMultiplayer = false;
                m_nGameState = startMenu;
                CreateGUI();
            }

        }

        else if (m_nGameState == IPscreen)
        {
            if (Menus["IP Menu"]->Buttons["1 Join"]->bPressed)
            {
                IP = TextBoxes["IP"]->mText;
                DestroyGUI();
                m_nGameState = usernameInput;
                CreateGUI();
            }
            else if (Menus["IP Menu"]->Buttons["2 Return"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = multiplayerMenu;
                textInputMode = false;
                CreateGUI();
            }
        }

        else if (m_nGameState == usernameInput)
        {
            if (Menus["Username Menu"]->Buttons["1 Join"]->bPressed)
            {
                Username = TextBoxes["Username"]->mText.c_str();
                textInputMode = false;
                DestroyGUI();
                m_nGameState = matchLobby;
                CreateGUI();
            }
            else if (Menus["Username Menu"]->Buttons["2 Return"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = IPscreen;
                textInputMode = false;
                CreateGUI();
            }
        }
    
        else if (m_nGameState == matchLobby)
        {
            if (bServer)
            {
                if (Menus["Lobby Menu"]->Buttons["1 Start"]->bPressed)
                {
                    BroadcastPacket(server, "5|\0");
                    m_nGameState = inMatch;
                }
            }
            
            if (Menus["Lobby Menu"]->Buttons["2 Return"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = startMenu;
                if (bServer) enet_host_destroy(server);
                textInputMode = false;
                bServer = false;
                bMultiplayer = false;
                CreateGUI();
            }
        }

        SDL_RenderClear(m_Renderer);

        GUIRender();

        //Background color
        SDL_SetRenderDrawColor(m_Renderer, 0xDF, 0xF9, 0xBA, 0xFF);

        //Update screen
        SDL_RenderPresent(m_Renderer);

    }

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
        if (log)
        {
            cout << "PARSE: " << data << "\n";
        }
        

        int data_type;
        char* cData = (char*)data;
        sscanf_s(cData, "%d|", &data_type);

        switch (data_type)
        {
            case 1:
            {
                char msg[80];
                sscanf_s(cData, "%*d|%[^\n]", &msg, sizeof(msg));

                currentPlayer = players[data[2] - 49];

                char send_data[1024] = { '\0' };
                sprintf_s(send_data, "1|%d|%s", id, msg);
                //BroadcastPacket(server, send_data);
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
            case 3:
            {
                int id;
                sscanf_s(cData, "%d|%d", &data_type, &id);

                client_map[id]->m_mapCreated = true;

                for (int i = 1; i < 5; i++)
                {
                    if (client_map.size() >= i)
                        if (client_map[i]->m_mapCreated == false)
                            return;
                }

                char random_seed[126] = { '\0' };
                sprintf_s(random_seed, "8|%d", randomSeed);
                printf("%s\n", random_seed);
                SendPacket(serverEvent.peer, random_seed);

                char AI_data[80] = "9|1|1|1|1";
                for (int i = 1; i < 5; i++)
                {
                    if (client_map.size() >= i) {
                        AI_data[2 * i] = '0';
                    }
                }
                printf("%s\n", AI_data);
                BroadcastPacket(server, AI_data);

                break;
            }
            case 7:
            {
                printf("%s\n", cData);
                int id;
                int turnData;
                int action;
                int argument;
                sscanf_s(cData, "%d|%d|%d|%d(%d)", &data_type, &id, &turnData, &action, &argument);
                printf("%i\n", turnData);
                client_map[id + 1]->SetTurn(turnData);
                client_map[id + 1]->m_actionQueue.emplace(action, argument);
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
                char username[80];
                sscanf_s(cData, "%*d|%*d|%[^|]", &username, sizeof(username));

                client_map[id] = new ClientData(id);
                client_map[id]->SetUsername(username);
                break;

            case 3:
                CLIENT_ID = id;
                break;
            case 5:
                DestroyGUI();
                m_nGameState = inMatch;
                CreateGUI();
                break;
            case 6:
                break;
            case 7:
                int actions[4];
                int arguments[4];
                int rTurn;
                sscanf_s(cData, "%d|%d|%d(%d)|%d(%d)|%d(%d)|%d(%d)", &data_type, &rTurn, &actions[0], &arguments[0], &actions[1], &arguments[1], &actions[2], &arguments[2], &actions[3], &arguments[3]);

                for (int i = 0; i < 4; i++)
                    playerActions[i] = { actions[i], arguments[i] };

                if (rTurn > nextTurn)
                {
                    nextTurn = rTurn;
                    turnSent = false;
                }

                break;
            case 8:
                randomSeed = id;
                break;
            case 9:
                int AIs[4];
                sscanf_s(cData, "%d|%d|%d|%d|%d", &data_type, &AIs[0], &AIs[1], &AIs[2], &AIs[3]);
                for (int i = 0; i < 4; i++)
                    if (AIs[i] == 1) players[i]->switchAI();
                break;
        }
        
        

    }

    virtual int initializeServer() 
    {
        new_player_id = 1;

        if (enet_initialize() != 0)
        {
            fprintf(stderr, "An error occurred while initializing ENet!\n");
            return EXIT_FAILURE;
        }
        atexit(enet_deinitialize);

        serverAddress.host = ENET_HOST_ANY;
        serverAddress.port = 7777;

        server = enet_host_create(&serverAddress, 4, 1, 0, 0);

        if (server == NULL)
        {
            fprintf(stderr, "An error occurred while trying to create an ENet server host!\n");
            return EXIT_FAILURE;
        }

        randomSeed = time(0);

        return EXIT_SUCCESS;
    }

    // Info types:
    // 1 Message
    // 2 Server broadcast
    // 3 ID assigment
    // 4 Disconnect
    // 5 Start match
    // 6 Game Action
    // 7 Turn
    // 8 RandomSeed

    virtual void Server()
    {
        // Handles turns
        if (m_nGameState == inMatch)
        {
            bool advanceTurn = true;

            for (auto const& x : client_map)
            {
                if (x.second->GetTurn() != turn) advanceTurn = false;
            }
            if (advanceTurn == true)
            {
                turn++;
                string content = to_string(turn);
                char message_data[80] = "7|";
                strcat_s(message_data, content.c_str());
                for (int i = 1; i < 5; i++)
                {
                    if (client_map.size() >= i && client_map[i] != NULL) {
                        if (client_map[i]->m_actionQueue.empty() == false)
                        {
                            content = "|" + to_string(client_map[i]->m_actionQueue.front().first) + "(" + to_string(client_map[i]->m_actionQueue.front().second) + ")";
                            client_map[i]->m_actionQueue.pop();
                        }
                        else content = "|0";
                        strcat_s(message_data, content.c_str());
                        client_map[i]->SetAction(0);
                    }
                    else
                    {
                        content = "|0(0)";
                        strcat_s(message_data, content.c_str());
                    }
                }
               
                printf("%s\n", message_data);
                BroadcastPacket(server, message_data);
                content = "";
            }
        }
        

        while (enet_host_service(server, &serverEvent, 0) > 0)
        {
            // Handles events in the lobby
            if (m_nGameState == matchLobby)
            {
                switch (serverEvent.type)
                {
                    case ENET_EVENT_TYPE_CONNECT:
                    {
                        for (auto const& x : client_map)
                        {
                            char send_data[1024] = { '\0' };
                            sprintf_s(send_data, "2|%d|%s", x.first, x.second->GetUsername().c_str());
                            SendPacket(serverEvent.peer, send_data);
                        }

                        while (client_map[new_player_id] != NULL) new_player_id++;
                        client_map[new_player_id] = new ClientData(new_player_id);
                        serverEvent.peer->data = client_map[new_player_id];

                        char data_to_send[126] = { '\0' };
                        sprintf_s(data_to_send, "3|%d", new_player_id);
                        SendPacket(serverEvent.peer, data_to_send);

                        DestroyGUI();
                        CreateGUI();

                        break;
                    }
                    case ENET_EVENT_TYPE_RECEIVE:
                    {
                        ParseData(server, static_cast<ClientData*>(serverEvent.peer->data)->GetID(), serverEvent.packet->data);
                        enet_packet_destroy(serverEvent.packet);

                        DestroyGUI();
                        CreateGUI();

                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT:
                    {
                        if (log)
                        {
                            printf("%x:%u disconnected.\n",
                                serverEvent.peer->address.host,
                                serverEvent.peer->address.port);
                        }


                        char disconnected_data[126] = { '\0' };
                        sprintf_s(disconnected_data, "4|%d", static_cast<ClientData*>(serverEvent.peer->data)->GetID());
                        BroadcastPacket(server, disconnected_data);

                        client_map.erase(static_cast<ClientData*>(serverEvent.peer->data)->GetID());
                        new_player_id = static_cast<ClientData*>(serverEvent.peer->data)->GetID();

                        serverEvent.peer->data = NULL;

                        DestroyGUI();
                        CreateGUI();

                        break;
                    }
                }

                system("CLS");
                cout << "Match Lobby (Server)" << endl;
                for (auto const& x : client_map)
                {
                    printf("Player %d: %s\n", x.first, x.second->GetUsername().c_str());
                }
                printf("Client map size: %d\n", client_map.size());
                cout << "S to start" << endl;
            }

            // Handles events in the match
            else if (m_nGameState == inMatch)
            {
                switch (serverEvent.type)
                {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    if (log)
                    {
                        printf("A new client connected from %x:%u.\n",
                            serverEvent.peer->address.host,
                            serverEvent.peer->address.port);
                    }

                    for (auto const& x : client_map)
                    {
                        char send_data[1024] = { '\0' };
                        sprintf_s(send_data, "2|%d|%s", x.first, x.second->GetUsername().c_str());
                        BroadcastPacket(server, send_data);
                    }

                    new_player_id++;
                    client_map[new_player_id] = new ClientData(new_player_id);
                    serverEvent.peer->data = client_map[new_player_id];

                    char data_to_send[126] = { '\0' };
                    sprintf_s(data_to_send, "3|%d", new_player_id);
                    SendPacket(serverEvent.peer, data_to_send);

                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE:
                {
                    if (log)
                    {
                        printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
                            serverEvent.packet->dataLength,
                            serverEvent.packet->data,
                            serverEvent.peer->address.host,
                            serverEvent.peer->address.port,
                            serverEvent.channelID);
                    }

                    ParseData(server, static_cast<ClientData*>(serverEvent.peer->data)->GetID(), serverEvent.packet->data);
                    //printf("%i\n", turn);
                    enet_packet_destroy(serverEvent.packet);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT:
                {
                    if (log)
                    {
                        printf("%x:%u disconnected.\n",
                            serverEvent.peer->address.host,
                            serverEvent.peer->address.port);
                    }


                    char disconnected_data[126] = { '\0' };
                    sprintf_s(disconnected_data, "4|%d", static_cast<ClientData*>(serverEvent.peer->data)->GetID());
                    BroadcastPacket(server, disconnected_data);

                    client_map.erase(static_cast<ClientData*>(serverEvent.peer->data)->GetID());

                    serverEvent.peer->data = NULL;
                    break;
                }
                }
            }
            
        }
        
        // GAME LOOP END

        
    }

    virtual int initializeClient()
    {
        const char* ip = IP.c_str();
        const char* username = Username.c_str();

        if (enet_initialize() != 0)
        {
            fprintf(stderr, "An error occurred while initializing ENet!\n");
            return EXIT_FAILURE;
        }
        atexit(enet_deinitialize);

        client = enet_host_create(NULL, 1, 1, 0, 0);

        if (client == NULL)
        {
            fprintf(stderr, "An error occurred while trying to create an ENet client host!\n");
            return EXIT_FAILURE;
        }

        enet_address_set_host(&clientAddress, ip);
        clientAddress.port = 7777;

        peer = enet_host_connect(client, &clientAddress, 1, 0);
        if (peer == NULL)
        {
            fprintf(stderr, "No available peers for initiating an ENet connection\n");
            return EXIT_FAILURE;
        }

        if (enet_host_service(client, &clientEvent, 5000) > 0 && clientEvent.type == ENET_EVENT_TYPE_CONNECT)
        {
            cout << "Connection to " << ip << " succeeded." << endl;
        }
        else
        {
            enet_peer_reset(peer);
            cout << "Connection to " << ip << " failed." << endl;
            return EXIT_SUCCESS;
        }

        // Send the server the user's username
        char str_data[80] = "2|";
        strcat_s(str_data, username);
        SendPacket(peer, str_data);
    }

    virtual int Client()
    {

        while (SDL_PollEvent(&m_Event) != 0)
        {
            //User requests quit
            if (m_Event.type == SDL_QUIT)
            {
                close();
            }
        }

        if (m_nGameState == inMatch)
        {
            // Handles player inputs
            
            // Handles local turns
            if (turn == nextTurn && !turnSent)
            {
                string sTurn = "|" + to_string(turn);
                char turn_data[80] = "7|";
                string content = to_string(currentPlayer->getTeam());
                strcat_s(turn_data, content.c_str());
                strcat_s(turn_data, sTurn.c_str());
                if (!actionQueue.empty())
                {
                    string action_data = "|";
                    action_data += to_string(actionQueue.front().first);
                    action_data += "(" + to_string(actionQueue.front().second) + ")";
                    actionQueue.pop();
                    strcat_s(turn_data, action_data.c_str());
                    lastAction = -1;
                }
                else
                {
                    string action_data = "|0(0)";
                    strcat_s(turn_data, action_data.c_str());
                }
                SendPacket(peer, turn_data);
                sTurn = "";
                turnSent = true;
            }
            
        }
        
        while (enet_host_service(client, &clientEvent, 0) > 0)
        {
            if (m_nGameState == matchLobby)
            {
                switch (clientEvent.type)
                {
                    case ENET_EVENT_TYPE_RECEIVE:
                        ("%s\n", clientEvent.packet->data);
                        ParseDataClient(clientEvent.packet->data);
                        DestroyGUI();
                        CreateGUI();
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        puts("Disconnection succeeded.");
                        break;
                }
                system("CLS");
                cout << "Match Lobby" << endl;
                for (auto const& x : client_map)
                {
                    if (x.first == CLIENT_ID) printf("Player %d: %s (You)\n", x.first, x.second->GetUsername().c_str());
                    else printf("Player %d: %s\n", x.first, x.second->GetUsername().c_str());
                    
                }
                printf("Client map size: %d", client_map.size());
            }
            else if (m_nGameState == inMatch)
            {
                switch (clientEvent.type)
                {
                case ENET_EVENT_TYPE_RECEIVE:
                    ParseDataClient(clientEvent.packet->data);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    //puts("Disconnection succeeded.");
                    break;
                }
            }
        }

        return EXIT_SUCCESS;
    }

    virtual void Input()
    {
        // INPUT ============================================

        lastAction = -1;

        while (SDL_PollEvent(&m_Event) != 0)
        {
            //User requests quit
            if (m_Event.type == SDL_QUIT)
            {
                freeMemory();
                close();
            }
            else if (m_Event.type == SDL_KEYDOWN || m_Event.type == SDL_KEYUP)
            {
                if (m_nGameState == startMenu)
                {
                    if (bKey[SDL_SCANCODE_S])
                    {
                        if (!bHoldKey[SDL_SCANCODE_S] && m_nGameState == startMenu)
                        {
                            m_nGameState = inMatch;
                            bHoldKey[SDL_SCANCODE_S] = true;
                        }
                        else
                            bHoldKey[SDL_SCANCODE_S] = false;
                    }

                    if (bKey[SDL_SCANCODE_M])
                    {
                        if (!bHoldKey[SDL_SCANCODE_M] && m_nGameState == startMenu)
                        {
                            m_nGameState = multiplayerMenu;
                            bHoldKey[SDL_SCANCODE_M] = true;
                        }
                        else
                            bHoldKey[SDL_SCANCODE_M] = false;
                    }
                }

                else if (m_nGameState == multiplayerMenu)
                {
                    if (bKey[SDL_SCANCODE_H])
                    {
                        if (!bHoldKey[SDL_SCANCODE_H] && m_nGameState == multiplayerMenu)
                        {
                            bServer = true;
                            m_nGameState = matchLobby;
                            bHoldKey[SDL_SCANCODE_H] = true;
                        }
                        else
                            bHoldKey[SDL_SCANCODE_H] = false;
                    }

                    if (bKey[SDL_SCANCODE_J])
                    {
                        if (!bHoldKey[SDL_SCANCODE_J] && m_nGameState == multiplayerMenu)
                        {
                            m_nGameState = multiplayerMenu;
                            bHoldKey[SDL_SCANCODE_J] = true;
                        }
                        else
                            bHoldKey[SDL_SCANCODE_J] = false;
                    }
                }

                else if (m_nGameState == inMatch)
                {
                    // Arrow keys - Camera movement 
                    if (bKey[SDL_SCANCODE_RIGHT]) if (currentPlayer->getCameraX() <= 40)     currentPlayer->setCamera({ currentPlayer->getCameraX() + (1.1f / fScale), currentPlayer->getCameraY() });
                    if (bKey[SDL_SCANCODE_LEFT]) if (currentPlayer->getCameraX() >= -40)      currentPlayer->setCamera({ currentPlayer->getCameraX() + (-1.1f / fScale), currentPlayer->getCameraY() });
                    if (bKey[SDL_SCANCODE_DOWN]) if (currentPlayer->getCameraY() <= 40)     currentPlayer->setCamera({ currentPlayer->getCameraX(), currentPlayer->getCameraY() + (1.1f / fScale) });
                    if (bKey[SDL_SCANCODE_UP]) if (currentPlayer->getCameraY() >= -40)      currentPlayer->setCamera({ currentPlayer->getCameraX(), currentPlayer->getCameraY() + (-1.1f / fScale) });

                    // Numpad "+" - Increase ticks per second (only singleplayer)

                    if (!bMultiplayer && bKey[SDL_SCANCODE_KP_PLUS])
                    {
                        nTicksPerSecond += (!bHoldKey[SDL_SCANCODE_KP_PLUS] && bKey[SDL_SCANCODE_KP_PLUS] && nTicksPerSecond < 200) ? 5 : 0;
                        setGameTick(nTicksPerSecond);
                        bHoldKey[SDL_SCANCODE_KP_PLUS] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_KP_PLUS] = false;

                    // Numpad "-" - Decrease ticks per second (only singleplayer)

                    if (!bMultiplayer && bKey[SDL_SCANCODE_KP_MINUS])
                    {
                        nTicksPerSecond -= (!bHoldKey[SDL_SCANCODE_KP_MINUS] && bKey[SDL_SCANCODE_KP_MINUS] && nTicksPerSecond > 0) ? 5 : 0;
                        setGameTick(nTicksPerSecond);
                        bHoldKey[SDL_SCANCODE_KP_MINUS] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_KP_MINUS] = false;

                    // "Z"/"X" - Zoom in/out
                    if (bKey[SDL_SCANCODE_Z])
                    {
                        nTileSize *= (!bHoldKey[SDL_SCANCODE_Z] && bKey[SDL_SCANCODE_Z] && nTileSize < 2048) ? 2 : 1;
                        bHoldKey[SDL_SCANCODE_Z] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_Z] = false;

                    if (bKey[SDL_SCANCODE_X])
                    {
                        nTileSize *= (!bHoldKey[SDL_SCANCODE_X] && bKey[SDL_SCANCODE_X] && nTileSize > 16) ? 0.5f : 1;
                        bHoldKey[SDL_SCANCODE_X] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_X] = false;

                    // "C" - Show/Hide grid
                    if (bKey[SDL_SCANCODE_C])
                    {
                        if (!bHoldKey[SDL_SCANCODE_C]) bShowGrid = !bShowGrid;
                        bHoldKey[SDL_SCANCODE_C] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_C] = false;

                    // "F3" - Active/Deactivate debug mode
                    if (bKey[SDL_SCANCODE_F3])
                    {
                        if (!bHoldKey[SDL_SCANCODE_F3]) {
                            bDebugMode = !bDebugMode;
                        }
                        bHoldKey[SDL_SCANCODE_F3] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_F3] = false;

                    // "F10" - Change screen size
                    if (bKey[SDL_SCANCODE_F10])
                    {
                        if (!bHoldKey[SDL_SCANCODE_F10]) {
                            if (!bFullscreen)
                            {
                                if (m_nScreenWidth == 1280)
                                {
                                    m_nScreenWidth = 1600;
                                    m_nScreenHeight = 900;
                                }
                                else if (m_nScreenWidth == 1600)
                                {
                                    m_nScreenWidth = 1920;
                                    m_nScreenHeight = 1080;
                                }
                                else if (m_nScreenWidth == 1920)
                                {
                                    m_nScreenWidth = 3840;
                                    m_nScreenHeight = 2160;
                                }
                                else if (m_nScreenWidth == 3840)
                                {
                                    m_nScreenWidth = 1280;
                                    m_nScreenHeight = 720;
                                }
                                SDL_SetWindowSize(m_Window, m_nScreenWidth, m_nScreenHeight);
                                DestroyGUI();
                                CreateGUI();
                            }
                            
                        }
                        bHoldKey[SDL_SCANCODE_F10] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_F10] = false;

                    // "F11" - Fullscreen
                    if (bKey[SDL_SCANCODE_F11])
                    {
                        if (!bHoldKey[SDL_SCANCODE_F11]) {

                            if (!bFullscreen)
                                SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                            else
                                SDL_SetWindowFullscreen(m_Window, 0);

                            SDL_GetWindowSize(m_Window, &m_nScreenWidth, &m_nScreenHeight);

                            DestroyGUI();
                            CreateGUI();

                            bFullscreen = !bFullscreen;
                            SetConfiguration();

                        }
                        bHoldKey[SDL_SCANCODE_F11] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_F11] = false;

                    // "F" - Train footman
                    keystrokeHandle(SDL_SCANCODE_F, 1);

                    // "T" - Train Tremendiñus 
                    keystrokeHandle(SDL_SCANCODE_T, 9);

                    // "Esc" - Return to start menu
                    if (bKey[SDL_SCANCODE_ESCAPE])
                    {

                        Menus["Escape Menu"]->enable(!Menus["Escape Menu"]->isEnabled());

                    }

                    // "P" - Pause
                    keystrokeHandle(SDL_SCANCODE_P, 4);

                    // "M" - Train mage
                    keystrokeHandle(SDL_SCANCODE_M, 2);

                    // "K" - Train knight
                    keystrokeHandle(SDL_SCANCODE_K, 3);

                    //"1" Building select
                    keystrokeHandle(SDL_SCANCODE_1, 5);

                    //"2" Building upgrade
                    keystrokeHandle(SDL_SCANCODE_2, 6);

                    //"3" - Passive gold upgrade
                    keystrokeHandle(SDL_SCANCODE_3, 8);

                    //"A" Train Archer
                    keystrokeHandle(SDL_SCANCODE_A, 7);

                    //"B" Train BigBird
                    keystrokeHandle(SDL_SCANCODE_B, 10);

                    //"Q" Train Cannon
                    keystrokeHandle(SDL_SCANCODE_Q, 11);

                    //"G" Train Minigun
                    keystrokeHandle(SDL_SCANCODE_G, 12);

                }

                else if (m_nGameState == matchLobby)
                {
                    // "S" - Starts match in server lobby 
                    if (bKey[SDL_SCANCODE_S])
                    {
                        if (!bHoldKey[SDL_SCANCODE_S] && m_nGameState == matchLobby)
                        {
                            BroadcastPacket(server, "5|\0");
                            m_nGameState = inMatch;
                            system("CLS");
                        };
                        bHoldKey[SDL_SCANCODE_S] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_S] = false;
                }
            }

            GUIInput();

            if (Menus["Barracks"]->Buttons["2 Train Footman"]->bPressed)
            {
                playerAction(1);
                Menus["Barracks"]->Buttons["2 Train Footman"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["3 Train Archer"]->bPressed)
            {
                playerAction(7);
                Menus["Barracks"]->Buttons["3 Train Archer"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["4 Train Mage"]->bPressed)
            {
                playerAction(2);
                Menus["Barracks"]->Buttons["4 Train Mage"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["5 Train Big Bird"]->bPressed)
            {
                playerAction(10);
                Menus["Barracks"]->Buttons["5 Train Big Bird"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["6 Train Cannon"]->bPressed)
            {
                playerAction(11);
                Menus["Barracks"]->Buttons["6 Train Cannon"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["7 Train Knight"]->bPressed)
            {
                playerAction(3);
                Menus["Barracks"]->Buttons["7 Train Knight"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["8 Train Tremendinius"]->bPressed)
            {
                playerAction(9);
                Menus["Barracks"]->Buttons["8 Train Tremendinius"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["9 Train Gatling Gun"]->bPressed)
            {
                playerAction(12);
                Menus["Barracks"]->Buttons["9 Train Gatling Gun"]->bPressed = false;
            }

            else if (Menus["Barracks"]->Buttons["1 Upgrade Building"]->bPressed)
            {
                playerAction(6);
                Menus["Barracks"]->Buttons["1 Upgrade Building"]->bPressed = false;
            }

            else if (Menus["Fortress"]->Buttons["Upgrade Building"]->bPressed)
            {
                playerAction(6);
                Menus["Fortress"]->Buttons["Upgrade Building"]->bPressed = false;
            }

            else if (Menus["Fortress"]->Buttons["Passive Gold"]->bPressed)
            {
                playerAction(8);
                Menus["Fortress"]->Buttons["Passive Gold"]->bPressed = false;
            }

            else if (Menus["Escape Menu"]->Buttons["1 Return"]->bPressed)
            {
                Menus["Escape Menu"]->enable(false);
                Menus["Escape Menu"]->Buttons["1 Return"]->bPressed = false;
            }

            else if (Menus["Escape Menu"]->Buttons["2 Pause"]->bPressed)
            {
                playerAction(4);
                Menus["Escape Menu"]->Buttons["2 Pause"]->bPressed = false;
            }

            else if (Menus["Escape Menu"]->Buttons["3 Settings"]->bPressed)
            {
                Menus["Escape Menu"]->enable(false);
                Menus["Escape Menu"]->Buttons["3 Settings"]->bPressed = false;
                Menus["Settings Menu"]->enable(true);
            }

            else if (Menus["Escape Menu"]->Buttons["4 Exit"]->bPressed)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (auto& texture : m_Textures[i])
                    {
                        texture.second.free();
                    }
                    m_Textures[i].clear();
                    
                }
                
                destroyMatch();
                m_nGameState = startMenu;
                DestroyGUI();
                CreateGUI();
            }

            else if (Menus["Settings Menu"]->Buttons["1 Fullscreen"]->bPressed)
            {
                if (!bFullscreen)
                    SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                else
                    SDL_SetWindowFullscreen(m_Window, 0);

                SDL_GetWindowSize(m_Window, &m_nScreenWidth, &m_nScreenHeight);

                bFullscreen = !bFullscreen;

                DestroyGUI();
                CreateGUI();

                SetConfiguration();
                Menus["Settings Menu"]->Buttons["1 Fullscreen"]->bPressed = false;
            }
            else if (Menus["Settings Menu"]->Buttons["2 Resolution"]->bPressed)
            {
                if (m_nScreenHeight == 720)
                {
                    m_nScreenWidth = 1600;
                    m_nScreenHeight = 900;
                }
                else if (m_nScreenHeight == 900)
                {
                    m_nScreenWidth = 1920;
                    m_nScreenHeight = 1080;
                }
                else if (m_nScreenHeight == 1080)
                {
                    m_nScreenWidth = 2560;
                    m_nScreenHeight = 1440;
                }
                else if (m_nScreenHeight == 1440)
                {
                    m_nScreenWidth = 3840;
                    m_nScreenHeight = 2160;
                }
                else if (m_nScreenHeight == 2160)
                {
                    m_nScreenWidth = 1280;
                    m_nScreenHeight = 720;
                }
                SDL_SetWindowSize(m_Window, m_nScreenWidth, m_nScreenHeight);
                DestroyGUI();
                CreateGUI();
                Menus["Settings Menu"]->Buttons["2 Resolution"]->bPressed = false;
            }
            else if (Menus["Settings Menu"]->Buttons["3 Language"]->bPressed)
            {
                if (mLanguage == "English")
                    mLanguage = "Spanish";
                else mLanguage = "English";
                DestroyGUI();
                CreateGUI();
                SetConfiguration();
                Menus["Settings Menu"]->Buttons["3 Language"]->bPressed = false;
            }
            else if (Menus["Settings Menu"]->Buttons["4 Exit"]->bPressed)
            {
                Menus["Settings Menu"]->enable(false);
                Menus["Escape Menu"]->enable(true);
                Menus["Settings Menu"]->Buttons["4 Exit"]->bPressed = false;
            }
            else if (Buttons["Escape"]->bPressed)
            {
                Menus["Escape Menu"]->enable(true);
                Buttons["Escape"]->bPressed = false;
            }

            for (auto& building : buildings)
            {
                if (building.second->getTeam() == currentPlayer->getTeam())
                {
                    int bID = building.second->getID();
                    if (Buttons[to_string(bID)]->bPressed)
                    {
                        playerAction(5, bID);
                        Buttons[to_string(bID)]->bPressed = false;
                        if (building.second->sName == "Fortress") Menus["Fortress"]->enable(true);
                        else Menus["Fortress"]->enable(false);
                        if (building.second->sName == "Barracks") Menus["Barracks"]->enable(true);
                        else Menus["Barracks"]->enable(false);
                    }
                }

            }
            
        }

        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x > m_nScreenWidth - m_nScreenWidth / 30)
        {
            if (currentPlayer->getCameraX() <= 40)     currentPlayer->setCamera({ currentPlayer->getCameraX() + (0.08f / fScale), currentPlayer->getCameraY() });
        }
        else if (x < m_nScreenWidth / 30)
        {
            if (currentPlayer->getCameraX() >= -40)     currentPlayer->setCamera({ currentPlayer->getCameraX() - (0.08f / fScale), currentPlayer->getCameraY() });
        }
        if (y > m_nScreenHeight - m_nScreenHeight / 30)
        {
            if (currentPlayer->getCameraY() <= 40)     currentPlayer->setCamera({ currentPlayer->getCameraX(), currentPlayer->getCameraY() + (0.08f / fScale) });
        }
        else if (y < m_nScreenHeight / 30)
        {
            if (currentPlayer->getCameraY() >= -40)     currentPlayer->setCamera({ currentPlayer->getCameraX(), currentPlayer->getCameraY() - (0.08f / fScale) });
        }

    }

    void keystrokeHandle(int key, int action, int argument = 0)
    {
        if (bKey[key])
        {
            if (!bHoldKey[key])
            {
                playerAction(action, argument);
            };
            bHoldKey[key] = true;
        }
        else
            bHoldKey[key] = false;
    }

    void playerAction(int action, int argument = 0)
    {
        if (bMultiplayer)
        {
            if (actionQueue.size() < 5)
            {
                actionQueue.emplace(action, argument);
            }
            else
            {
                actionQueue.emplace(action, argument);
                actionQueue.pop();
            }
        }
        else gameAction(currentPlayer->getTeam(), action, argument);
    }

    virtual void Settings()
    {
        setGameTick(nTicksPerSecond);
    }

    virtual void CreateMatch()
    {
        createMap();
        createPlayers();
        players[0]->selectedBuilding()->select();
        players[1]->selectedBuilding()->select();
        players[2]->selectedBuilding()->select();
        players[3]->selectedBuilding()->select();

        if(!bMultiplayer) randomSeed = time(0);
        srand(randomSeed);
        if (bMultiplayer)
        {
            char mapCreated[5] = "3|";
            string content = to_string(CLIENT_ID);
            strcat_s(mapCreated, content.c_str());
            SendPacket(peer, mapCreated);
        }

        CreateGUI();

    }

    void destroyMatch()
    {
        for (auto& player : players)
        {
            delete player;
        }
        players.clear();
        for (auto& entity : entityList)
        {
            delete entity.second;
        }
        entityList.clear();
        buildings.clear();
        units.clear();
        projectiles.clear();
        waveTimer = 0;
        lastAction = 0;
        turn = 0;
        nextTurn = 0;
        ticksSinceLastTurn = 0;
    }

    virtual void Update(float fElapsedTime)
    {      

            // GAME LOGIC ============================================
        ticksSinceLastTurn++;
        if (turn < nextTurn && ticksSinceLastTurn >= 10)
        {
            turn++;
            ticksSinceLastTurn = 0;
            for (int i = 0; i < 4; i++)
                gameAction(i, playerActions[i].first, playerActions[i].second);
        }

        if ((ticksSinceLastTurn < 10 || !bMultiplayer) && !pause)
        {
            
            for (int i = 0; i < players.size(); i++) players[i]->spawnUnitCooldown--;

            waveTimer++;

            if (waveTimer == 1 || waveTimer % 900 == 0)
            {
                for (int i = 0; i < (int)players.size(); i++)
                {
                    players[i]->addGold(players[i]->nPassiveGold);

                    for (int a = 0; a < (int)players[i]->teamBuildings.size(); a++)
                    {
                        if (players[i]->teamBuildings[a]->sName == "Barracks")
                        {
                            vector<Unit*> wave;
                            wave.push_back(new Footman());
                            wave.push_back(new Footman());
                            wave.push_back(new Footman());
                            wave.push_back(new Archer());
                            wave.push_back(new Archer());

                            if (players[i]->teamBuildings[a]->getLevel() >= 2)
                            {
                                wave.push_back(new BigBird());
                                wave.push_back(new BigBird());
                            }
                            if (players[i]->teamBuildings[a]->getLevel() >= 3)
                            {
                                wave.push_back(new Footman());
                                wave.push_back(new Mage());
                                wave.push_back(new Archer());
                            }
                            if (players[i]->teamBuildings[a]->getLevel() >= 4)
                            {
                                wave.push_back(new BigBird());
                                wave.push_back(new Archer());
                                wave.push_back(new Cannon());
                            }

                            wave = players[i]->teamBuildings[a]->spawnWave(wave);

                            for (int b = 0; b < (int)wave.size(); b++)
                            {
                                wave[b]->setHealth((int)(wave[b]->nHealth * players[wave[b]->getTeam()]->healthModifier));
                                wave[b]->setMaxHealth((int)(wave[b]->nMaxHealth * players[wave[b]->getTeam()]->healthModifier));
                            }


                            for (int b = 0; b < (int)wave.size(); b++)
                            {
                                int ID = createEntity(wave[b]);
                                players[wave[b]->getTeam()]->teamUnits.push_back(wave[b]);
                                units[ID] = wave[b];
                            }
                        }
                        
                    }
                }

            }

            // PROJECTILE HANDLING
            for (auto projectile = projectiles.begin(); projectile != projectiles.end();)
            {
                if (projectile->second->move(projectile->second->mTargetPosition, entityList))
                {
                    int toBeDestroyed = projectile->second->getID();
                    ++projectile;
                    destroyEntity(toBeDestroyed);
                }
                else ++projectile;
                
            }

            // BUILDING AI

            for (auto& building : buildings)
            {
                for (auto& unit : units)
                {
                    if (building.second->getTeam() != unit.second->getTeam())
                    {
                        if (building.second->getTargetUnit() == -1)
                        {
                            if (cDistance(building.second->mPosition, unit.second->mPosition) < building.second->fAttackDistance)
                                building.second->setTargetUnit(unit.second->getID());
                        }
                    }
                }

                if (building.second->getTargetUnit() != -1)
                {
                    building.second->setTargetPosition(units[building.second->getTargetUnit()]->mPosition);

                    if (cDistance(building.second->mPosition, units[building.second->getTargetUnit()]->mPosition) <= building.second->fAttackRange + 0)
                    {
                        shootProjectile(building.second, building.second->attack(units[building.second->getTargetUnit()]), building.second->getTargetUnit());
                    }
                    else
                    {
                        building.second->setTargetUnit(-1);
                    }
                   
                }
            }

            // UNIT AI

            if (units.size() >= 1)
            {

                for (auto& unit : units)
                {
                    unit.second->checkCollition(entityList);
                    if (cDistance(unit.second->mPosition, unit.second->mTargetPosition) >= unit.second->fAttackRange + unit.second->fWidth / 2.0f)
                    {

                        

                        Point previousPosition = unit.second->mPosition;

                        unit.second->move(unit.second->mTargetPosition);

                    }
                    
                    

                    if (cDistance(unit.second->mPosition, unit.second->mDefaultTargetPosition) <= unit.second->fAttackRange + unit.second->fHeight)
                    {
                        int id = -1;
                        float min = 100;
                        for (int i = 0; i < players.size(); i++)
                        {
                            if (players[i]->getTeam() != unit.second->getTeam() && players[i]->teamBuildings.size() >= 1)
                            {
                                for (int j = 0; j < players[i]->teamBuildings.size(); j++)
                                {
                                    float fDistance = cDistance(unit.second->mPosition, players[i]->teamBuildings[j]->mPosition);
                                    if (fDistance < min)
                                    {
                                        id = players[i]->teamBuildings[j]->getID();
                                        min = fDistance;
                                    }
                                    unit.second->setDefaultTarget(buildings[id]->mPosition);
                                }
                                
                            }
                        }
                    }
                        
                       

                    if (unit.second->getTargetUnit() == -1 || cDistance(units[unit.second->getTargetUnit()]->mPosition, unit.second->mPosition) > unit.second->fAttackRange)
                    {
                        int id = -1;
                        float min = unit.second->fAttackDistance;
                        for (auto& unit2 : units)
                        {
                            if (unit.second->getID() != unit2.second->getID())
                            {
                                float fDistance = cDistance(unit.second->mPosition, unit2.second->mPosition);
                                if (fDistance < min && unit.second->getTeam() != unit2.second->getTeam())
                                {
                                    min = fDistance;
                                    id = unit2.second->getID();
                                }
                            }
                        }
                        unit.second->setTargetUnit(id);
                        if (unit.second->getTargetUnit() == -1 && unit.second->getTargetBuilding() == -1)
                        {
                            unit.second->setTargetPosition(unit.second->mDefaultTargetPosition);
                        }
                    }

                    if (unit.second->getTargetUnit() != -1)
                    {
                        unit.second->setTargetPosition(units[unit.second->getTargetUnit()]->mPosition);

                        if (cDistance(unit.second->mPosition, unit.second->mTargetPosition) <= unit.second->fAttackRange + units[unit.second->getTargetUnit()]->fWidth / 2.0f + unit.second->fWidth / 2.0f)
                        {
                            shootProjectile(unit.second, unit.second->attack(units[unit.second->getTargetUnit()]), unit.second->getTargetUnit());
                        }
                    }
                    else
                    {
                        if (unit.second->getTargetBuilding() >= 0)
                        {
                            unit.second->setTargetPosition(buildings[unit.second->getTargetBuilding()]->mPosition);

                            if (cDistance(unit.second->mPosition, unit.second->mTargetPosition) < unit.second->fAttackRange + buildings[unit.second->getTargetBuilding()]->fWidth / 2.0f + unit.second->fWidth / 2.0f)
                            {
                                shootProjectile(unit.second, unit.second->attack(buildings[unit.second->getTargetBuilding()]), unit.second->getTargetBuilding());
                            }
                        }
                        else
                        {
                            for (auto& building : buildings)
                            {
                                if (unit.second->getTeam() != building.second->getTeam())
                                {
                                    if (cDistance(unit.second->mPosition, building.second->mPosition) < unit.second->fAttackDistance && unit.second->getTargetBuilding() == -1)
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
                                {
                                    unit2.second->setTargetUnit(-1);
                                }

                            }
                            for (auto& building : buildings)
                            {
                                if (building.second->getTargetUnit() == unit.second->getID())
                                {
                                    building.second->setTargetUnit(-1);
                                }

                            }
                            for (auto& projectile : projectiles)
                            {
                                if (projectile.second->nTargetID == unit.second->getID())
                                {
                                    projectile.second->nTargetID = -1;
                                }

                            }

                            int team = unit.second->getLastHitID();
                            int player = unit.second->getTeam();
                                
                            players[team]->addGold(unit.second->nKillReward);

                            if (unit.second->sName == "Tremendinius") players[player]->tremendiniusAlive = false;

                            if (unit.second->sName == "Minigun") players[player]->minigunAlive = false;

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
                    if (building.second->nHealth <= 0)
                    {
                        bBuildingDestroyed = true;
                        for (auto& unit : units)
                        {
                            if (unit.second->getTargetBuilding() == building.second->getID()) unit.second->setTargetBuilding(-1);
                        }
                        for (auto& projectile : projectiles)
                        {
                            if (projectile.second->nTargetID == building.second->getID())
                            {
                                projectile.second->nTargetID = -1;
                            }

                        }
                        int killer = building.second->getLastHitID();
                        int owner = building.second->getTeam();
                        players[killer]->addGold(building.second->nKillReward);

                        if (players[owner]->teamBuildings.size() > 1 && players[owner]->selectedBuilding() == building.second)
                        {
                            gameAction(owner, 5);
                        }
                        
                        destroyEntity(building.second->getID());
                        break;
                    }
                }


            }

            // Player AI
            if (waveTimer % 50 == 0)
            {
                for (int i = 0; i < (int)players.size(); i++)
                {
                    if (players[i]->isAI())
                    {
                        int AIaction = rand() % 12 + 1;
                        if (players[i]->teamBuildings.size() > 1)
                        {
                            if (waveTimer < 3000)
                            {
                                if (AIaction != 4 && AIaction != 5) gameAction(i, AIaction);
                                else if (AIaction == 5)
                                {
                                    int tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                    int counter = 0;
                                    while (players[i]->teamBuildings[tBuilding]->sName == "Tower" || counter >= 10)
                                    {
                                        tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                        counter++;
                                    }
                                    int argument = players[i]->teamBuildings[tBuilding]->getID();

                                    gameAction(i, AIaction, argument);
                                }
                            }
                            else if (waveTimer < 6000 && players[i]->getGold() > 1000)
                            {
                                if (AIaction != 4 && AIaction != 5) gameAction(i, AIaction);
                                else if (AIaction == 5)
                                {
                                    int tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                    int counter = 0;
                                    while (players[i]->teamBuildings[tBuilding]->sName == "Tower" || counter >= 10)
                                    {
                                        tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                        counter++;
                                    }
                                    int argument = players[i]->teamBuildings[tBuilding]->getID();
                                    gameAction(i, AIaction, argument);
                                }
                            }
                            else if (waveTimer < 9000 && players[i]->getGold() > 2000)
                            {
                                if (AIaction != 4 && AIaction != 5) gameAction(i, AIaction);
                                else if (AIaction == 5)
                                {
                                    int tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                    int counter = 0;
                                    while (players[i]->teamBuildings[tBuilding]->sName == "Tower" || counter >= 10)
                                    {
                                        tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                        counter++;
                                    }
                                    int argument = players[i]->teamBuildings[tBuilding]->getID();
                                    gameAction(i, AIaction, argument);
                                }
                            }
                            else if (waveTimer < 12000 && players[i]->getGold() > 3000)
                            {
                                if (AIaction != 4 && AIaction != 5) gameAction(i, AIaction);
                                else if (AIaction == 5)
                                {
                                    int tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                    int counter = 0;
                                    while (players[i]->teamBuildings[tBuilding]->sName == "Tower" || counter >= 10)
                                    {
                                        tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                        counter++;
                                    }
                                    int argument = players[i]->teamBuildings[tBuilding]->getID();
                                    gameAction(i, AIaction, argument);
                                }
                            }
                            else if (waveTimer < 15000 && players[i]->getGold() > 4000)
                            {
                                if (AIaction != 4 && AIaction != 5) gameAction(i, AIaction);
                                else if (AIaction == 5)
                                {
                                    int tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                    int counter = 0;
                                    while (players[i]->teamBuildings[tBuilding]->sName == "Tower" || counter >= 10)
                                    {
                                        tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                        counter++;
                                    }
                                    int argument = players[i]->teamBuildings[tBuilding]->getID();
                                    gameAction(i, AIaction, argument);
                                }
                            }
                            else if (players[i]->getGold() > 5000)
                            {
                                if (AIaction != 4 && AIaction != 5) gameAction(i, AIaction);
                                else if (AIaction == 5)
                                {
                                    int tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                    int counter = 0;
                                    while (players[i]->teamBuildings[tBuilding]->sName == "Tower" || counter >= 10)
                                    {
                                        tBuilding = rand() % (int)players[i]->teamBuildings.size();
                                        counter++;
                                    }
                                    int argument = players[i]->teamBuildings[tBuilding]->getID();
                                    gameAction(i, AIaction, argument);
                                }
                            }
                        }
                      
                    }
                }
            }
            

        }

        if (!currentPlayer->getStatus()) bWin = true;

        for (auto& player : players)
        {
            if (player->teamBuildings.empty()) player->setStatus(true);
            if (player != currentPlayer && !player->getStatus()) bWin = false;
        }

        if (bWin && !TextBoxes["Victory"]->isEnabled())
        {
            TextBoxes["Victory"]->enable(true);
        }

    }

    virtual void Render()
    {
        // RENDER OUTPUT ============================================
       
        //Clear screen
        SDL_RenderClear(m_Renderer);
        
        if (m_nGameState == startMenu)
        {
        
        }
        
        else if (m_nGameState == multiplayerMenu)
        {
        
        }
        
        else if (m_nGameState == inMatch)
        {
            // Tiles in Screen
            fVerticalTilesInScreen = (float)m_nScreenHeight / (float)nTileSize;
            fHorizontalTilesInScreen = (float)m_nScreenWidth / (float)nTileSize;
            
            // Draw grid
            SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);

            if (bShowGrid)
            {
                for (int i = 0; i < m_nScreenWidth; i++)
                {
                    float fPixelX = (float)i / nTileSize - (fHorizontalTilesInScreen / 2) + currentPlayer->getCameraX();
                    float fRemainderX = fPixelX - (int)fPixelX;
                    if (fRemainderX < 0) fRemainderX += 1;
                    if (fRemainderX >= 0 && fRemainderX < (1.0 / (float)nTileSize))
                    {
                        SDL_RenderDrawLine(m_Renderer, i, 0, i, m_nScreenHeight);
                    }
                }
                for (int i = 0; i < m_nScreenHeight; i++)
                {
                    float fPixelY = (float)i / nTileSize - (fVerticalTilesInScreen / 2) + currentPlayer->getCameraY();
                    float fRemainderY = fPixelY - (int)fPixelY;
                    if (fRemainderY < 0) fRemainderY += 1;
                    if (fRemainderY >= 0 && fRemainderY < (1.0 / (float)nTileSize))
                    {
                        SDL_RenderDrawLine(m_Renderer, 0, i, m_nScreenWidth, i);
                    }
                }
            
            }
            
            fScale = (float)nTileSize / (float)16;
        
            // Calculate screen coordinates
        
            float fScreenLeftBorder = currentPlayer->getCameraX() - (fHorizontalTilesInScreen / 2.0f);
            float fScreenRightBorder = currentPlayer->getCameraX() + (fHorizontalTilesInScreen / 2.0f);
            float fScreenTopBorder = currentPlayer->getCameraY() - (fVerticalTilesInScreen / 2.0f);
            float fScreenBottomBorder = currentPlayer->getCameraY() + (fVerticalTilesInScreen / 2.0f);
            //
            //
            //
            int objectsToRender = 0;
        
            for (auto& entity : entityList)
            {
                if ((entity.second->mPosition.x > fScreenLeftBorder - entity.second->fWidth && entity.second->mPosition.x - entity.second->fWidth < fScreenRightBorder) && (entity.second->mPosition.y > fScreenTopBorder - entity.second->fHeight && entity.second->mPosition.y - entity.second->fHeight < fScreenBottomBorder))
                {
                    objectsToRender++;
                    int entityScreenLocationX = (int)((float)(entity.second->mPosition.x - currentPlayer->getCameraX() - (float)(entity.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                    int entityScreenLocationY = (int)((float)(entity.second->mPosition.y - currentPlayer->getCameraY() - (float)(entity.second->fHeight / 2.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);
                    
                    int RentityScreenLocationX = (int)((float)(entity.second->mPosition.x - currentPlayer->getCameraX()) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                    int RentityScreenLocationY = (int)((float)(entity.second->mPosition.y - currentPlayer->getCameraY()) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);

                    int realWidth = entity.second->fWidth * nTileSize;
                    int realHeight = entity.second->fHeight * nTileSize;

                    if (bDebugMode)
                    {
                        for (int i = 0; i < 12; i++)
                        {
                            SDL_RenderDrawLine(m_Renderer, RentityScreenLocationX, RentityScreenLocationY, RentityScreenLocationX + (realHeight / 2.5f * cos(i * 30 * PI / 180)), RentityScreenLocationY + (realHeight / 2.5f * sin(i * 30 * PI / 180)));
                        }

                        SDL_RenderDrawLine(m_Renderer, entityScreenLocationX, entityScreenLocationY, entityScreenLocationX + realWidth, entityScreenLocationY);
                        SDL_RenderDrawLine(m_Renderer, entityScreenLocationX + realWidth, entityScreenLocationY, entityScreenLocationX + realWidth, entityScreenLocationY + realHeight);
                        SDL_RenderDrawLine(m_Renderer, entityScreenLocationX, entityScreenLocationY, entityScreenLocationX, entityScreenLocationY + realHeight);
                        SDL_RenderDrawLine(m_Renderer, entityScreenLocationX, entityScreenLocationY + realHeight, entityScreenLocationX + realWidth, entityScreenLocationY + realHeight);
                    }

                    
                
                    int team = entity.second->getTeam();
                
                    auto it = m_Textures[team].find(entity.second->pSprite);
                
                    if (entity.second->pSprite != "" && (it == m_Textures[team].end() || it->second.mTexture == NULL))
                    {
                        m_Textures[team].insert({ entity.second->pSprite, LTexture(m_Renderer, m_Window) });
                
                        m_Textures[team][entity.second->pSprite].loadPixelsFromFile(entity.second->pSprite.c_str());
                
                        //Get pixel data
                        Uint32* pixels = m_Textures[team][entity.second->pSprite].getPixels32();
                        int pixelCount = m_Textures[team][entity.second->pSprite].getPitch32() * m_Textures[team][entity.second->pSprite].getHeight();
                
                        //Map colors
                        Uint32 colorKey[4];
                        colorKey[0] = m_Textures[team][entity.second->pSprite].mapRGBA(0xFA, 0xFA, 0xFA, 0xFF);
                        colorKey[1] = m_Textures[team][entity.second->pSprite].mapRGBA(0xE3, 0xE3, 0xE3, 0xFF);
                        colorKey[2] = m_Textures[team][entity.second->pSprite].mapRGBA(0xC9, 0xC9, 0xC9, 0xFF);
                        colorKey[3] = m_Textures[team][entity.second->pSprite].mapRGBA(0xB0, 0xB0, 0xB0, 0xFF);
                
                        Uint32 teamColor[4];
                
                        for (int i = 0; i < 4; i++)
                        {
                            teamColor[i] = m_Textures[team][entity.second->pSprite].mapRGBA(teamColors[team][i].r, teamColors[team][i].g, teamColors[team][i].b, teamColors[team][i].a);
                        }
                
                        //Color key pixels
                        for (int i = 0; i < pixelCount; ++i)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                if (pixels[i] == colorKey[j])
                                {
                                    pixels[i] = teamColor[j];
                                }
                            }    
                        }
                
                        //Create texture from manually color keyed pixels
                        m_Textures[team][entity.second->pSprite].loadFromPixels();
                
                    }
                    
                    if (entity.second->sClass == "PROJECTILE")
                    {
                        if (entity.second->fMovementAngle < 0)
                            m_Textures[team][entity.second->pSprite].render(entityScreenLocationX, entityScreenLocationY, realWidth, realHeight, NULL, -entity.second->fMovementAngle, NULL, SDL_FLIP_NONE);
                        else
                            m_Textures[team][entity.second->pSprite].render(entityScreenLocationX, entityScreenLocationY, realWidth, realHeight, NULL, -entity.second->fMovementAngle, NULL, SDL_FLIP_NONE);
                       
                    }
                       
                    else
                    {
                        if (entity.second->fMovementAngle > 90 || entity.second->fMovementAngle < -90)
                            m_Textures[team][entity.second->pSprite].render(entityScreenLocationX, entityScreenLocationY, realWidth, realHeight, NULL, NULL, NULL, SDL_FLIP_HORIZONTAL);
                        else
                            m_Textures[team][entity.second->pSprite].render(entityScreenLocationX, entityScreenLocationY, realWidth, realHeight, NULL, NULL, NULL, SDL_FLIP_NONE);
                    }
                    
                    
                    
                }
            }
            
            for (auto& unit : units)
            {
                if ((unit.second->mPosition.x > fScreenLeftBorder - unit.second->fWidth && unit.second->mPosition.x - unit.second->fWidth < fScreenRightBorder) && (unit.second->mPosition.y > fScreenTopBorder - unit.second->fHeight && unit.second->mPosition.y - unit.second->fHeight < fScreenBottomBorder))
                {
                    objectsToRender++;
                    int entityScreenLocationX = (int)((float)(unit.second->mPosition.x - currentPlayer->getCameraX() - (float)(unit.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                    int entityScreenLocationY = (int)((float)(unit.second->mPosition.y - currentPlayer->getCameraY() - (float)(unit.second->fHeight / 3.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);
            
                    SDL_Rect HealthBar = { entityScreenLocationX + (unit.second->fWidth * nTileSize) / 4, entityScreenLocationY - (unit.second->fHeight * nTileSize) / 4, (unit.second->fWidth * nTileSize) / 2, (unit.second->fWidth * nTileSize) / 10 };
                    SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
                    SDL_RenderFillRect(m_Renderer, &HealthBar);
            
                    SDL_Rect CurrentHealth = { entityScreenLocationX + (unit.second->fWidth * nTileSize) / 4, entityScreenLocationY - (unit.second->fHeight * nTileSize) / 4, (unit.second->fWidth * nTileSize) / 2 * ((float)unit.second->nHealth / (float)unit.second->nMaxHealth), (unit.second->fWidth * nTileSize) / 10 };
                    SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
                    SDL_RenderFillRect(m_Renderer, &CurrentHealth);
            
                }
            }
            
            for (auto& building : buildings)
            {
                int entityScreenLocationX = (int)((float)(building.second->mPosition.x - currentPlayer->getCameraX() - (float)(building.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                int entityScreenLocationY = (int)((float)(building.second->mPosition.y - currentPlayer->getCameraY() - (float)(building.second->fHeight / 3.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);

                if ((building.second->mPosition.x > fScreenLeftBorder - building.second->fWidth && building.second->mPosition.x - building.second->fWidth < fScreenRightBorder) && (building.second->mPosition.y > fScreenTopBorder - building.second->fHeight && building.second->mPosition.y - building.second->fHeight < fScreenBottomBorder))
                {
                    objectsToRender++;
            
                    SDL_Rect HealthBar = { entityScreenLocationX + (building.second->fWidth * nTileSize) / 4, entityScreenLocationY - (building.second->fHeight * nTileSize) / 4, (building.second->fWidth * nTileSize) / 2, (building.second->fWidth * nTileSize) / 10 };
                    SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
                    SDL_RenderFillRect(m_Renderer, &HealthBar);
            
                    SDL_Rect CurrentHealth = { entityScreenLocationX + (building.second->fWidth * nTileSize) / 4, entityScreenLocationY - (building.second->fHeight * nTileSize) / 4, (building.second->fWidth * nTileSize) / 2 * ((float)building.second->nHealth / (float)building.second->nMaxHealth), (building.second->fWidth * nTileSize) / 10 };
                    SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
                    SDL_RenderFillRect(m_Renderer, &CurrentHealth);
            
                    if (building.second->bSelected == true && building.second->getTeam() == currentPlayer->getTeam())
                    {
                        SDL_Rect Selection = { entityScreenLocationX - (building.second->fWidth * nTileSize) / 4, entityScreenLocationY - (building.second->fHeight * nTileSize) / 4, (building.second->fWidth * nTileSize) * 1.5f, (building.second->fHeight * nTileSize) * 1.5f };
                        SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
                        SDL_RenderDrawRect(m_Renderer, &Selection);
                    }

                    
                }

                building.second->SelectionBox->setPosition((float)entityScreenLocationX / (float)m_nScreenWidth, (float)entityScreenLocationY / (float)m_nScreenHeight);
                building.second->SelectionBox->setSize((float)(building.second->fWidth* nTileSize) / (float)m_nScreenWidth, (float)(building.second->fHeight* nTileSize) / (float)m_nScreenHeight);
                building.second->SelectionBox->setText("Test");

                if (building.second->Counter != NULL)
                {
                    building.second->Counter->setPosition((float)entityScreenLocationX / (float)m_nScreenWidth, ((float)entityScreenLocationY - nTileSize * 1.5f) / (float)m_nScreenHeight);
                    building.second->Counter->setSize((float)(building.second->fWidth* nTileSize) / (float)m_nScreenWidth, (float)(building.second->fHeight * nTileSize) / (float)m_nScreenHeight / 2);
                    building.second->Counter->setFontSize(nTileSize / 2);
                    building.second->Counter->setText(to_string(30 - (waveTimer / 30) % 30));
                }
            }
            
            if (mLanguage == "English")
                TextBoxes["Gold"]->setText("Gold: " + to_string(currentPlayer->getGold()));
            else if (mLanguage == "Spanish")
                TextBoxes["Gold"]->setText("Oro: " + to_string(currentPlayer->getGold()));

            GUIRender();
            
            SDL_SetRenderDrawColor(m_Renderer, 0x35, 0xa7, 0x42, 0xFF);
        
            //Update screen
            SDL_RenderPresent(m_Renderer);
        
            //Print info
        
            string windowTitle = "Caelis Chaos 0.3.0 Alpha";
            windowTitle += " - Tile size: " + to_string(nTileSize);
            windowTitle += " - FPS: " + to_string(avgFPS);
            windowTitle += " - Next wave: " + to_string(30 - (waveTimer / 30) % 30);
            windowTitle += " - Objects: " + to_string(objectsToRender);
            windowTitle += " - Ticks per second: " + to_string(nTicksPerSecond);
            SDL_SetWindowTitle(m_Window, windowTitle.c_str());
        
        }

        
    }

private:

    // Generate Base Map

    void createMap()
    {
        Fortress* Fortress1 = new Fortress();
        int fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(0, -32);
        entityList[fortressID]->setTeam(0);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(-32, 0);
        entityList[fortressID]->setTeam(1);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(0, 32);
        entityList[fortressID]->setTeam(2);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(32, 0);
        entityList[fortressID]->setTeam(3);
        
        // Team 0
        Barracks* Barracks1 = new Barracks();
        int barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(0, -27);
        entityList[barracksID]->setTeam(0);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-5, -32);
        entityList[barracksID]->setTeam(0);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(5, -32);
        entityList[barracksID]->setTeam(0);

        Tower* tower1 = new Tower();
        int towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-3, -29);
        entityList[towerID]->setTeam(0);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(3, -29);
        entityList[towerID]->setTeam(0);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-3, -35);
        entityList[towerID]->setTeam(0);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(3, -35);
        entityList[towerID]->setTeam(0);

        
        // Team 1
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-27, 0);
        entityList[barracksID]->setTeam(1);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-32, 5);
        entityList[barracksID]->setTeam(1);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-32, -5);
        entityList[barracksID]->setTeam(1);

        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-29, 3);
        entityList[towerID]->setTeam(1);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-29, -3);
        entityList[towerID]->setTeam(1);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-35, -3);
        entityList[towerID]->setTeam(1);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-35, 3);
        entityList[towerID]->setTeam(1);

        // Team 2
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(0, 27);
        entityList[barracksID]->setTeam(2);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-5, 32);
        entityList[barracksID]->setTeam(2);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(5, 32);
        entityList[barracksID]->setTeam(2);

        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-3, 29);
        entityList[towerID]->setTeam(2);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(3, 29);
        entityList[towerID]->setTeam(2);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-3, 35);
        entityList[towerID]->setTeam(2);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(3, 35);
        entityList[towerID]->setTeam(2);

        // Team 3
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(27, 0);
        entityList[barracksID]->setTeam(3);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(32, 5);
        entityList[barracksID]->setTeam(3);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(32, -5);
        entityList[barracksID]->setTeam(3);
        

        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(29, 3);
        entityList[towerID]->setTeam(3);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(29, -3);
        entityList[towerID]->setTeam(3);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(35, -3);
        entityList[towerID]->setTeam(3);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(35, 3);
        entityList[towerID]->setTeam(3);

    }

    void createPlayers()
    {
        players.push_back(new Player());
        players[0]->setTeam(0);

        players.push_back(new Player());
        players[1]->setTeam(1);

        players.push_back(new Player());
        players[2]->setTeam(2);

        players.push_back(new Player());
        players[3]->setTeam(3);;

        if (bMultiplayer) currentPlayer = players[CLIENT_ID - 1];
        else currentPlayer = players[0];

        for (int i = 0; i < (int)players.size(); i++)
        {
            for (auto& building : buildings)
                if (building.second->getTeam() == players[i]->getTeam()) players[i]->teamBuildings.push_back(building.second);
            if (!bMultiplayer && players[i] != currentPlayer) players[i]->switchAI();

            players[i]->setCamera(players[i]->teamBuildings[0]->mPosition);
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
        int player = entityList[ID]->getTeam();
        for (int i = 0; i < (int)players[player]->teamBuildings.size(); i++)
        {
            if (ID == players[player]->teamBuildings[i]->getID()) players[player]->teamBuildings.erase(players[player]->teamBuildings.begin() + i);
        }
        for (int i = 0; i < (int)players[player]->teamUnits.size(); i++)
        {
            if (ID == players[player]->teamUnits[i]->getID()) players[player]->teamUnits.erase(players[player]->teamUnits.begin() + i);
        }
        
        if (units.find(ID) != units.end())
        {
            delete units[ID];
            units.erase(ID);
        }
        if (buildings.find(ID) != buildings.end())
        {
            
            Buttons[to_string(ID)]->free();
            Buttons.erase(to_string(ID));
            if (buildings[ID]->sName == "Barracks")
            {
                TextBoxes[to_string(ID)]->free();
                TextBoxes.erase(to_string(ID));
            }
            delete buildings[ID];
            buildings.erase(ID);
        }
        if (projectiles.find(ID) != projectiles.end())
        {
            delete projectiles[ID];
            projectiles.erase(ID);
        }

        entityList.erase(ID);

    }

    void shootProjectile(Entity* entity, string projectile, int target)
    {
        int ID = -1;
        if (projectile == "Arrow")
        {
            Arrow* arrow = new Arrow();
            arrow->mPosition = entity->mPosition;
            arrow->setTeam(entity->getTeam());
            arrow->setTargetPosition(entityList[target]->mPosition);
            arrow->nAttack = entity->nAttack;
            arrow->nTargetID = target;
            ID = createEntity(arrow);
            projectiles[ID] = arrow;

        }
        else if (projectile == "Fireball")
        {
            Fireball* fireball = new Fireball();
            fireball->mPosition = entity->mPosition;
            fireball->setTeam(entity->getTeam());
            fireball->setTargetPosition(entityList[target]->mPosition);
            fireball->nAttack = entity->nAttack;
            fireball->nTargetID = target;
            ID = createEntity(fireball);
            projectiles[ID] = fireball;
        }
        else if (projectile == "Cannonball")
        {
            Cannonball* cannonball = new Cannonball();
            cannonball->mPosition = entity->mPosition;
            cannonball->setTeam(entity->getTeam());
            cannonball->setTargetPosition(entityList[target]->mPosition);
            cannonball->nAttack = entity->nAttack;
            cannonball->nTargetID = target;
            ID = createEntity(cannonball);
            projectiles[ID] = cannonball;
        }
        else if (projectile == "BulletMG")
        {
            BulletMG* bulletMG = new BulletMG();
            bulletMG->mPosition = entity->mPosition;
            bulletMG->setTeam(entity->getTeam());
            bulletMG->setTargetPosition(entityList[target]->mPosition);
            bulletMG->nAttack = entity->nAttack;
            bulletMG->nTargetID = target;
            ID = createEntity(bulletMG);
            projectiles[ID] = bulletMG;
        }
        
        
    }

    void gameAction(int player, int id, int argument = 0)
    {
        switch (id)
        {
        case 1:
            if (players[player]->teamBuildings.size() >= 1)
                if (players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower")
                spawnUnit("Footman", player);
            break;
        case 2:
            if (players[player]->teamBuildings.size() >= 1)
                if(players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower")
                    spawnUnit("Mage", player);
            break;
        case 3:
            if (players[player]->teamBuildings.size() >= 1)
                if (players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower" && players[player]->lockKnight == false)
                    spawnUnit("Knight", player);
            break;
        case 4:
            pause = !pause;
            break;
        case 5:

            if (players[player]->selectedBuildingID < players[player]->teamBuildings.size())
                players[player]->selectedBuilding()->select();
            for (int i = 0; i < players[player]->teamBuildings.size(); i++)
            {
                if (players[player]->teamBuildings[i]->getID() == argument)
                {
                    players[player]->selectedBuildingID = i;
                    players[player]->selectedBuilding()->select();
                    break;
                }
            }
            
            break;
        case 6:
            if (players[player]->teamBuildings.size() >= 1)
            {
                if (players[player]->selectedBuildingID < players[player]->teamBuildings.size())
                    players[player]->selectedBuilding()->upgrade(players[player]);
            }
            break;
        case 7:
            if (players[player]->teamBuildings.size() >= 1)
                if (players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower")
                    spawnUnit("Archer", player);
            break;
		case 8:
            players[player]->passiveGoldUpgrade();
            break;
        case 9:
            if (players[player]->teamBuildings.size() >= 1)
                if (players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower" && players[player]->tremendiniusAlive == false && players[player]->lockTremendinius == false)
                    spawnUnit("Tremendinius", player);
            break;
        case 10:
            if (players[player]->teamBuildings.size() >= 1)
                if (players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower")
                    spawnUnit("BigBird", player);
            break;
        case 11:
            if (players[player]->teamBuildings.size() >= 1)
                if (players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower" && players[player]->lockCannon == false)
                    spawnUnit("Cannon", player);
            break;
        case 12:
            if (players[player]->teamBuildings.size() >= 1)
                if (players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower" && players[player]->minigunAlive == false && players[player]->lockMinigun == false)
                    spawnUnit("Minigun", player);
            break;
        }

    }

    void spawnUnit(string unit, int player) {
        vector<Unit*> wave;

        if (unit == "Footman")
            wave.push_back(new Footman());

        else if (unit == "Mage")
            wave.push_back(new Mage());

        else if (unit == "Archer")
            wave.push_back(new Archer());

        else if (unit == "Knight")
            wave.push_back(new Knight());

        else if (unit == "Tremendinius")
            wave.push_back(new Tremendinius());

        else if (unit == "BigBird")
            wave.push_back(new BigBird());

        else if (unit == "Cannon")
            wave.push_back(new Cannon());

        else if (unit == "Minigun")
            wave.push_back(new Minigun());

        if (players[player]->getGold() < wave[0]->nTrainingCost) {
            wave.clear();
            return;
        }
        else {
            wave = players[player]->selectedBuilding()->spawnWave(wave);

            int ID = createEntity(wave[0]);
            players[wave[0]->getTeam()]->teamUnits.push_back(wave[0]);
            units[ID] = wave[0];

            players[player]->addGold(-(wave[0]->nTrainingCost));
            players[player]->spawnUnitCooldown = 30;

            if (unit == "Cannon" || unit == "Mage")         //Possible nerf to the all powerfull tactic "mage/cannon spam"
                players[player]->spawnUnitCooldown = 60;

            if (unit == "Tremendinius")
                players[player]->tremendiniusAlive = true;

            if (unit == "Minigun")
                players[player]->minigunAlive = true;

        }
    }
        
    void freeMemory()
    {

    }

protected:

};

int main(int argc, char* args[])
{
    Caelis_Chaos game;
    game.Start();

    return 0;
}

#endif