#ifndef CAELISCHAOS_H
#define CAELISCHAOS_H

/*
Caelis Chaos

Version 0.4.0 DevBuild 4

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
#include <functional>
#include "TobiGameEngine/TobiGameEngine.h"
#include "TobiGameEngine/RTS-utilities/Sprite.h"
#include "TobiGameEngine/RTS-utilities/Unit.h"
#include "TobiGameEngine/RTS-utilities/Building.h"
#include "TobiGameEngine/RTS-utilities/Player.h"
#include "TobiGameEngine/RTS-utilities/Projectile.h"

using namespace std;

string VersionString = "0.4.0 DevBuild 4";

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
        fHeight = 6;
        fWidth = 6;
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
            addMaxHealth(1000);
            player->addGold(-3000);
            player->unlockKnight();
            player->setHealthModifier(1.1f);
            setSprite(pSprites[1]);
        }
        else if (player->getGold() >= 5000 && nLevel == 2)
        {
            setLevel(3);
            addHealth(1500);
            addMaxHealth(1500);
            player->addGold(-5000);
            player->unlockTremendinius();
            player->unlockCannon();
            player->unlockKatyusha();
            player->setHealthModifier(1.2f);
            setSprite(pSprites[2]);
            fHeight = 7.0f;
            fWidth = 7.0f;
        }
    }

};

class Barracks : public Building
{
public:

    string pSprites[4];
    int heroCooldown;

    Barracks()
    {
        nHealth = 1200;
        nMaxHealth = 1200;
        sName = "Barracks";
        nLevel = 1;
        nKillReward = 500;

        pSprite = "res/textures/BarracksLevel_1.png";
        fHeight = 4.0f;
        fWidth = 4.0f;
        
        pSprites[0] = "res/textures/BarracksLevel_1.png";
        pSprites[1] = "res/textures/BarracksLevel_2.png";
        pSprites[2] = "res/textures/BarracksLevel_3.png";
        pSprites[3] = "res/textures/BarracksLevel_4.png";

        heroCooldown = 2000;
    }

    void upgrade(Player* player) override{
        if (player->getGold() >= 2000 && nLevel == 1)
        {
            setLevel(2);
            addHealth(500);
            addMaxHealth(500);
            player->addGold(-2000);
            setSprite(pSprites[1]);
        }
        else if (player->getGold() >= 3000 && nLevel == 2)
        {
            setLevel(3);
            addHealth(500);
            addMaxHealth(500);
            player->addGold(-3000);
            setSprite(pSprites[2]);
        }
        else if (player->getGold() >= 4000 && nLevel == 3)
        {
            setLevel(4);
            addHealth(500);
            addMaxHealth(500);
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
        fVisionRange = 6;

        pSprite = "res/textures/Tower.png";
        fHeight = 3.0f;
        fWidth = 2.0f;
    }

};

class Wall : public Entity
{
public:

    Wall()
    {
        nHealth = 999999;
        nMaxHealth = 999999;
        sName = "Wall";
        isCollidable = true;

        pSprite = "res/textures/Tower.png";
        fHeight = 2.0f;
        fWidth = 2.0f;
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

    enum teamColor
    {
        blue, red, cyan, yellow
    };

    enum cursorModes
    {
        select, place
    };

    enum unitTypes
    {
        melee,
        range,
        mage,
        mounted,
        heavy,
        siege,
        hero1,
        hero2
    };

    enum upgradeTypes
    {
        health,
        attack1,
        attack2,
        passiveGold
    };

    struct placedUnit
    {
        string type;
        int team;
    };

//Match Settings

    bool bDebugMatch = false;
    int nTicksPerSecond = 30;

//Match Pointers

    unordered_map<string, Unit> unitPrototypes;
    unordered_map<string, Building> buildingPrototypes;
    unordered_map<string, Upgrade> upgradePrototypes;

    unordered_map<int, Unit*> units;
    unordered_map<int, Building*> buildings;
    unordered_map<int, Projectile*> projectiles;
    vector<Player*> players;
    Player* currentPlayer;

    Unit* selectedUnit;


//Match Attributes

    int tickCounter = 0;
    int secondCounter = -10;
    bool bWin = false;
    bool bGameOver = false;
    int randomSeed;

//Match Multiplayer Attributes

    int lastAction = 0;
    int turn = 0;
    int nextTurn = 0;
    int ticksSinceLastTurn = 0;
    bool turnSent = false;
    pair<int, int> playerActions[4];
    queue<pair<int, int>> actionQueue;

// Miscelaneous

    bool log = false;
    bool bHoldKey[256] = { false };
    const Uint8* bKey = SDL_GetKeyboardState(NULL);
    
    SDL_Color teamColors[4][4];
    bool textInputMode = false;
    string textInput;

// Cursor

    int cursorMode = select;
    placedUnit unitPlaced = {"NONE", 0};

// Graphic Settings

    bool bDebugMode = false;
    bool bShowGrid = true;
    bool bShowHealthBars = true;
    float fScreenRatio = (float)m_nScreenWidth / (float)m_nScreenHeight;
    float fVerticalTilesInScreen = (float)m_nScreenHeight / (float)nTileSize;
    float fHorizontalTilesInScreen = (float)m_nScreenWidth / (float)nTileSize;
    float fScale = 1;
    int nTileSize = 64;

    float fScreenLeftBorder;
    float fScreenRightBorder;
    float fScreenTopBorder;
    float fScreenBottomBorder;


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

    
    string Username;

public:

    virtual void CreateGUI()
    {
        if (m_nGameState == initializing)
        {
            createWindow("Caelis Chaos " + VersionString);
            m_Font = TTF_OpenFont("res/fonts/PixeloidSans-mLxMm.ttf", 50);
            m_nGameState = startMenu;
        }

        if (m_nGameState == startMenu)
        {
            TextBoxes["startMenu Title"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["startMenu Title"]->setPosition(0.2f, 0.05f);
            TextBoxes["startMenu Title"]->setSize(0.6f, 0.15f);
            TextBoxes["startMenu Title"]->setFontSize(200);
            TextBoxes["startMenu Title"]->setText("Caelis Chaos");
            TextBoxes["startMenu Title"]->setTextColor({ 0x00, 0x00, 0x00 });
            TextBoxes["startMenu Title"]->showBorder(false);

            Menus["Start Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Start Menu"]->setPosition(0.3f, 0.3f);
            Menus["Start Menu"]->setSize(0.4f, 0.60f);
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
            TextBoxes["Configuration Menu Title"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Configuration Menu Title"]->setPosition(0.2f, 0.05f);
            TextBoxes["Configuration Menu Title"]->setSize(0.6f, 0.15f);
            TextBoxes["Configuration Menu Title"]->setFontSize(200);
            TextBoxes["Configuration Menu Title"]->setTextColor({ 0x00, 0x00, 0x00 });
            TextBoxes["Configuration Menu Title"]->setAlignment("CENTERED");
            TextBoxes["Configuration Menu Title"]->showBorder(false);
            if (mLanguage == "English")
            {
                TextBoxes["Configuration Menu Title"]->setText("Settings");
            }
            else if (mLanguage == "Spanish")
            {
                TextBoxes["Configuration Menu Title"]->setText("Configuracion");
            }

            Menus["Configuration Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Configuration Menu"]->setPosition(0.3f, 0.2f);
            Menus["Configuration Menu"]->setSize(0.4f, 0.60f);
            Menus["Configuration Menu"]->setTableSize(4, 1);
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
        
        else if (m_nGameState == singleplayerMenu)
        {
            TextBoxes["Singleplayer Menu Title"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Singleplayer Menu Title"]->setPosition(0.2f, 0.05f);
            TextBoxes["Singleplayer Menu Title"]->setSize(0.6f, 0.15f);
            TextBoxes["Singleplayer Menu Title"]->setFontSize(200);
            TextBoxes["Singleplayer Menu Title"]->setText("Choose a match type");
            TextBoxes["Singleplayer Menu Title"]->setTextColor({ 0x00, 0x00, 0x00 });
            TextBoxes["Singleplayer Menu Title"]->setAlignment("CENTERED");
            TextBoxes["Singleplayer Menu Title"]->showBorder(false);
            if (mLanguage == "English")
            {
                TextBoxes["Singleplayer Menu Title"]->setText("Choose a match type");
            }
            else if (mLanguage == "Spanish")
            {
                TextBoxes["Singleplayer Menu Title"]->setText("Elige el tipo de partida");
            }

            Menus["Singleplayer Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Singleplayer Menu"]->setPosition(0.3f, 0.2f);
            Menus["Singleplayer Menu"]->setSize(0.4f, 0.45f);
            Menus["Singleplayer Menu"]->setTableSize(3, 1);
            Menus["Singleplayer Menu"]->enable(true);
            if (mLanguage == "English")
            {
                Menus["Singleplayer Menu"]->addButton("1 Normal", "Normal");
                Menus["Singleplayer Menu"]->addButton("2 Debug", "Debug");
                Menus["Singleplayer Menu"]->addButton("3 Return", "Return");
            }
            else if (mLanguage == "Spanish")
            {
                Menus["Singleplayer Menu"]->addButton("1 Normal", "Normal");
                Menus["Singleplayer Menu"]->addButton("2 Debug", "Debug");
                Menus["Singleplayer Menu"]->addButton("3 Return", "Volver");
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
            TextBoxes["IP"]->setText(IP);
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
            Menus["Barracks"]->setLayer(1);
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
                Menus["Barracks"]->addButton("9 Train Katyusha", "Katyusha");
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
                Menus["Barracks"]->addButton("9 Train Katyusha", "Katyusha");
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
                building.second->selectionBox = new Button(m_Renderer, m_Window, m_Font);
                building.second->selectionBox->setVisibility(false);
                building.second->selectionBox->setLayer(2);
                Buttons[to_string(building.second->getID())] = building.second->selectionBox;

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

            for (auto& unit : units)
            {
                unit.second->selectionBox = new Button(m_Renderer, m_Window, m_Font);
                unit.second->selectionBox->setVisibility(false);
                unit.second->selectionBox->setLayer(2);
                Buttons[to_string(unit.second->getID())] = unit.second->selectionBox;
            }

            Menus["Fortress"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Fortress"]->setPosition(0.75f, 0.7f);
            Menus["Fortress"]->setSize(0.25f, 0.3f);
            Menus["Fortress"]->setTableSize(2, 3);
            Menus["Fortress"]->setLayer(1);
            Menus["Fortress"]->enable(false);
            if (mLanguage == "English")
            {
                Menus["Fortress"]->addButton("1 Upgrade Building", "Upgrade");
                Menus["Fortress"]->addButton("2 Placeholder", "");
                Menus["Fortress"]->addButton("3 Passive Gold", "Passive Gold");
                Menus["Fortress"]->addButton("4 Attack1", "Sharper Blades");
                Menus["Fortress"]->addButton("5 Attack2", "Pointy Arrows");
                Menus["Fortress"]->addButton("6 Health", "Better Training");
            }
                
            else if (mLanguage == "Spanish")
            {
                Menus["Fortress"]->addButton("1 Upgrade Building", "Mejorar");
                Menus["Fortress"]->addButton("2 Placeholder", "");
                Menus["Fortress"]->addButton("3 Passive Gold", "Oro pasivo");
                Menus["Fortress"]->addButton("4 Attack1", "Espadas filosas");
                Menus["Fortress"]->addButton("5 Attack2", "Flechas puntiagudas");
                Menus["Fortress"]->addButton("6 Health", "Mejor entrenamiento");
            }

            TextBoxes["Victory"] = new TextBox(m_Renderer, m_Window, m_Font);
            TextBoxes["Victory"]->setPosition(0.42f, 0.3f);
            TextBoxes["Victory"]->setSize(0.16f, 0.2f);
            TextBoxes["Victory"]->setFontSize(70);
            TextBoxes["Victory"]->showBorder(true);
            TextBoxes["Victory"]->enable(false);
            if (mLanguage == "English")
                TextBoxes["Victory"]->setText("Victory!");
            else if (mLanguage == "Spanish")
                TextBoxes["Victory"]->setText("Victoria!");

            Menus["Escape Menu"] = new Menu(m_Renderer, m_Window, m_Font);
            Menus["Escape Menu"]->setPosition(0.35f, 0.3f);
            Menus["Escape Menu"]->setSize(0.3f, 0.5f);
            Menus["Escape Menu"]->setTableSize(4, 1);
            Menus["Escape Menu"]->setLayer(1);
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
            Menus["Settings Menu"]->setSize(0.4f, 0.60f);
            Menus["Settings Menu"]->setTableSize(4, 1);
            Menus["Settings Menu"]->setLayer(1);
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
            Buttons["Escape"]->setLayer(1);

            Lists["Data"] = new ListUI(m_Renderer, m_Window, m_Font);
            Lists["Data"]->setPosition(0.21f, 0.0f);
            Lists["Data"]->setSize(0.4f, 0.2f);
            Lists["Data"]->setFontSize(20);
            Lists["Data"]->setTextColor({ 0xFF, 0xFF, 0xFF });
            Lists["Data"]->setBackgroundColor({ 0x00, 0x62, 0x41 });
            Lists["Data"]->showBorder(false);
            Lists["Data"]->enable(false);
            Lists["Data"]->setTableSize(4, 1);
            Lists["Data"]->addItem("Tile Size", "Tile size: ");
            Lists["Data"]->addItem("FPS", "FPS: ");
            Lists["Data"]->addItem("Entities", "Entities: ");
            Lists["Data"]->addItem("TpS", "Ticks per Second: ");

            unitHUD = new UnitHUD(m_Renderer, m_Window, m_Font);
            unitHUD->setPosition(0.4f, 0.8f);
            unitHUD->setSize(0.3f, 0.2f);
            unitHUD->setLayer(1);
            unitHUD->enable(false);

            if (bDebugMatch)
            {
                DropdownMenus["Unit Selector"] = new DropdownMenu(m_Renderer, m_Window, m_Font);
                DropdownMenus["Unit Selector"]->setTitle("Units");
                DropdownMenus["Unit Selector"]->setPosition(0.0f, 0.2f);
                DropdownMenus["Unit Selector"]->setSize(0.15f, 0.5f);
                DropdownMenus["Unit Selector"]->setButtonSize(0.15f, 0.05f);
                DropdownMenus["Unit Selector"]->setLayer(1);
                DropdownMenus["Unit Selector"]->enable(true);
                if (mLanguage == "English")
                {
                    for (auto unit : unitPrototypes)
                    {
                        DropdownMenus["Unit Selector"]->addItem(unit.first, unit.second.sName);
                    }                 
                }
                else if (mLanguage == "Spanish")
                {
                    for (auto unit : unitPrototypes)
                    {
                        DropdownMenus["Unit Selector"]->addItem(unit.first, unit.second.sName);
                    }
                }

                DropdownMenus["Team Selector"] = new DropdownMenu(m_Renderer, m_Window, m_Font);
                DropdownMenus["Team Selector"]->setTitle("Team");
                DropdownMenus["Team Selector"]->setPosition(0.0f, 0.245f);
                DropdownMenus["Team Selector"]->setSize(0.15f, 0.2f);
                DropdownMenus["Team Selector"]->setButtonSize(0.15f, 0.05f);
                DropdownMenus["Team Selector"]->setLayer(2);
                DropdownMenus["Team Selector"]->enable(true);
                if (mLanguage == "English")
                {
                    DropdownMenus["Team Selector"]->addItem("1 Blue", "Blue");
                    DropdownMenus["Team Selector"]->addItem("2 Red", "Red");
                    DropdownMenus["Team Selector"]->addItem("3 Cyan", "Cyan");
                    DropdownMenus["Team Selector"]->addItem("4 Yellow", "Yellow");
                }
                else if (mLanguage == "Spanish")
                {
                    DropdownMenus["Team Selector"]->addItem("1 Blue", "Blue");
                    DropdownMenus["Team Selector"]->addItem("2 Red", "Red");
                    DropdownMenus["Team Selector"]->addItem("3 Cyan", "Cyan");
                    DropdownMenus["Team Selector"]->addItem("4 Yellow", "Yellow");
                }
            }
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
                            SetConfiguration();
                            DestroyGUI();
                            m_nGameState = usernameInput;
                            CreateGUI();
                            bHoldKey[SDL_SCANCODE_RETURN] = true;
                        }
                        else
                            bHoldKey[SDL_SCANCODE_RETURN] = false;
                    }
                }

                if (m_nGameState == usernameInput && textInputMode == true)
                {
                    if (bKey[SDL_SCANCODE_RETURN] && textInputMode)
                    {
                        if (!bHoldKey[SDL_SCANCODE_RETURN])
                        {
                            if (TextBoxes["Username"]->mText.length() > 0)
                            {
                                Username = TextBoxes["Username"]->mText.c_str();
                                textInputMode = false;
                                DestroyGUI();
                                m_nGameState = matchLobby;
                                CreateGUI();
                            }
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
                m_nGameState = singleplayerMenu;
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

        else if (m_nGameState == singleplayerMenu)
        {

            if (Menus["Singleplayer Menu"]->Buttons["1 Normal"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = inMatch;
                CreateGUI();
            }
            else if (Menus["Singleplayer Menu"]->Buttons["2 Debug"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = inMatch;
                bDebugMatch = true;
                CreateGUI();
            }
            else if (Menus["Singleplayer Menu"]->Buttons["3 Return"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = startMenu;
                CreateGUI();
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
                changeScreenResolution();
                Menus["Configuration Menu"]->Buttons["2 Resolution"]->bPressed = false;
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
                SetConfiguration();
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
                Menus["Username Menu"]->Buttons["1 Join"]->bPressed = false;
                if (TextBoxes["Username"]->mText.length() > 0)
                {
                    Username = TextBoxes["Username"]->mText.c_str();
                    textInputMode = false;
                    DestroyGUI();
                    m_nGameState = matchLobby;
                    CreateGUI();
                }
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
                if (Menus["Lobby Menu"]->Buttons["1 Start"]->bPressed && client_map.size() > 0)
                {
                    BroadcastPacket(server, "5|\0");
                    m_nGameState = inMatch;
                    Menus["Lobby Menu"]->Buttons["1 Start"]->bPressed = false;
                }
                else if (Menus["Lobby Menu"]->Buttons["1 Start"]->bPressed && client_map.size() == 0)
                {
                    Menus["Lobby Menu"]->Buttons["1 Start"]->bPressed = false;
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

        else if (m_nGameState == inMatch && bServer)
        {
            if (Menus["Lobby Menu"]->Buttons["2 Return"]->bPressed)
            {
                DestroyGUI();
                m_nGameState = startMenu;
                enet_host_destroy(server);
                textInputMode = false;
                bServer = false;
                bMultiplayer = false;
                client_map.clear();
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
        while (SDL_PollEvent(&m_Event) != 0)
        {

            GUIInput();
            //User requests quit
            if (m_Event.type == SDL_QUIT)
            {
                close();
            }
        }

        // Handles turns
        if (m_nGameState == inMatch)
        {
            UpdateMenu();
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
            return EXIT_FAILURE;
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

            GUIInput();
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

    virtual void Input(float fElapsedTime)
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
                    if (bKey[SDL_SCANCODE_RIGHT]) if (currentPlayer->getCameraX() <= 80)     currentPlayer->setCamera({ currentPlayer->getCameraX() + (400.0f * fElapsedTime / (fScale / 2.0f)), currentPlayer->getCameraY() });
                    if (bKey[SDL_SCANCODE_LEFT]) if (currentPlayer->getCameraX() >= -80)      currentPlayer->setCamera({ currentPlayer->getCameraX() + (-400.0f * fElapsedTime / (fScale / 2.0f)), currentPlayer->getCameraY() });
                    if (bKey[SDL_SCANCODE_DOWN]) if (currentPlayer->getCameraY() <= 80)     currentPlayer->setCamera({ currentPlayer->getCameraX(), currentPlayer->getCameraY() + (400.0f * fElapsedTime / (fScale / 2.0f)) });
                    if (bKey[SDL_SCANCODE_UP]) if (currentPlayer->getCameraY() >= -80)      currentPlayer->setCamera({ currentPlayer->getCameraX(), currentPlayer->getCameraY() + (-400.0f * fElapsedTime / (fScale / 2.0f)) });

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

                    // "Left ALT" - Show/Hide health bars
                    if (bKey[SDL_SCANCODE_LALT])
                    {
                        if (!bHoldKey[SDL_SCANCODE_LALT]) {
                            bShowHealthBars = !bShowHealthBars;
                        }
                        bHoldKey[SDL_SCANCODE_LALT] = true;
                    }
                    else
                        bHoldKey[SDL_SCANCODE_LALT] = false;

                    // "F3" - Active/Deactivate debug mode
                    if (bKey[SDL_SCANCODE_F3])
                    {
                        if (!bHoldKey[SDL_SCANCODE_F3]) {
                            bDebugMode = !bDebugMode;
                            if (bDebugMode) Lists["Data"]->enable(true);
                            else Lists["Data"]->enable(false);
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
                                changeScreenResolution();
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
                    keystrokeHandle(SDL_SCANCODE_F, 1, melee);

                    // "T" - Train Tremendiñus 
                    keystrokeHandle(SDL_SCANCODE_T, 1, hero2);

                    // "Esc" - Open escape menu
                    if (bKey[SDL_SCANCODE_ESCAPE])
                    {

                        if (cursorMode == place) cursorMode = select;

                        else
                        {
                            Menus["Escape Menu"]->enable(!Menus["Escape Menu"]->isEnabled());
                            if (Menus["Settings Menu"]->isEnabled()) Menus["Settings Menu"]->enable(false);
                        }
                        
                    }

                    // "P" - Pause
                    keystrokeHandle(SDL_SCANCODE_P, 4);

                    // "M" - Train mage
                    keystrokeHandle(SDL_SCANCODE_M, 1, mage);

                    // "K" - Train knight
                    keystrokeHandle(SDL_SCANCODE_K, 1, heavy);

                    //"1" Building select
                    keystrokeHandle(SDL_SCANCODE_1, 5);

                    //"2" Building upgrade
                    keystrokeHandle(SDL_SCANCODE_2, 6);

                    //"3" - Passive gold upgrade
                    keystrokeHandle(SDL_SCANCODE_3, 8);

                    //"A" Train Archer
                    keystrokeHandle(SDL_SCANCODE_A, 1, range);

                    //"B" Train BigBird
                    keystrokeHandle(SDL_SCANCODE_B, 1, mounted);

                    //"Q" Train Cannon
                    keystrokeHandle(SDL_SCANCODE_Q, 1, siege);

                    //"G" Train Katyusha
                    keystrokeHandle(SDL_SCANCODE_G, 1, hero1);

                }

            }

            GUIInput();

            if (Menus["Barracks"]->Buttons["2 Train Footman"]->bPressed)
            {
                playerAction(1, melee);
                Menus["Barracks"]->Buttons["2 Train Footman"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["3 Train Archer"]->bPressed)
            {
                playerAction(1, range);
                Menus["Barracks"]->Buttons["3 Train Archer"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["4 Train Mage"]->bPressed)
            {
                playerAction(1, mage);
                Menus["Barracks"]->Buttons["4 Train Mage"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["5 Train Big Bird"]->bPressed)
            {
                playerAction(1, mounted);
                Menus["Barracks"]->Buttons["5 Train Big Bird"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["6 Train Cannon"]->bPressed)
            {
                playerAction(1, siege);
                Menus["Barracks"]->Buttons["6 Train Cannon"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["7 Train Knight"]->bPressed)
            {
                playerAction(1, heavy);
                Menus["Barracks"]->Buttons["7 Train Knight"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["8 Train Tremendinius"]->bPressed)
            {
                playerAction(1, hero2);
                Menus["Barracks"]->Buttons["8 Train Tremendinius"]->bPressed = false;
            }
            else if (Menus["Barracks"]->Buttons["9 Train Katyusha"]->bPressed)
            {
                playerAction(1, hero1);
                Menus["Barracks"]->Buttons["9 Train Katyusha"]->bPressed = false;
            }

            else if (Menus["Barracks"]->Buttons["1 Upgrade Building"]->bPressed)
            {
                if (currentPlayer->selectedBuilding() != NULL)
                    if (currentPlayer->selectedBuilding()->sName == "Barracks")
                        playerAction(3, currentPlayer->selectedBuildingID);
                Menus["Barracks"]->Buttons["1 Upgrade Building"]->bPressed = false;
            }

            else if (Menus["Fortress"]->Buttons["1 Upgrade Building"]->bPressed)
            {
                if (currentPlayer->selectedBuilding() != NULL)
                    if (currentPlayer->selectedBuilding()->sName == "Fortress")
                        playerAction(3, currentPlayer->selectedBuildingID);
                Menus["Fortress"]->Buttons["1 Upgrade Building"]->bPressed = false;
            }

            else if (Menus["Fortress"]->Buttons["2 Placeholder"]->bPressed)
            {
                Menus["Fortress"]->Buttons["2 Placeholder"]->bPressed = false;
            }

            else if (Menus["Fortress"]->Buttons["3 Passive Gold"]->bPressed)
            {
                playerAction(2, passiveGold);
                Menus["Fortress"]->Buttons["3 Passive Gold"]->bPressed = false;
            }

            else if (Menus["Fortress"]->Buttons["4 Attack1"]->bPressed)
            {
                playerAction(2, attack1);
                Menus["Fortress"]->Buttons["4 Attack1"]->bPressed = false;
            }

            else if (Menus["Fortress"]->Buttons["5 Attack2"]->bPressed)
            {
                playerAction(2, attack2);
                Menus["Fortress"]->Buttons["5 Attack2"]->bPressed = false;
            }

            else if (Menus["Fortress"]->Buttons["6 Health"]->bPressed)
            {
                playerAction(2, health);
                Menus["Fortress"]->Buttons["6 Health"]->bPressed = false;
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

                if (bMultiplayer)
                {
                    bMultiplayer = false;
                    enet_host_destroy(client);
                }

                m_nGameState = startMenu;
                DestroyGUI();
                CreateGUI();
                return;
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
                Menus["Settings Menu"]->enable(true);
            }
            else if (Menus["Settings Menu"]->Buttons["2 Resolution"]->bPressed)
            {
                changeScreenResolution();
                Menus["Settings Menu"]->Buttons["2 Resolution"]->bPressed = false;
                Menus["Settings Menu"]->enable(true);
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
                Menus["Settings Menu"]->enable(true);
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

                else
                {
                    int bID = building.second->getID();
                    Buttons[to_string(bID)]->bPressed = false;
                }
            }

            for (auto& unit : units)
            {

                int uID = unit.second->getID();
                if (Buttons[to_string(uID)]->bPressed)
                {
                    selectedUnit = unit.second;
                    gameAction(currentPlayer->getTeam(), 5, -1);
                    Buttons[to_string(uID)]->bPressed = false;
                }

            }

            if (bDebugMatch)
            {
                for (auto button : DropdownMenus["Unit Selector"]->menu->Buttons)
                {
                    
                    if (button.second->bPressed)
                    {
                        cursorMode = place;
                        unitPlaced.type = button.first;
                        button.second->bPressed = false;
                        return;
                    }
                }
                
                int t = 0;
                for (auto button : DropdownMenus["Team Selector"]->menu->Buttons)
                {
                    
                    if (button.second->bPressed)
                    {
                        unitPlaced.team = t;
                        button.second->bPressed = false;
                        return;
                    }
                    t++;
                }

                if (cursorMode == place && unitPlaced.type != "NONE" && cursorLayer == 0)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    if (m_Event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        placeUnit(unitPlaced.type, unitPlaced.team, currentPlayer->getCameraX() + (x - m_nScreenWidth / 2) / nTileSize, currentPlayer->getCameraY() + (y - m_nScreenHeight / 2) / nTileSize);
                    }
                }



            }


            
        }


        if (!Menus["Escape Menu"]->isEnabled() && !Menus["Settings Menu"]->isEnabled())
        {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (x > m_nScreenWidth - m_nScreenWidth / 30)
            {
                if (currentPlayer->getCameraX() <= 80)     currentPlayer->setCamera({ currentPlayer->getCameraX() + (30.0f * fElapsedTime / (fScale / 2.0f)), currentPlayer->getCameraY() });
            }
            else if (x < m_nScreenWidth / 30)
            {
                if (currentPlayer->getCameraX() >= -80)     currentPlayer->setCamera({ currentPlayer->getCameraX() - (30.0f * fElapsedTime / (fScale / 2.0f)), currentPlayer->getCameraY() });
            }
            if (y > m_nScreenHeight - m_nScreenHeight / 30)
            {
                if (currentPlayer->getCameraY() <= 80)     currentPlayer->setCamera({ currentPlayer->getCameraX(), currentPlayer->getCameraY() + (30.0f * fElapsedTime / (fScale / 2.0f)) });
            }
            else if (y < m_nScreenHeight / 30)
            {
                if (currentPlayer->getCameraY() >= -80)     currentPlayer->setCamera({ currentPlayer->getCameraX(), currentPlayer->getCameraY() - (30.0f * fElapsedTime / (fScale / 2.0f)) });
            }
        }

        

    }

    void placeUnit(string unitType, int team, float x, float y)
    {
        Unit* unit = new Unit(unitPrototypes[unitType]);
        

        if (unit != NULL)
        {
            unit->setTeam(team);
            unit->setCoords(x, y);
        }

        int ID = createEntity(unit);
        players[team]->teamUnits.push_back(unit);
        units[ID] = unit;
    }

    void changeScreenResolution()
    {
        if (!bFullscreen)
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
            SetConfiguration();
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
        loadEntities();
        loadUpgrades();
        loadMap();
        createPlayers();

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
        for (auto& trigger : Triggers)
        {
            delete trigger;
        }
        Triggers.clear();
        buildings.clear();
        units.clear();
        projectiles.clear();
        unitPrototypes.clear();
        buildingPrototypes.clear();
        upgradePrototypes.clear();
        
        tickCounter = 0;
        lastAction = 0;
        turn = 0;
        nextTurn = 0;
        ticksSinceLastTurn = 0;
        pause = false;
        bDebugMatch = false;
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

            for (auto building : buildings)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (building.second->abilityCooldown[i] > 0) building.second->abilityCooldown[i]--;
                }
            }
            
            for (int i = 0; i < players.size(); i++)
            {
                players[i]->spawnUnitCooldown--;
                if (players[i]->teamBuildings.size() == 0)
                {
                    players[i]->defeated = true;
                    players[i]->alive = false;
                }
            }

            tickCounter++;

            if (tickCounter == 1 || tickCounter % 1350 == 0)
            {
                for (int i = 0; i < (int)players.size(); i++)
                {
                    players[i]->addGold(players[i]->nPassiveGold);

                    for (int a = 0; a < (int)players[i]->teamBuildings.size(); a++)
                    {
                        if (players[i]->teamBuildings[a]->sName == "Barracks")
                        {
                            vector<Unit*> wave;
                            wave.push_back(new Unit(players[i]->unitPrototypes["Melee"]));
                            wave.push_back(new Unit(players[i]->unitPrototypes["Melee"]));
                            wave.push_back(new Unit(players[i]->unitPrototypes["Melee"]));
                            wave.push_back(new Unit(players[i]->unitPrototypes["Range"]));
                            wave.push_back(new Unit(players[i]->unitPrototypes["Range"]));
                            wave.push_back(new Unit(players[i]->unitPrototypes["Mage"]));

                            if (players[i]->teamBuildings[a]->getLevel() >= 2)
                            {
                                wave.push_back(new Unit(players[i]->unitPrototypes["Mounted"]));
                                wave.push_back(new Unit(players[i]->unitPrototypes["Mounted"]));
                            }
                            if (players[i]->teamBuildings[a]->getLevel() >= 3)
                            {
                                wave.push_back(new Unit(players[i]->unitPrototypes["Melee"]));
                                wave.push_back(new Unit(players[i]->unitPrototypes["Range"]));
                                wave.push_back(new Unit(players[i]->unitPrototypes["Mage"]));
                                wave.push_back(new Unit(players[i]->unitPrototypes["Knight"]));
                            }
                            if (players[i]->teamBuildings[a]->getLevel() >= 4)
                            {
                                wave.push_back(new Unit(players[i]->unitPrototypes["Mounted"]));
                                wave.push_back(new Unit(players[i]->unitPrototypes["Range"]));
                                wave.push_back(new Unit(players[i]->unitPrototypes["Siege"]));
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
                            if (cDistance(building.second->mPosition, unit.second->mPosition) < building.second->fVisionRange)
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
                    
                    for (auto trigger : Triggers) trigger->activate(unit.second);

                    if (cDistance(unit.second->mPosition, unit.second->mTargetPosition) >= unit.second->fAttackRange + unit.second->fWidth / 2.0f)
                    {
                        unit.second->checkCollition(entityList);
                        Vector2D previousPosition = unit.second->mPosition;

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
                                    if (id != -1) unit.second->setDefaultTarget(buildings[id]->mPosition);
                                }
                                
                            }
                        }
                    }
                        
                       

                    if (unit.second->getTargetUnit() == -1 || cDistance(units[unit.second->getTargetUnit()]->mPosition, unit.second->mPosition) > unit.second->fAttackRange)
                    {
                        int id = -1;
                        float min = unit.second->fVisionRange;
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
                            shootProjectile(unit.second, unit.second->attack(units[unit.second->getTargetUnit()], entityList), unit.second->getTargetUnit());
                        }
                    }
                    else
                    {
                        if (unit.second->getTargetBuilding() >= 0)
                        {
                            unit.second->setTargetPosition(buildings[unit.second->getTargetBuilding()]->mPosition);

                            if (cDistance(unit.second->mPosition, unit.second->mTargetPosition) < unit.second->fAttackRange + buildings[unit.second->getTargetBuilding()]->fWidth / 2.0f + unit.second->fWidth / 2.0f)
                            {
                                shootProjectile(unit.second, unit.second->attack(buildings[unit.second->getTargetBuilding()], entityList), unit.second->getTargetBuilding());
                            }
                        }
                        else
                        {
                            for (auto& building : buildings)
                            {
                                if (unit.second->getTeam() != building.second->getTeam())
                                {
                                    if (cDistance(unit.second->mPosition, building.second->mPosition) < unit.second->fVisionRange && unit.second->getTargetBuilding() == -1)
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

                            if (unit.second->sName == "Katyusha") players[player]->KatyushaAlive = false;

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

                        if (players[owner]->selectedBuilding() == building.second)
                        {
                            players[owner]->selectedBuildingID = -1;
                        }
                        
                        destroyEntity(building.second->getID());
                        break;
                    }
                }


            }

            // Player AI
            if (tickCounter % 60 == 0)
            {
                for (int i = 0; i < (int)players.size(); i++)
                {
                    if (players[i]->isAI())
                    {
                        int AIaction = rand() % 12 + 1;
                        if (players[i]->teamBuildings.size() > 1)
                        {
                            if (tickCounter < 3000)
                            {
                                AIPlan(i, AIaction);
                            }
                            else if (tickCounter < 6000 && players[i]->getGold() > 1000)
                            {
                                AIPlan(i, AIaction);
                            }
                            else if (tickCounter < 9000 && players[i]->getGold() > 2000)
                            {
                                AIPlan(i, AIaction);
                            }
                            else if (tickCounter < 12000 && players[i]->getGold() > 3000)
                            {
                                AIPlan(i, AIaction);
                            }
                            else if (tickCounter < 15000 && players[i]->getGold() > 4000)
                            {
                                AIPlan(i, AIaction);
                            }
                            else if (players[i]->getGold() > 5000)
                            {
                                AIPlan(i, AIaction);
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

    void AIPlan(int player, int AIaction)
    {
        if (AIaction == 1)
        {
            int tUnit = rand() % players[player]->unitPrototypes.size();
            gameAction(player, 1, tUnit);
        }
        else if (AIaction == 2)
        {
            int tUpgrade = rand() % players[player]->upgrades.size();
            gameAction(player, 2, tUpgrade);
        }
        else if (AIaction == 3)
        {
            if (players[player]->selectedBuilding() != NULL)
            {
                if (players[player]->selectedBuilding()->sName != "Tower")
                    gameAction(player, 3, players[player]->selectedBuildingID);
            }          
        }
        else if (AIaction == 5)
        {
            int tBuilding = rand() % (int)players[player]->teamBuildings.size();
            int counter = 0;
            while (players[player]->teamBuildings[tBuilding]->sName == "Tower" || counter >= 10)
            {
                tBuilding = rand() % (int)players[player]->teamBuildings.size();
                counter++;
            }
            int argument = players[player]->teamBuildings[tBuilding]->getID();

            gameAction(player, AIaction, argument);
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
        
            fScreenLeftBorder = currentPlayer->getCameraX() - (fHorizontalTilesInScreen / 2.0f);
            fScreenRightBorder = currentPlayer->getCameraX() + (fHorizontalTilesInScreen / 2.0f);
            fScreenTopBorder = currentPlayer->getCameraY() - (fVerticalTilesInScreen / 2.0f);
            fScreenBottomBorder = currentPlayer->getCameraY() + (fVerticalTilesInScreen / 2.0f);

            int objectsToRender = 0;
        
            for (auto& entity : entityList)
            {
                if ((entity.second->mPosition.x > fScreenLeftBorder - entity.second->fWidth && entity.second->mPosition.x - entity.second->fWidth < fScreenRightBorder) && (entity.second->mPosition.y > fScreenTopBorder - entity.second->fHeight && entity.second->mPosition.y - entity.second->fHeight < fScreenBottomBorder))
                {
                    int entityScreenLocationX = (int)((float)(entity.second->mPosition.x - currentPlayer->getCameraX() - (float)(entity.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                    int entityScreenLocationY = (int)((float)(entity.second->mPosition.y - currentPlayer->getCameraY() - (float)(entity.second->fHeight / 2.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);

                    objectsToRender++;
                    renderEntity(entity.second, entityScreenLocationX, entityScreenLocationY, false);

                }

                //if ((entity.second->mPosition.x > fScreenLeftBorder - entity.second->fWidth && entity.second->mPosition.x - entity.second->fWidth < fScreenRightBorder) && (entity.second->mPosition.y > fScreenTopBorder - entity.second->fHeight && entity.second->mPosition.y - entity.second->fHeight < fScreenBottomBorder))
                //{
                //    objectsToRender++;
                //    int entityScreenLocationX = (int)((float)(entity.second->mPosition.x - currentPlayer->getCameraX() - (float)(entity.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                //    int entityScreenLocationY = (int)((float)(entity.second->mPosition.y - currentPlayer->getCameraY() - (float)(entity.second->fHeight / 2.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);
                //    
                //    int RentityScreenLocationX = (int)((float)(entity.second->mPosition.x - currentPlayer->getCameraX()) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                //    int RentityScreenLocationY = (int)((float)(entity.second->mPosition.y - currentPlayer->getCameraY()) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);
                //
                //    int realWidth = entity.second->fWidth * nTileSize;
                //    int realHeight = entity.second->fHeight * nTileSize;
                //
                //    
                //
                //    int team = entity.second->getTeam();
                //
                //    auto it = m_Textures[team].find(entity.second->pSprite);
                //
                //    if (entity.second->pSprite != "" && (it == m_Textures[team].end() || it->second.mTexture == NULL))
                //    {
                //        m_Textures[team].insert({ entity.second->pSprite, LTexture(m_Renderer, m_Window) });
                //
                //        m_Textures[team][entity.second->pSprite].loadPixelsFromFile(entity.second->pSprite.c_str());
                //
                //        //Get pixel data
                //        Uint32* pixels = m_Textures[team][entity.second->pSprite].getPixels32();
                //        int pixelCount = m_Textures[team][entity.second->pSprite].getPitch32() * m_Textures[team][entity.second->pSprite].getHeight();
                //
                //        //Map colors
                //        Uint32 colorKey[4];
                //        colorKey[0] = m_Textures[team][entity.second->pSprite].mapRGBA(0xFA, 0xFA, 0xFA, 0xFF);
                //        colorKey[1] = m_Textures[team][entity.second->pSprite].mapRGBA(0xE3, 0xE3, 0xE3, 0xFF);
                //        colorKey[2] = m_Textures[team][entity.second->pSprite].mapRGBA(0xC9, 0xC9, 0xC9, 0xFF);
                //        colorKey[3] = m_Textures[team][entity.second->pSprite].mapRGBA(0xB0, 0xB0, 0xB0, 0xFF);
                //
                //        Uint32 teamColor[4];
                //
                //        for (int i = 0; i < 4; i++)
                //        {
                //            teamColor[i] = m_Textures[team][entity.second->pSprite].mapRGBA(teamColors[team][i].r, teamColors[team][i].g, teamColors[team][i].b, teamColors[team][i].a);
                //        }
                //
                //        //Color key pixels
                //        for (int i = 0; i < pixelCount; ++i)
                //        {
                //            for (int j = 0; j < 4; j++)
                //            {
                //                if (pixels[i] == colorKey[j])
                //                {
                //                    pixels[i] = teamColor[j];
                //                }
                //            }    
                //        }
                //
                //        //Create texture from manually color keyed pixels
                //        m_Textures[team][entity.second->pSprite].loadFromPixels();
                //
                //    }
                //    
                //    if (entity.second->sClass == "PROJECTILE")
                //    {
                //        if (entity.second->fMovementAngle < 0)
                //            m_Textures[team][entity.second->pSprite].render(entityScreenLocationX, entityScreenLocationY, realWidth, realHeight, NULL, -entity.second->fMovementAngle, NULL, SDL_FLIP_NONE);
                //        else
                //            m_Textures[team][entity.second->pSprite].render(entityScreenLocationX, entityScreenLocationY, realWidth, realHeight, NULL, -entity.second->fMovementAngle, NULL, SDL_FLIP_NONE);
                //       
                //    }
                //       
                //    else
                //    {
                //        if (entity.second->fMovementAngle > 90 || entity.second->fMovementAngle < -90)
                //            m_Textures[team][entity.second->pSprite].render(entityScreenLocationX, entityScreenLocationY, realWidth, realHeight, NULL, NULL, NULL, SDL_FLIP_HORIZONTAL);
                //        else
                //            m_Textures[team][entity.second->pSprite].render(entityScreenLocationX, entityScreenLocationY, realWidth, realHeight, NULL, NULL, NULL, SDL_FLIP_NONE);
                //    }
                //    
                //    
                //    
                //}
            }
            
            if (bShowHealthBars)
            {
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

                    }

                }
            }

            if (currentPlayer->selectedBuilding() != NULL)
            {
                if (currentPlayer->selectedBuilding()->sName == "Barracks")
                {
                    if (currentPlayer->selectedBuilding()->abilityCooldown[0] != 0)
                    {
                        Menus["Barracks"]->Buttons["8 Train Tremendinius"]->setText(to_string(currentPlayer->selectedBuilding()->abilityCooldown[0] / 30));
                    }
                    else
                    {
                        Menus["Barracks"]->Buttons["8 Train Tremendinius"]->setText("Tremendinius");
                    }
                    if (currentPlayer->selectedBuilding()->abilityCooldown[1] != 0)
                    {
                        Menus["Barracks"]->Buttons["9 Train Katyusha"]->setText(to_string(currentPlayer->selectedBuilding()->abilityCooldown[1] / 30));
                    }
                    else
                    {
                        Menus["Barracks"]->Buttons["9 Train Katyusha"]->setText("Katyusha");
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

                    unit.second->selectionBox->enable(true);
                    unit.second->selectionBox->setPosition((float)entityScreenLocationX / (float)m_nScreenWidth, (float)entityScreenLocationY / (float)m_nScreenHeight);
                    unit.second->selectionBox->setSize((float)(unit.second->fWidth * nTileSize) / (float)m_nScreenWidth, (float)(unit.second->fHeight * nTileSize) / (float)m_nScreenHeight);
                    unit.second->selectionBox->setText("Test");
                }
                else
                {
                    unit.second->selectionBox->enable(false);
                }
            }
            
            if (selectedUnit != NULL)
            {
                if ((selectedUnit->mPosition.x > fScreenLeftBorder - selectedUnit->fWidth && selectedUnit->mPosition.x - selectedUnit->fWidth < fScreenRightBorder) && (selectedUnit->mPosition.y > fScreenTopBorder - selectedUnit->fHeight && selectedUnit->mPosition.y - selectedUnit->fHeight < fScreenBottomBorder))
                {
                    objectsToRender++;
                    int entityScreenLocationX = (int)((float)(selectedUnit->mPosition.x - currentPlayer->getCameraX() - (float)(selectedUnit->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                    int entityScreenLocationY = (int)((float)(selectedUnit->mPosition.y - currentPlayer->getCameraY() - (float)(selectedUnit->fHeight / 3.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);

                    SDL_Rect Selection = { entityScreenLocationX - (selectedUnit->fWidth * nTileSize) / 4, entityScreenLocationY - (selectedUnit->fHeight * nTileSize) / 4, (selectedUnit->fWidth * nTileSize) * 1.5f, (selectedUnit->fHeight * nTileSize) * 1.5f };
                    SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
                    SDL_RenderDrawRect(m_Renderer, &Selection);
                }
            }

            for (auto& building : buildings)
            {
                int entityScreenLocationX = (int)((float)(building.second->mPosition.x - currentPlayer->getCameraX() - (float)(building.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                int entityScreenLocationY = (int)((float)(building.second->mPosition.y - currentPlayer->getCameraY() - (float)(building.second->fHeight / 3.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);

                if ((building.second->mPosition.x > fScreenLeftBorder - building.second->fWidth && building.second->mPosition.x - building.second->fWidth < fScreenRightBorder) && (building.second->mPosition.y > fScreenTopBorder - building.second->fHeight && building.second->mPosition.y - building.second->fHeight < fScreenBottomBorder))
                {
                    if (building.second->bSelected == true && building.second->getTeam() == currentPlayer->getTeam())
                    {
                        SDL_Rect Selection = { entityScreenLocationX - (building.second->fWidth * nTileSize) / 4, entityScreenLocationY - (building.second->fHeight * nTileSize) / 4, (building.second->fWidth * nTileSize) * 1.5f, (building.second->fHeight * nTileSize) * 1.5f };
                        SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
                        SDL_RenderDrawRect(m_Renderer, &Selection);
                    }
                    building.second->selectionBox->enable(true);
                    building.second->selectionBox->setPosition((float)entityScreenLocationX / (float)m_nScreenWidth, (float)entityScreenLocationY / (float)m_nScreenHeight);
                    building.second->selectionBox->setSize((float)(building.second->fWidth * nTileSize) / (float)m_nScreenWidth, (float)(building.second->fHeight * nTileSize) / (float)m_nScreenHeight);
                    building.second->selectionBox->setText("Test");
                }
                else building.second->selectionBox->enable(false);

                

                if (building.second->Counter != NULL)
                {
                    building.second->Counter->setPosition((float)entityScreenLocationX / (float)m_nScreenWidth, ((float)entityScreenLocationY - nTileSize * 1.5f) / (float)m_nScreenHeight);
                    building.second->Counter->setSize((float)(building.second->fWidth * nTileSize) / (float)m_nScreenWidth, (float)(building.second->fHeight * nTileSize) / (float)m_nScreenHeight / 2);
                    building.second->Counter->setFontSize(nTileSize / 2);
                    building.second->Counter->setText(to_string(45 - (tickCounter / 30) % 45));
                }
            }
            
            if (mLanguage == "English")
                TextBoxes["Gold"]->setText("Gold: " + to_string(currentPlayer->getGold()));
            else if (mLanguage == "Spanish")
                TextBoxes["Gold"]->setText("Oro: " + to_string(currentPlayer->getGold()));

            if (bDebugMode)
            {
                Lists["Data"]->TextBoxes["Tile Size"]->setText("Tile Size: " + to_string(nTileSize));
                Lists["Data"]->TextBoxes["FPS"]->setText("FPS: " + to_string(avgFPS));
                Lists["Data"]->TextBoxes["Entities"]->setText("Entities: " + to_string(objectsToRender));
                Lists["Data"]->TextBoxes["TpS"]->setText("Ticks per second: " + to_string(nTicksPerSecond));

                SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);

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
                    }
                }

            }

            if (selectedUnit != NULL)
            {
                unitHUD->enable(true);
                unitHUD->stats->TextBoxes["1 Name"]->setText(selectedUnit->sName);
                unitHUD->stats->TextBoxes["2 Health"]->setText("Health: " + to_string(selectedUnit->nHealth) + "/" + to_string(selectedUnit->nMaxHealth));
                unitHUD->stats->TextBoxes["3 Armour"]->setText("Armour: " + to_string(selectedUnit->nArmour));
                unitHUD->stats->TextBoxes["4 Damage"]->setText("Damage: " + to_string(selectedUnit->nAttack));
                unitHUD->stats->TextBoxes["5 Range"]->setText("Range: " + to_string(selectedUnit->fAttackRange));
                unitHUD->stats->TextBoxes["6 AoE"]->setText("AoE: " + to_string(selectedUnit->fSplashArea));
            }
            else if (currentPlayer->selectedBuilding() != NULL)
            {
                unitHUD->enable(true);
                unitHUD->stats->TextBoxes["1 Name"]->setText(currentPlayer->selectedBuilding()->sName);
                unitHUD->stats->TextBoxes["2 Health"]->setText("Health: " + to_string(currentPlayer->selectedBuilding()->nHealth) + "/" + to_string(currentPlayer->selectedBuilding()->nMaxHealth));
                unitHUD->stats->TextBoxes["3 Armour"]->setText("Armour: " + to_string(currentPlayer->selectedBuilding()->nArmour));
                unitHUD->stats->TextBoxes["4 Damage"]->setText("Damage: " + to_string(currentPlayer->selectedBuilding()->nAttack));
                unitHUD->stats->TextBoxes["5 Range"]->setText("Range: " + to_string(currentPlayer->selectedBuilding()->fAttackRange));
                unitHUD->stats->TextBoxes["6 AoE"]->setText("AoE: " + to_string(currentPlayer->selectedBuilding()->fSplashArea));
            }
            else unitHUD->enable(false);

            if (bDebugMatch)
            {
                if (cursorMode == place && unitPlaced.type != "NONE")
                {
                    Unit* unit = new Unit(unitPrototypes[unitPlaced.type]);

                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    renderEntity(unit, x, y, true);
                }
            }
            
            GUIRender();
            
            SDL_SetRenderDrawColor(m_Renderer, 0x35, 0xa7, 0x42, 0xFF);
        
            //Update screen
            SDL_RenderPresent(m_Renderer);      
            
            //string windowTitle = "Caelis Chaos 0.3.0";
            //windowTitle += " - Tile size: " + to_string(nTileSize);
            //windowTitle += " - FPS: " + to_string(avgFPS);
            //windowTitle += " - Next wave: " + to_string(30 - (tickCounter / 30) % 30);
            //windowTitle += " - Objects: " + to_string(objectsToRender);
            //windowTitle += " - Ticks per second: " + to_string(nTicksPerSecond);
            //SDL_SetWindowTitle(m_Window, windowTitle.c_str());
        }

    }

    void renderEntity(Entity* entity, int x, int y, bool ghost)
    {
        int realWidth = entity->fWidth * nTileSize;
        int realHeight = entity->fHeight * nTileSize;

        int team = entity->getTeam();

        string spritePath = entity->pSprite;

        spritePath += ghost ? ".ghost" : "";

        auto it = m_Textures[team].find(spritePath);

        if (spritePath != "" && (it == m_Textures[team].end() || it->second.mTexture == NULL))
        {
            m_Textures[team].insert({ spritePath, LTexture(m_Renderer, m_Window) });

            m_Textures[team][spritePath].loadPixelsFromFile(entity->pSprite.c_str());

            //Get pixel data
            Uint32* pixels = m_Textures[team][spritePath].getPixels32();
            int pixelCount = m_Textures[team][spritePath].getPitch32() * m_Textures[team][spritePath].getHeight();

            //Map colors
            Uint32 colorKey[4];
            colorKey[0] = m_Textures[team][spritePath].mapRGBA(0xFA, 0xFA, 0xFA, 0xFF);
            colorKey[1] = m_Textures[team][spritePath].mapRGBA(0xE3, 0xE3, 0xE3, 0xFF);
            colorKey[2] = m_Textures[team][spritePath].mapRGBA(0xC9, 0xC9, 0xC9, 0xFF);
            colorKey[3] = m_Textures[team][spritePath].mapRGBA(0xB0, 0xB0, 0xB0, 0xFF);

            Uint32 teamColor[4];

            for (int i = 0; i < 4; i++)
            {
                teamColor[i] = m_Textures[team][spritePath].mapRGBA(teamColors[team][i].r, teamColors[team][i].g, teamColors[team][i].b, teamColors[team][i].a);
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
            m_Textures[team][spritePath].loadFromPixels();

            if (ghost)
            {
                m_Textures[team][spritePath].setAlpha(100);
            }
        }

        if (entity->sClass == "PROJECTILE")
        {
            if (entity->fMovementAngle < 0)
                m_Textures[team][spritePath].render(x, y, realWidth, realHeight, NULL, -entity->fMovementAngle, NULL, SDL_FLIP_NONE);
            else
                m_Textures[team][spritePath].render(x, y, realWidth, realHeight, NULL, -entity->fMovementAngle, NULL, SDL_FLIP_NONE);

        }

        else
        {
            if (entity->fMovementAngle > 90 || entity->fMovementAngle < -90)
                m_Textures[team][spritePath].render(x, y, realWidth, realHeight, NULL, NULL, NULL, SDL_FLIP_HORIZONTAL);
            else
                m_Textures[team][spritePath].render(x, y, realWidth, realHeight, NULL, NULL, NULL, SDL_FLIP_NONE);
        }

    }


private:

    void loadUpgrades()
    {
        std::fstream Upgrades;
        Upgrades.open("res/upgrades/default.ccu", std::fstream::in | std::fstream::out | std::fstream::app);

        std::string TextBuffer;
        bool uPrototype = false;
        string name = "";

        while (getline(Upgrades, TextBuffer)) {
            if (TextBuffer == "UPGRADE_PROTOTYPE:")
                uPrototype = true;

            if (uPrototype)
            {
                if (TextBuffer.substr(0, 5) == "Name:")
                {
                    name = TextBuffer.substr(6);
                    upgradePrototypes[name].sName = name;
                }
                if (name != "")
                {
                    if (TextBuffer.substr(0, 5) == "Race:")
                    {
                        upgradePrototypes[name].sRace = TextBuffer.substr(6);
                    }
                    if (TextBuffer.substr(0, 6) == "Class:")
                    {
                        upgradePrototypes[name].sClass = TextBuffer.substr(7);
                    }
                    if (TextBuffer.substr(0, 5) == "Type:")
                    {
                        upgradePrototypes[name].sType = TextBuffer.substr(6);
                    }
                    if (TextBuffer.substr(0, 5) == "Cost:")
                    {
                        upgradePrototypes[name].nPrice = stoi(TextBuffer.substr(6));
                    }
                    if (TextBuffer.substr(0, 8) == "Affects:")
                    {
                        upgradePrototypes[name].EntitiesAffected.insert(TextBuffer.substr(9));
                    }
                    if (TextBuffer.substr(0, 8) == "Effects:")
                    {
                        while (TextBuffer != "END_PROTOTYPE")
                        {
                            if (TextBuffer.substr(0, 10) == "addHealth:")
                            {
                                int health = stoi(TextBuffer.substr(11));

                                upgradePrototypes[name].addEffect([health](Entity* entity, Player* player) {entity->addMaxHealth(health); });
                                upgradePrototypes[name].addEffect([health](Entity* entity, Player* player) {entity->addHealth(health); });
                            }

                            if (TextBuffer.substr(0, 10) == "addAttack:")
                            {
                                int attack = stoi(TextBuffer.substr(11));

                                upgradePrototypes[name].addEffect([attack](Entity* entity, Player* player) {entity->nAttack += attack; });
                            }

                            if (TextBuffer.substr(0, 10) == "addArmour:")
                            {
                                int armour = stoi(TextBuffer.substr(11));

                                upgradePrototypes[name].addEffect([armour](Entity* entity, Player* player) {entity->nArmour += armour; });
                            }

                            if (TextBuffer.substr(0, 17) == "addPassiveIncome:")
                            {
                                int passiveIncome = stoi(TextBuffer.substr(18));

                                upgradePrototypes[name].addEffect([passiveIncome](Player* player) { player->nPassiveGold += passiveIncome; } );
                            }

                            if (TextBuffer.substr(0, 20) == "Unlock: Tremendinius")
                            {
                                upgradePrototypes[name].addEffect([](Player* player) { player->unlockTremendinius(); });
                            }

                            if (TextBuffer.substr(0, 16) == "Unlock: Katyusha")
                            {
                                upgradePrototypes[name].addEffect([](Player* player) { player->unlockKatyusha(); });
                            }

                            if (TextBuffer.substr(0, 18) == "UpgradeToBuilding:")
                            {
                                string nextBuilding = TextBuffer.substr(19);

                                Building nextBuildingPrototype = buildingPrototypes[nextBuilding];

                                upgradePrototypes[name].addEffect([nextBuilding](Entity* entity, Player* player) {entity->sName = player->buildingPrototypes[nextBuilding].sName; });
                                upgradePrototypes[name].addEffect([nextBuilding](Entity* entity, Player* player) {entity->nHealth += player->buildingPrototypes[nextBuilding].nMaxHealth - entity->nMaxHealth; });
                                upgradePrototypes[name].addEffect([nextBuilding](Entity* entity, Player* player) {entity->nMaxHealth = player->buildingPrototypes[nextBuilding].nMaxHealth; });
                                upgradePrototypes[name].addEffect([nextBuilding](Entity* entity, Player* player) {entity->fHeight = player->buildingPrototypes[nextBuilding].fHeight; });
                                upgradePrototypes[name].addEffect([nextBuilding](Entity* entity, Player* player) {entity->fWidth = player->buildingPrototypes[nextBuilding].fWidth; });
                                upgradePrototypes[name].addEffect([nextBuilding](Entity* entity, Player* player) {entity->pSprite = player->buildingPrototypes[nextBuilding].pSprite; });
                                upgradePrototypes[name].addEffect([nextBuilding](Entity* entity, Player* player) {Building* buildingPointer = (Building*) entity; buildingPointer->sUpgradesTo = player->buildingPrototypes[nextBuilding].sUpgradesTo; });
                                upgradePrototypes[name].addEffect([nextBuilding](Entity* entity, Player* player) {if (!player->buildingPrototypes[nextBuilding].upgrades.empty()) { Building* buildingPointer = (Building*)entity; buildingPointer->upgrades = player->buildingPrototypes[nextBuilding].upgrades; }});
                            }

                            getline(Upgrades, TextBuffer);

                        }
                    }
                    
                    
                    if (TextBuffer == "END_PROTOTYPE")
                    {
                        if (upgradePrototypes[name].sClass == "Building")
                        {
                            for (auto building : upgradePrototypes[name].EntitiesAffected)
                            {
                                buildingPrototypes[building].upgrades[name] = upgradePrototypes[name];
                            }
                        }
                        uPrototype = false;
                    }
                }


            }

            
        }
    }

    void loadEntities()
    {
        std::fstream Entities;
        Entities.open("res/entities/default.cce", std::fstream::in | std::fstream::out | std::fstream::app);

        std::string TextBuffer;
        bool bPrototype = false;
        bool uPrototype = false;
        string name = "";

        while (getline(Entities, TextBuffer)) {
            if (TextBuffer == "BUILDING_PROTOTYPE:")
                bPrototype = true;

            if (bPrototype)
            {
                if (TextBuffer.substr(0, 3) == "ID:")
                {
                    name = TextBuffer.substr(4);
                    buildingPrototypes[name].sSubClass = name;
                }
                if (name != "")
                {
                    if (TextBuffer.substr(0, 5) == "Name:")
                    {
                        buildingPrototypes[name].sName = TextBuffer.substr(6);
                    }

                    if (TextBuffer.substr(0, 5) == "Race:")
                    {
                        buildingPrototypes[name].sRace = TextBuffer.substr(6);
                    }
                    if (TextBuffer.substr(0, 7) == "Health:")
                    {
                        buildingPrototypes[name].nMaxHealth = stoi(TextBuffer.substr(8));
                        buildingPrototypes[name].nHealth = stoi(TextBuffer.substr(8));
                    }
                    if (TextBuffer.substr(0, 7) == "Sprite:")
                    {
                        buildingPrototypes[name].setSprite((TextBuffer.substr(8)));
                    }
                    if (TextBuffer.substr(0, 7) == "Height:")
                    {
                        buildingPrototypes[name].fHeight = stof(TextBuffer.substr(8));
                    }
                    if (TextBuffer.substr(0, 6) == "Width:")
                    {
                        buildingPrototypes[name].fWidth = stof(TextBuffer.substr(7));
                    }
                    if (TextBuffer.substr(0, 7) == "Reward:")
                    {
                        buildingPrototypes[name].nKillReward = stoi(TextBuffer.substr(8));
                    }
                    if (TextBuffer.substr(0, 7) == "Attack:")
                    {
                        buildingPrototypes[name].nAttack = stoi(TextBuffer.substr(8));
                    }
                    if (TextBuffer.substr(0, 12) == "AttackSpeed:")
                    {
                        buildingPrototypes[name].nAttackSpeed = stoi(TextBuffer.substr(13));
                    }
                    if (TextBuffer.substr(0, 15) == "AttackCooldown:")
                    {
                        buildingPrototypes[name].nDefaultAttackCooldown = stoi(TextBuffer.substr(16));
                    }
                    if (TextBuffer.substr(0, 12) == "AttackRange:")
                    {
                        buildingPrototypes[name].fAttackRange = stof(TextBuffer.substr(13));
                    }
                    if (TextBuffer.substr(0, 12) == "VisionRange:")
                    {
                        buildingPrototypes[name].fVisionRange = stof(TextBuffer.substr(13));
                    }
                    if (TextBuffer.substr(0, 12) == "sProjectile:")
                    {
                        buildingPrototypes[name].sProjectile = TextBuffer.substr(13);
                    }
                    if (TextBuffer.substr(0, 11) == "UpgradesTo:")
                    {
                        buildingPrototypes[name].sUpgradesTo = TextBuffer.substr(12);
                    }
                    if (TextBuffer == "END_PROTOTYPE")
                    {
                        bPrototype = false;
                    }
                }
                
                
            }

            if (TextBuffer == "UNIT_PROTOTYPE:")
                uPrototype = true;

            if (uPrototype)
            {
                if (TextBuffer.substr(0, 3) == "ID:")
                {
                    name = TextBuffer.substr(4);
                    unitPrototypes[name].sSubClass = name;
                }
                if (name != "")
                {
                    if (TextBuffer.substr(0, 5) == "Name:")
                    {
                        unitPrototypes[name].sName = TextBuffer.substr(6);
                    }
                    if (TextBuffer.substr(0, 5) == "Race:")
                    {
                        unitPrototypes[name].sRace = TextBuffer.substr(6);
                    }
                    if (TextBuffer.substr(0, 7) == "Health:")
                    {
                        unitPrototypes[name].nMaxHealth = stoi(TextBuffer.substr(8));
                        unitPrototypes[name].nHealth = stoi(TextBuffer.substr(8));
                    }

                    if (TextBuffer.substr(0, 7) == "Sprite:")
                    {
                        unitPrototypes[name].setSprite((TextBuffer.substr(8)));
                    }
                    if (TextBuffer.substr(0, 7) == "Height:")
                    {
                        unitPrototypes[name].fHeight = stof(TextBuffer.substr(8));
                    }
                    if (TextBuffer.substr(0, 6) == "Width:")
                    {
                        unitPrototypes[name].fWidth = stof(TextBuffer.substr(7));
                    }
                    if (TextBuffer.substr(0, 7) == "Reward:")
                    {
                        unitPrototypes[name].nKillReward = stoi(TextBuffer.substr(8));
                    }
                    if (TextBuffer.substr(0, 14) == "MovementSpeed:")
                    {
                        unitPrototypes[name].fMovementSpeed = stof(TextBuffer.substr(15));
                    }
                    if (TextBuffer.substr(0, 7) == "Attack:")
                    {
                        unitPrototypes[name].nAttack = stoi(TextBuffer.substr(8));
                    }
                    if (TextBuffer.substr(0, 12) == "AttackSpeed:")
                    {
                        unitPrototypes[name].nAttackSpeed = stoi(TextBuffer.substr(13));
                    }
                    if (TextBuffer.substr(0, 15) == "AttackCooldown:")
                    {
                        unitPrototypes[name].nDefaultAttackCooldown = stoi(TextBuffer.substr(16));
                    }
                    if (TextBuffer.substr(0, 12) == "AttackRange:")
                    {
                        unitPrototypes[name].fAttackRange = stof(TextBuffer.substr(13));
                    }
                    if (TextBuffer.substr(0, 12) == "VisionRange:")
                    {
                        unitPrototypes[name].fVisionRange = stof(TextBuffer.substr(13));
                    }
                    if (TextBuffer.substr(0, 12) == "sProjectile:")
                    {
                        unitPrototypes[name].sProjectile = TextBuffer.substr(13);
                    }
                    if (TextBuffer.substr(0, 7) == "Armour:")
                    {
                        unitPrototypes[name].nArmour = stoi(TextBuffer.substr(8));
                    }
                    if (TextBuffer.substr(0, 5) == "Cost:")
                    {
                        unitPrototypes[name].nTrainingCost = stoi(TextBuffer.substr(6));
                    }
                    if (TextBuffer.substr(0, 11) == "SplashArea:")
                    {
                        unitPrototypes[name].fSplashArea = stof(TextBuffer.substr(12));
                    }
                    if (TextBuffer == "END_PROTOTYPE")
                    {
                        uPrototype = false;
                    }
                }


            }
        }
    }

    // Generate Base Map

    void loadMap()
    {
        std::fstream Map;
        Map.open("res/maps/default.ccm", std::fstream::in | std::fstream::out | std::fstream::app);

        std::string TextBuffer;

        while (getline(Map, TextBuffer)) {
            
            if (TextBuffer.substr(0, 8) == "Players:")
            {
                int playerAmount = stoi(TextBuffer.substr(9));

                for (int i = 0; i < playerAmount; i++)
                    players.push_back(new Player);
            }


            Entity* entity = new Entity;
            int entityID;
            bool isEntity = false;
            if (buildingPrototypes.find(TextBuffer) != buildingPrototypes.end())
            {
                entity = new Building (buildingPrototypes[TextBuffer]);
                entityID = createEntity(entity);
                buildings[entityID] = (Building*) entity;
                isEntity = true;
            }
            
            if (isEntity)
            {
                getline(Map, TextBuffer);
                Vector2D coords = readCoordinates(TextBuffer);
                entityList[entityID]->setCoords(coords);
                getline(Map, TextBuffer);
                int team = stof(TextBuffer);
                entityList[entityID]->setTeam(team);
            }

            Trigger* trigger = new Trigger;
            if (TextBuffer == "Trigger")
            {
                getline(Map, TextBuffer);
                if (TextBuffer == "Movement")
                {
                    trigger = new MovementTrigger;
                    getline(Map, TextBuffer);
                    Vector2D upperCorner = readCoordinates(TextBuffer);
                    getline(Map, TextBuffer);
                    Vector2D lowerCorner = readCoordinates(TextBuffer);
                    getline(Map, TextBuffer);
                    Vector2D Target = readCoordinates(TextBuffer);
                    trigger->setCoords(upperCorner, lowerCorner);
                    trigger->setNewTarget(Target);

                    set<int> validTeams;

                    getline(Map, TextBuffer);

                    string number = "";

                    int i = 0;

                    while (i < TextBuffer.size())
                    {
                        if (TextBuffer[i] != '{' && TextBuffer[i] != ',' && TextBuffer[i] != '}' && TextBuffer[i] != ' ')
                        {
                            number += TextBuffer[i];
                        }
                        else if (TextBuffer[i] == ',' || TextBuffer[i] == '}')
                        {
                            validTeams.insert(stoi(number));
                            number = "";
                        }
                        i++;
                    }
                    trigger->setValidTeams(validTeams);

                    getline(Map, TextBuffer);

                    while (TextBuffer != "endTrigger")
                    {
                        if (TextBuffer.substr(0, 9) == "Defeated:")
                        {
                            int player = stoi(TextBuffer.substr(10));
                            trigger->conditions.push_back(&players[player]->defeated);
                        }
                        
                        if (TextBuffer.substr(0, 6) == "Alive:")
                        {
                            int player = stoi(TextBuffer.substr(7));
                            trigger->conditions.push_back(&players[player]->alive);
                        }

                        getline(Map, TextBuffer);
                    }

                    Triggers.push_back(trigger);
                }
            }
            
        }

        Map.close();
    }

    Vector2D readCoordinates(string line)
    {
        float x = 0;
        float y = 0;

        string number = "";

        int i = 0;

        while (i < line.size())
        {
            if (line[i] != '(' && line[i] != ',' && line[i] != ')' && line[i] != ' ')
            {
                number += line[i];
            }
            else if (line[i] == ',')
            {
                x = stof(number);
                number = "";
            }
            else if (line[i] == ')')
            {
                y = stof(number);
            }
            i++;
        }

        return { x, y };
    }

    void createPlayers()
    {
        players[0]->setTeam(0);
        players[1]->setTeam(1);
        players[2]->setTeam(2);
        players[3]->setTeam(3);

        if (bMultiplayer) currentPlayer = players[CLIENT_ID - 1];
        else currentPlayer = players[0];

        for (int i = 0; i < (int)players.size(); i++)
        {
            for (auto& building : buildings)
                if (building.second->getTeam() == players[i]->getTeam())
                {
                    players[i]->teamBuildings.push_back(building.second);
                    building.second->Owner = players[i];
                }
            if (!bMultiplayer && players[i] != currentPlayer) players[i]->switchAI();
            if (bDebugMatch) players[i]->addGold(1000000);

            if (!players[i]->teamBuildings.empty()) players[i]->setCamera(players[i]->teamBuildings[0]->mPosition);

            players[i]->sRace = "Human";

            for (auto uPrototype : unitPrototypes)
                if (uPrototype.second.sRace == players[i]->sRace) players[i]->unitPrototypes[uPrototype.first] = uPrototype.second;

            for (auto bPrototype : buildingPrototypes)
                if (bPrototype.second.sRace == players[i]->sRace) players[i]->buildingPrototypes[bPrototype.first] = bPrototype.second;

            for (auto upPrototype : upgradePrototypes)
                if (upPrototype.second.sRace == players[i]->sRace && upPrototype.second.sClass == "Player") players[i]->upgrades[upPrototype.second.sType].push_back(upPrototype.second);
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

        if (entity->sClass == "UNIT")
        {
            entity->selectionBox = new Button(m_Renderer, m_Window, m_Font);
            entity->selectionBox->setLayer(2);
            entity->selectionBox->setVisibility(false);
            Buttons[to_string(i)] = entity->selectionBox;
        }

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
            if (units[ID] == selectedUnit) selectedUnit = NULL;
            Buttons[to_string(ID)]->free();
            Buttons.erase(to_string(ID));
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
            arrow->fSplashArea = entity->fSplashArea;
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
            fireball->fSplashArea = entity->fSplashArea;
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
            cannonball->fSplashArea = entity->fSplashArea;
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
            bulletMG->fSplashArea = entity->fSplashArea;
            bulletMG->nTargetID = target;
            ID = createEntity(bulletMG);
            projectiles[ID] = bulletMG;
        }
        
        
    }

    void gameAction(int player, int id, int argument = 0, string argument2 = "")
    {
        if (!pause)
        {
            switch (id)
            {
            //Train unit
            case 1:
            {
                if (players[player]->selectedBuilding() != NULL)
                    if (players[player]->spawnUnitCooldown <= 0 && players[player]->selectedBuilding()->sName != "Tower")
                    {
                        string type;
                        switch (argument)
                        {
                            case melee:
                                type = "Melee";
                                break;
                            case range:
                                type = "Range";
                                break;
                            case mage:
                                type = "Mage";
                                break;
                            case mounted:
                                type = "Mounted";
                                break;
                            case heavy:
                                type = "Heavy";
                                break;
                            case siege:
                                type = "Siege";
                                break;
                            case hero1:
                                type = "Hero1";
                                break;
                            case hero2:
                                type = "Hero2";
                                break;
                        }
                        spawnUnit(type, player);
                    }
                        
            
                        
                break;

            }
            //Player Upgrade
            case 2:
            {
                string type = "";
                switch (argument)
                {
                    case health:
                        type = "Health";
                        break;
                    case attack1:
                        type = "Attack1";
                        break;
                    case attack2:
                        type = "Attack2";
                        break;
                    case passiveGold:
                        type = "PassiveGold";
                        break;
                }
                players[player]->researchUpgrade(type);
                break;

            }
            //Building Upgrade
            case 3:
            {
                players[player]->teamBuildings[argument]->researchUpgrade(players[player]->teamBuildings[argument]->sUpgradesTo);
                break;
            }
                
            case 4:
                pause = !pause;
                break;
            case 5:

                if (players[player]->selectedBuildingID < players[player]->teamBuildings.size() && players[player]->selectedBuilding() != NULL)
                {
                    players[player]->selectedBuilding()->select();
                    if (players[player] == currentPlayer)
                    {
                        if (players[player]->selectedBuilding()->sName == "Barracks" || players[player]->selectedBuilding()->sName == "Fortress") 
                            Menus[players[player]->selectedBuilding()->sName]->enable(false);
                    }
                        
                }

                if (argument != -1)
                    for (int i = 0; i < players[player]->teamBuildings.size(); i++)
                    {
                        if (players[player]->teamBuildings[i]->getID() == argument)
                        {
                            players[player]->selectedBuildingID = i;
                            players[player]->selectedBuilding()->select();

                            if (players[player] == currentPlayer)
                            {
                                if (selectedUnit != NULL) selectedUnit = NULL;
                            }

                            break;
                        }
                    }
                else players[player]->selectedBuildingID = -1;

                break;
            case 6:
                if (players[player]->selectedBuilding() != NULL)
                {
                    if (players[player]->selectedBuildingID < players[player]->teamBuildings.size())
                        players[player]->selectedBuilding()->upgrade(players[player]);
                }
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:          
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            }
        }
        else
        {
            if (id == 4) pause = false;
        }

    }

    void spawnUnit(string unitType, int player) {
        vector<Unit*> wave;

        wave.push_back(new Unit(players[player]->unitPrototypes[unitType]));

        if (players[player]->getGold() < wave[0]->nTrainingCost) {
            wave.clear();
            return;
        }
        else if ((unitType == "Hero2" && (players[player]->tremendiniusAlive || players[player]->selectedBuilding()->abilityCooldown[0] > 0 || players[player]->lockTremendinius)) || (unitType == "Hero1" && (players[player]->KatyushaAlive || players[player]->selectedBuilding()->abilityCooldown[1] > 0 || players[player]->lockKatyusha)))
        {
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

            if (unitType == "Hero2")
            {
                players[player]->selectedBuilding()->abilityCooldown[0] = 7200;
                players[player]->tremendiniusAlive = true;
            }
                

            if (unitType == "Hero1")
            {
                players[player]->selectedBuilding()->abilityCooldown[1] = 7200;
                players[player]->KatyushaAlive = true;
            }
                

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