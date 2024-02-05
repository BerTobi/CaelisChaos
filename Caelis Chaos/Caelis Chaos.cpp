/*
Caelis Chaos

Version 0.3.0 Dev build

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

class Bullet : public Projectile
{
public:
    Bullet()
    {
        fSpeed = 0.3;
        fX = 0;
        fY = 0;
        sName = "Bullet";

        pSprite = "res/textures/Bullet.png";
        fWidth = 0.1f;
        fHeight = 0.1f;

    }
};

class Fireball : public Projectile
{
public:
    Fireball()
    {
        fSpeed = 0.2;
        fX = 0;
        fY = 0;
        sName = "Fireball";

        Sprite fireballSprite;

        pSprite = "res/textures/Fireball.png";
        fWidth = 0.2f;
        fHeight = 0.2f;
    }
};

class Cannonball : public Projectile
{
public:
    Cannonball()
    {
        fSpeed = 0.4;
        fX = 0;
        fY = 0;
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
        fSpeed = 0.5;
        fX = 0;
        fY = 0;
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
        fSpeed = 0.0375;
        fX = 0;
        fY = 0;
        nAttack = 15;
        nAttackSpeed = 1000;
        nDefaultAttackCooldown = 20000;
        fAttackRange = 0.2;
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
        fSpeed = 0.0375;
        fX = 0;
        fY = 0;
        nAttack = 50;
        nAttackSpeed = 2000;
        nDefaultAttackCooldown = 20000;
        fAttackRange = 0.2;
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
        fSpeed = 0.03;
        fX = 0;
        fY = 0;
        nAttack = 50;
        nAttackSpeed = 500;
        nDefaultAttackCooldown = 20000;
        fAttackRange = 3.5;
        fAttackDistance = 5;
        sName = "Mage";
        sProjectile = "Fireball";
        nArmour = 0;

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
        fSpeed = 0.03375;
        fX = 0;
        fY = 0;
        nAttack = 10;
        nAttackSpeed = 1000;
        nDefaultAttackCooldown = 20000;
        fAttackRange = 2.5;
        fAttackDistance = 5;
        sName = "Archer";
        sProjectile = "Bullet";
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
        fSpeed = 0.025;
        fX = 0;
        fY = 0;
        nAttack = 1300;
        nAttackSpeed = 500;
        nDefaultAttackCooldown = 20000;
        fAttackRange = 0.6;
        fAttackDistance = 4;
        sName = "Tremendinius";
        nArmour = 50;

        nKillReward = 500;
        nTrainingCost = 4000;

        pSprite = "res/textures/Tremendinius.png";
        fWidth = 2;
        fHeight = 2;
    }
};

class BigBird : public Unit
{
public:
    BigBird()
    {
        nHealth = 700;
        nMaxHealth = 700;
        fSpeed = 0.04;
        fX = 0;
        fY = 0;
        nAttack = 50;
        nAttackSpeed = 1500;
        nDefaultAttackCooldown = 20000;
        fAttackRange = 0.2;
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
        fSpeed = 0.025;
        fX = 0;
        fY = 0;
        nAttack = 270;
        nAttackSpeed = 333;
        nDefaultAttackCooldown = 20000;
        fAttackRange = 4.5;
        fAttackDistance = 6;
        sName = "Cannon";
        sProjectile = "Cannonball";
        nArmour = 10;


        nKillReward = 150;
        nTrainingCost = 1000;

        pSprite = "res/textures/Cannon.png";
        fWidth = 1;
        fHeight = 1;
    }
};

class Minigun : public Unit
{
public:
    Minigun()
    {
        nHealth = 3000;
        nMaxHealth = 3000;
        fSpeed = 0.02;
        fX = 0;
        fY = 0;
        nAttack = 15;
        nAttackSpeed = 20000;
        nDefaultAttackCooldown = 20000;
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
        fX = 0;
        fY = 0;
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
        fX = 0;
        fY = 0;
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
        fX = 0;
        fY = 0;
        sName = "Tower";
        sProjectile = "Bullet";
        nLevel = 1;
        nKillReward = 250;

        nAttack = 75;
        nAttackSpeed = 1000;
        nDefaultAttackCooldown = 20000;
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
    queue<int> m_actionQueue;
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

        teamColors[0] = { 0, 0, 255, 0 };
        teamColors[1] = { 255, 0, 0, 0 };
        teamColors[2] = { 12, 241, 249, 0 };
        teamColors[3] = { 255, 216, 0, 0 };

        CLIENT_ID = -1;

        pause = false;

    }

private:

    // Likely temporary

    Sprite sprites[2];
    unordered_map<int, Unit*> units;
    unordered_map<int, Building*> buildings;
    unordered_map<int, Projectile*> projectiles;
    vector<Player*> players;

    bool bGameOver = false;
    bool bKey[21];
    bool bHoldKey[21] = { false };
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

    int waveTimer = 0;
    SDL_Color teamColors[4];

    int lastAction = 0;

    bool log = false;

    int turn = 0;
    int nextTurn = 0;
    int ticksSinceLastTurn = 0;
    bool turnSent = false;

    int playerActions[4];
    int randomSeed;
    queue<int> actionQueue;


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

public:

    virtual void UpdateMenu() {
        char option;
        cout << "Singleplayer(s) or Multiplayer(m)?" << endl;
        cin >> option;

        if (option == 's') m_nGameState = inMatch;
        else if (option == 'm')
        {
            bMultiplayer = true;
            cout << "Host(h) or Join(j)?" << endl;
            cin >> option;
            if (option == 'h') {
                bServer = true;
                //initializeServer();
                m_nGameState = matchLobby;
                /*while (true)
                {
                    Server();
                }*/
            }
            else if (option == 'j')
            {
                cout << "IP: ";
                cin >> IP;
                /*initializeClient();
                while (true)
                {
                    Client();
                }*/
                m_nGameState = matchLobby;
            }
        }

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
                sscanf_s(cData, "%d|%d|%d|%d", &data_type, &id, &turnData, &action);
                printf("%i\n", turnData);
                client_map[id + 1]->SetTurn(turnData);
                client_map[id + 1]->m_actionQueue.emplace(action);
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
                m_nGameState = inMatch;
                break;
            case 6:
                break;
            case 7:
                int actions[4];
                int rTurn;
                sscanf_s(cData, "%d|%d|%d|%d|%d|%d", &data_type, &rTurn, &actions[0], &actions[1], &actions[2], &actions[3]);

                for (int i = 0; i < 4; i++)
                    playerActions[i] = actions[i];

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
        new_player_id = 0;

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
                    if (client_map.size() >= i) {
                        if (client_map[i]->m_actionQueue.empty() == false)
                        {
                            content = "|" + to_string(client_map[i]->m_actionQueue.front());
                            client_map[i]->m_actionQueue.pop();
                        }
                        else content = "|0";
                        strcat_s(message_data, content.c_str());
                        client_map[i]->SetAction(0);
                    }
                    else
                    {
                        content = "|0";
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
                    ParseData(server, static_cast<ClientData*>(serverEvent.peer->data)->GetID(), serverEvent.packet->data);
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


                    serverEvent.peer->data = NULL;
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
                    printf("%i\n", turn);
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


                    serverEvent.peer->data = NULL;
                    break;
                }
                }
            }
            
        }
        

        // GAME LOOP END

        //enet_host_destroy(server);
    }

    virtual int initializeClient()
    {
        printf("Please enter your username:\n");
        char username[80];
        cin >> username;
        cin.ignore();

        const char* ip = IP.c_str();

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
                    action_data += to_string(actionQueue.front());
                    actionQueue.pop();
                    strcat_s(turn_data, action_data.c_str());
                    lastAction = -1;
                }
                else
                {
                    string action_data = "|0";
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
                    printf("%s\n", clientEvent.packet->data);
                    ParseDataClient(clientEvent.packet->data);
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

        for (int k = 0; k < 21; k++)
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x26ZXCFTS\x1BPMK123ABQG"[k]))) != 0;
        
        lastAction = -1;

        bool isConsoleWindowFocused = (GetConsoleWindow() == GetForegroundWindow());

        if (isConsoleWindowFocused)
        {
            if (m_nGameState == inMatch)
            {
                //// Arrow keys - Camera movement 
                //if (bKey[0]) if (currentPlayer->getCameraX() <= 26)     currentPlayer->setCamera(currentPlayer->getCameraX() + (0.9f / fScale), currentPlayer->getCameraY());
                //if (bKey[1]) if (currentPlayer->getCameraX() >= -26)      currentPlayer->setCamera(currentPlayer->getCameraX() + (-0.9f / fScale), currentPlayer->getCameraY());
                //if (bKey[2]) if (currentPlayer->getCameraY() <= 26)     currentPlayer->setCamera(currentPlayer->getCameraX(), currentPlayer->getCameraY() + (0.9f / fScale));
                //if (bKey[3]) if (currentPlayer->getCameraY() >= -26)      currentPlayer->setCamera(currentPlayer->getCameraX(), currentPlayer->getCameraY() + (-0.9f / fScale));
                //
                //// "Z"/"X" - Zoom in/out
                //if (bKey[4])
                //{
                //    nTileSize += (!bHoldKey[4] && bKey[4]) ? 1 : 0;
                //    bHoldKey[4] = true;
                //}
                //else
                //    bHoldKey[4] = false;
                //
                //if (bKey[5])
                //{
                //    nTileSize -= (!bHoldKey[5] && bKey[5]) ? 1 : 0;
                //    bHoldKey[5] = true;
                //}
                //else
                //    bHoldKey[5] = false;

                //// "C" - Show/Hide grid
                //if (bKey[6])
                //{
                //    if (!bHoldKey[6]) bShowGrid = !bShowGrid;
                //    bHoldKey[6] = true;
                //}
                //else
                //    bHoldKey[6] = false;

                //// "F" - Train footman
                //keystrokeAction(7, 1);
                //
                //// "T" - Train Tremendiñus 
                //keystrokeAction(8, 9);
                //
                //// "Esc" - Return to start menu
                //if (bKey[10]) m_nGameState = startMenu;
                //
                //// "P" - Pause
                //keystrokeAction(11, 4);
                //
                //// "M" - Train mage
                //keystrokeAction(12, 2);
                //
                //// "K" - Train knight
                //keystrokeAction(13, 3);
                //
                ////"1" Building select
                //keystrokeAction(14, 5);
                //
                ////"2" Building upgrade
                //keystrokeAction(15, 6);
                //
                ////"3" - Passive gold upgrade
                //keystrokeAction(16, 8);
                //
                ////"A" Train Archer
                //keystrokeAction(17, 7);
                //
                ////"B" Train BigBird
                //keystrokeAction(18, 10);
                //
                ////"Q" Train Cannon
                //keystrokeAction(19, 11);
                //
                ////"G" Train Minigun
                //keystrokeAction(20, 12);

            }

            else if (m_nGameState == matchLobby)
            {
                // "S" - Starts match in server lobby 
                if (bKey[9])
                {
                    if (!bHoldKey[9] && m_nGameState == matchLobby)
                    {
                        BroadcastPacket(server, "5|\0");
                        m_nGameState = inMatch;
                        system("CLS");
                    };
                    bHoldKey[9] = true;
                }
                else
                    bHoldKey[9] = false;
            }

        }

        while (SDL_PollEvent(&m_Event) != 0)
        {
            //User requests quit
            if (m_Event.type == SDL_QUIT)
            {
                m_nGameState = startMenu;
            }
            else if (m_Event.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
                switch (m_Event.key.keysym.sym)
                {
                // Arrow keys - Camera movement 
                case SDLK_UP:
                    if (currentPlayer->getCameraY() > -42) currentPlayer->setCamera(currentPlayer->getCameraX(), currentPlayer->getCameraY() + (-1.1f / fScale));
                    break;
                
                case SDLK_DOWN:
                    if (currentPlayer->getCameraY() < 42) currentPlayer->setCamera(currentPlayer->getCameraX(), currentPlayer->getCameraY() + (1.1f / fScale));
                    break;
                
                case SDLK_LEFT:
                    if (currentPlayer->getCameraX() > -42) currentPlayer->setCamera(currentPlayer->getCameraX() + (-1.1f / fScale), currentPlayer->getCameraY());
                    break;
                
                case SDLK_RIGHT:
                    if (currentPlayer->getCameraX() < 42) currentPlayer->setCamera(currentPlayer->getCameraX() + (1.1f / fScale), currentPlayer->getCameraY());
                    break;
                
                // "Z"/"X" - Zoom in/out
                case SDLK_z:
                    if (nTileSize < 2048) nTileSize *= 2;
                    break;
                
                case SDLK_x:
                    if (nTileSize > 16) nTileSize *= 0.5;
                    break;

                // "C" - Show/Hide grid
                case SDLK_c:
                    bShowGrid = !bShowGrid;
                    break;

                // "F" - Train footman
                case SDLK_f:
                    keystrokeAction(1);
                    break;

                // "T" - Train Tremendiñus 
                case SDLK_t:
                    keystrokeAction(9);
                    break;

                // "Esc" - Return to start menu
                case SDLK_ESCAPE:
                    m_nGameState = startMenu;
                    break;

                // "P" - Pause
                case SDLK_p:
                    keystrokeAction(4);
                    break;

                // "M" - Train mage
                case SDLK_m:
                    keystrokeAction(2);
                    break;

                // "K" - Train knight
                case SDLK_k:
                    keystrokeAction(3);
                    break;

                //"1" Building select
                case SDLK_1:
                    keystrokeAction(5);
                    break;

                //"2" Building upgrade
                case SDLK_2:
                    keystrokeAction(6);
                    break;

                //"3" - Passive gold upgrade
                case SDLK_3:
                    keystrokeAction(8);
                    break;

                //"A" Train Archer
                case SDLK_a:
                    keystrokeAction(7);
                    break;

                //"B" Train BigBird
                case SDLK_b:
                    keystrokeAction(10);
                    break;

                //"Q" Train Cannon
                case SDLK_q:
                    keystrokeAction(11);
                    break;

                //"G" Train Minigun
                case SDLK_g:
                    keystrokeAction(12);
                    break;

                default:
                    break;
                }
            }
        }

    }

    void keystrokeAction(int action)
    {

        if (bMultiplayer)
        {
            if (actionQueue.size() < 5)
            {
                actionQueue.emplace(action);
            }
            else
            {
                actionQueue.emplace(action);
                actionQueue.pop();
            }
        }
        else gameAction(currentPlayer->getTeam(), action);
    }

    virtual void Settings()
    {
        setGameTick(30);
    }

    virtual void Create()
    {
        createWindow("Caelis Chaos 0.3.0 Alpha");
        //createConsole(m_sConsoleTitle, m_nScreenWidth, m_nScreenHeight, 7, 7);
        //setCursorVisibility(false);
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
    }

    virtual void Update(float fElapsedTime)
    {      

            // GAME LOGIC ============================================
        ticksSinceLastTurn++;
        if (turn < nextTurn && ticksSinceLastTurn >= 6)
        {
            turn++;
            ticksSinceLastTurn = 0;
            for (int i = 0; i < 4; i++)
                gameAction(i, playerActions[i]);
        }

            if ((ticksSinceLastTurn < 6 || !bMultiplayer) && !pause)
            {
                
                for (int i = 0; i < players.size(); i++) players[i]->spawnUnitCooldown--;

                waveTimer++;

                if (waveTimer == 1 || waveTimer % 600 == 0)
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

                                // Unbalanced on purpose for testing reasons
                                //if (players[i]->getTeam() == 1)
                                    //wave.push_back(new Knight());

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
                    if (cDistance(projectile->second->fX, projectile->second->fY, projectile->second->fTargetX, projectile->second->fTargetY) > 0) {
                        projectile->second->move(projectile->second->fTargetX, projectile->second->fTargetY);
                        ++projectile;
                    }
                    else
                    {
                        int toBeDestroyed = projectile->second->getID();
                        ++projectile;
                        destroyEntity(toBeDestroyed);
                    }
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
                                if (cDistance(building.second->fX, building.second->fY, unit.second->fX, unit.second->fY) < building.second->fAttackDistance)
                                    building.second->setTargetUnit(unit.second->getID());
                            }
                        }
                    }

                    if (building.second->getTargetUnit() != -1)
                    {
                        building.second->setTarget(units[building.second->getTargetUnit()]->fX, units[building.second->getTargetUnit()]->fY);

                        if (cDistance(building.second->fX, building.second->fY, units[building.second->getTargetUnit()]->fX, units[building.second->getTargetUnit()]->fY) <= building.second->fAttackRange)
                        {
                            shootProjectile(building.second, building.second->attack(units[building.second->getTargetUnit()]));
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
                        if (cDistance(unit.second->fX, unit.second->fY, unit.second->fTargetX, unit.second->fTargetY) >= unit.second->fAttackRange)
                            unit.second->move(unit.second->fTargetX, unit.second->fTargetY);

                        if (cDistance(unit.second->fX, unit.second->fY, unit.second->fDefaultTargetX, unit.second->fDefaultTargetY) <= unit.second->fAttackRange)
                        {
                            int id = -1;
                            float min = 100;
                            for (int i = 0; i < players.size(); i++)
                            {
                                if (players[i]->getTeam() != unit.second->getTeam() && players[i]->teamBuildings.size() >= 1)
                                {
                                    for (int j = 0; j < players[i]->teamBuildings.size(); j++)
                                    {
                                        float fDistance = cDistance(unit.second->fX, unit.second->fY, players[i]->teamBuildings[j]->fX, players[i]->teamBuildings[j]->fY);
                                        if (fDistance < min)
                                        {
                                            id = players[i]->teamBuildings[j]->getID();
                                            min = fDistance;
                                        }
                                        unit.second->setDefaultTarget(buildings[id]->fX, buildings[id]->fY);
                                    }
                                    
                                }
                            }
                        }
                            
                           

                        if (unit.second->getTargetUnit() == -1)
                        {
                            int id = -1;
                            float min = unit.second->fAttackDistance;
                            for (auto& unit2 : units)
                            {
                                if (unit.second->getID() != unit2.second->getID())
                                {
                                    float fDistance = cDistance(unit.second->fX, unit.second->fY, unit2.second->fX, unit2.second->fY);
                                    if (fDistance < min && unit.second->getTeam() != unit2.second->getTeam() && unit.second->getTargetUnit() == -1)
                                    {
                                        min = fDistance;
                                        id = unit2.second->getID();
                                    }
                                }
                            }
                            unit.second->setTargetUnit(id);
                            if (unit.second->getTargetUnit() == -1 && unit.second->getTargetBuilding() == -1)
                            {
                                unit.second->setTarget(unit.second->fDefaultTargetX, unit.second->fDefaultTargetY);
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
                                swprintf_s(&bfScreen[m_nScreenWidth * 8], leng + 1, L"Unit Target %i: %i", unitIndex, units[unitIndex]->getTargetUnit());
                                leng = snprintf(NULL, 0, "Units Size: %i", (int)units.size());
                                swprintf_s(&bfScreen[m_nScreenWidth * 9], leng + 1, L"Units Size: %i", (int)units.size());
                                writeToScreen(bfScreen, m_nScreenWidth * m_nScreenHeight);
                                this_thread::sleep_for(10000ms);
                            }*/
                            unit.second->setTarget(units[unit.second->getTargetUnit()]->fX, units[unit.second->getTargetUnit()]->fY);

                            if (cDistance(unit.second->fX, unit.second->fY, unit.second->fTargetX, unit.second->fTargetY) <= unit.second->fAttackRange)
                            {
                                shootProjectile(unit.second, unit.second->attack(units[unit.second->getTargetUnit()]));
                            }
                        }
                        else
                        {
                            // Small guards, activate them if you think TargetUnits are getting out of range.
                            /*if ((int)units.size() >= 1 && (units[a]->getTargetUnit() > (int)units.size() || units[a]->getTargetUnit() < -1))
                            {
                                int leng;
                                leng = snprintf(NULL, 0, "Unit Target %i: %i", unitIndex, units[unitIndex]->getTargetUnit());
                                swprintf_s(&bfScreen[m_nScreenWidth * 8], leng + 1, L"Unit Target %i: %i", unitIndex, units[unitIndex]->getTargetUnit());
                                leng = snprintf(NULL, 0, "Units Size: %i", (int)units.size());
                                swprintf_s(&bfScreen[m_nScreenWidth * 9], leng + 1, L"Units Size: %i", (int)units.size());
                                writeToScreen(bfScreen, m_nScreenWidth * m_nScreenHeight);
                                this_thread::sleep_for(10000ms);
                            }*/
                            if (unit.second->getTargetBuilding() >= 0)
                            {
                                unit.second->setTarget(buildings[unit.second->getTargetBuilding()]->fX, buildings[unit.second->getTargetBuilding()]->fY);

                                if (cDistance(unit.second->fX, unit.second->fY, unit.second->fTargetX, unit.second->fTargetY) < unit.second->fAttackRange)
                                {
                                    shootProjectile(unit.second, unit.second->attack(buildings[unit.second->getTargetBuilding()]));
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
                                int team = unit.second->getLastHitID();
                                int player = unit.second->getTeam();

                                    //int team = units[killer]->getTeam();
                                    
                                    players[team]->addGold(unit.second->nKillReward);

                                    if (unit.second->sName == "Tremendinius") players[player]->tremendiniusAlive = false;

                                    if (unit.second->sName == "Minigun") players[player]->minigunAlive = false;

                                    /*if (unit.second->sName == "Footman") players[team]->addGold(50);
                                    else if (unit.second->sName == "Archer") players[team]->addGold(100);
                                    else if (unit.second->sName == "Mage") players[team]->addGold(150);
                                    else if (unit.second->sName == "Knight") players[team]->addGold(350);*/
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
                            if (waveTimer < 3000)
                            {
                                if (AIaction != 4) gameAction(i, AIaction);
                            }
                            else if (waveTimer < 6000 && players[i]->getGold() > 1000)
                            {
                                if (AIaction != 4) gameAction(i, AIaction);
                            }
                            else if (waveTimer < 9000 && players[i]->getGold() > 2000)
                            {
                                if (AIaction != 4) gameAction(i, AIaction);
                            }
                            else if (waveTimer < 12000 && players[i]->getGold() > 3000)
                            {
                                if (AIaction != 4) gameAction(i, AIaction);
                            }
                            else if (waveTimer < 15000 && players[i]->getGold() > 4000)
                            {
                                if (AIaction != 4) gameAction(i, AIaction);
                            }
                            else if (players[i]->getGold() > 5000)
                            {
                                if (AIaction != 4) gameAction(i, AIaction);
                            }
                            
                        }
                    }
                }
                

            }

    }

    virtual void Render()
    {
        // RENDER OUTPUT ============================================

        //Clear screen
        SDL_RenderClear(m_Renderer);

        //Tiles in Screen
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
            if ((entity.second->fX > fScreenLeftBorder - entity.second->fWidth && entity.second->fX - entity.second->fWidth < fScreenRightBorder) && (entity.second->fY > fScreenTopBorder - entity.second->fHeight && entity.second->fY - entity.second->fHeight < fScreenBottomBorder))
            {
                objectsToRender++;
                int enemyScreenLocationX = (int)((float)(entity.second->fX - currentPlayer->getCameraX() - (float)(entity.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                int enemyScreenLocationY = (int)((float)(entity.second->fY - currentPlayer->getCameraY() - (float)(entity.second->fHeight / 3.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);
                
                float realWidth = entity.second->fWidth * (float)nTileSize;
                float realHeight = entity.second->fHeight * (float)nTileSize;

                SDL_Rect renderQuad = { enemyScreenLocationX, enemyScreenLocationY, (int)realWidth, (int)realHeight };

                int team = entity.second->getTeam();

                auto it = m_Textures[team].find(entity.second->pSprite);

                if (entity.second->pSprite != "" && it == m_Textures[team].end())
                {
                    SDL_Surface* loadedSurface = IMG_Load(entity.second->pSprite.c_str());

                    SDL_Surface* mSurfacePixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(m_Window), 0);

                    SDL_FreeSurface(loadedSurface);

                    Uint32* pixels = static_cast<Uint32*>(mSurfacePixels->pixels);

                    int pixelCount = (mSurfacePixels->pitch / 4) * mSurfacePixels->h;

                    Uint32 colorKey = SDL_MapRGBA(mSurfacePixels->format, 0xFA, 0xFA, 0xFA, 0xFF);
                    int team = entity.second->getTeam();
                    Uint32 teamColor = SDL_MapRGBA(mSurfacePixels->format, teamColors[team].r, teamColors[team].g, teamColors[team].b, teamColors[team].a);

                    //Color key pixels
                    for (int i = 0; i < pixelCount; ++i)
                    {
                        if (pixels[i] == colorKey)
                        {
                            pixels[i] = teamColor;
                        }
                    }

                    SDL_SetColorKey(mSurfacePixels, SDL_TRUE, SDL_MapRGB(mSurfacePixels->format, 0xAA, 0xAA, 0xAA));

                    m_Textures[team].insert({ entity.second->pSprite, SDL_CreateTextureFromSurface(m_Renderer, mSurfacePixels) });

                    SDL_FreeSurface(mSurfacePixels);

                    

                }
                SDL_RenderCopy(m_Renderer, m_Textures[team][entity.second->pSprite], NULL, &renderQuad);
            }
        }

        for (auto& unit : units)
        {
            if ((unit.second->fX > fScreenLeftBorder - unit.second->fWidth && unit.second->fX - unit.second->fWidth < fScreenRightBorder) && (unit.second->fY > fScreenTopBorder - unit.second->fHeight && unit.second->fY - unit.second->fHeight < fScreenBottomBorder))
            {
                objectsToRender++;
                int enemyScreenLocationX = (int)((float)(unit.second->fX - currentPlayer->getCameraX() - (float)(unit.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                int enemyScreenLocationY = (int)((float)(unit.second->fY - currentPlayer->getCameraY() - (float)(unit.second->fHeight / 3.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);

                SDL_Rect HealthBar = { enemyScreenLocationX + (unit.second->fWidth * nTileSize) / 4, enemyScreenLocationY - (unit.second->fHeight * nTileSize) / 4, (unit.second->fWidth * nTileSize) / 2, (unit.second->fWidth * nTileSize) / 6 };
                SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(m_Renderer, &HealthBar);

                SDL_Rect CurrentHealth = { enemyScreenLocationX + (unit.second->fWidth * nTileSize) / 4, enemyScreenLocationY - (unit.second->fHeight * nTileSize) / 4, (unit.second->fWidth * nTileSize) / 2 * ((float)unit.second->nHealth / (float)unit.second->nMaxHealth), (unit.second->fWidth * nTileSize) / 6};
                SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderFillRect(m_Renderer, &CurrentHealth);

            }
        }

        for (auto& building : buildings)
        {
            if ((building.second->fX > fScreenLeftBorder - building.second->fWidth && building.second->fX - building.second->fWidth < fScreenRightBorder) && (building.second->fY > fScreenTopBorder - building.second->fHeight && building.second->fY - building.second->fHeight < fScreenBottomBorder))
            {
                objectsToRender++;
                int enemyScreenLocationX = (int)((float)(building.second->fX - currentPlayer->getCameraX() - (float)(building.second->fWidth / 2.0f)) * (float)nTileSize + (float)(fHorizontalTilesInScreen / 2.0f) * (float)nTileSize);
                int enemyScreenLocationY = (int)((float)(building.second->fY - currentPlayer->getCameraY() - (float)(building.second->fHeight / 3.0f)) * (float)nTileSize + (float)(fVerticalTilesInScreen / 2.0f) * (float)nTileSize);

                SDL_Rect HealthBar = { enemyScreenLocationX + (building.second->fWidth * nTileSize) / 4, enemyScreenLocationY - (building.second->fHeight * nTileSize) / 4, (building.second->fWidth * nTileSize) / 2, (building.second->fWidth * nTileSize) / 6 };
                SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(m_Renderer, &HealthBar);

                SDL_Rect CurrentHealth = { enemyScreenLocationX + (building.second->fWidth * nTileSize) / 4, enemyScreenLocationY - (building.second->fHeight * nTileSize) / 4, (building.second->fWidth * nTileSize) / 2 * ((float)building.second->nHealth / (float)building.second->nMaxHealth), (building.second->fWidth * nTileSize) / 6 };
                SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderFillRect(m_Renderer, &CurrentHealth);

                if (building.second->bSelected == true && building.second->getTeam() == currentPlayer->getTeam())
                {
                    SDL_Rect Selection = { enemyScreenLocationX - (building.second->fWidth * nTileSize) / 4, enemyScreenLocationY - (building.second->fHeight * nTileSize) / 4, (building.second->fWidth * nTileSize) * 1.5f, (building.second->fHeight * nTileSize) * 1.5f };
                    SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xFF, 0x00, 0xFF);
                    SDL_RenderDrawRect(m_Renderer, &Selection);
                }
            }
        }

        SDL_SetRenderDrawColor(m_Renderer, 0x35, 0xa7, 0x42, 0xFF);

        //Update screen
        SDL_RenderPresent(m_Renderer);

        //Print info

        string windowTitle = "Caelis Chaos 0.3.0 Alpha -";
        windowTitle += " Gold: " + to_string(currentPlayer->getGold());
        windowTitle += " - Tile size: " + to_string(nTileSize);
        windowTitle += " - FPS: " + to_string(avgFPS);
        windowTitle += " - Next wave: " + to_string(30 - (waveTimer / 20) % 30);
        windowTitle += " - Objects: " + to_string(objectsToRender);
        SDL_SetWindowTitle(m_Window, windowTitle.c_str());

        //
        //// Print Info
        ///*
        //int len = snprintf(NULL, 0, "Camera X: %.1f", fCameraX);
        //swprintf_s(&bfScreen[0].Char.UnicodeChar, len + 1, L"Camera X: %.1f", fCameraX);
        //len = snprintf(NULL, 0, "Camera Y: %.1f", fCameraY);
        //swprintf_s(&bfScreen[m_nScreenWidth].Char.UnicodeChar, len + 1, L"Camera Y: %.1f", fCameraY);
        //len = snprintf(NULL, 0, "Tile Size: %i", nTileSize);
        //swprintf_s(&bfScreen[m_nScreenWidth * 2].Char.UnicodeChar, len + 1, L"Tile Size: %i", nTileSize);
        //len = snprintf(NULL, 0, "Entities: %i", (int)units.size());
        //swprintf_s(&bfScreen[m_nScreenWidth * 3].Char.UnicodeChar, len + 1, L"Entities: %i", (int)units.size());
        //if (infoIndex == 0)
        //{
        //    for (int a = 0; a < (int)buildings.size(); a++)
        //    {
        //        len = snprintf(NULL, 0, "Fortress %i HP: %i", buildings[a]->getTeam(), buildings[a]->getHealth());
        //        swprintf_s(&bfScreen[m_nScreenWidth * (4 + a)].Char.UnicodeChar, len + 1, L"Fortress %i HP: %i", buildings[a]->getTeam(), buildings[a]->getHealth());
        //    }
        //}
        //else
        //{
        //    for (int i = 1; i < 5; i++)
        //    {
        //        int teamUnits = 0;
        //        for (int a = 0; a < (int)units.size(); a++)
        //        {
        //            if (units[a]->getTeam() == i) teamUnits++;
        //        }
        //        len = snprintf(NULL, 0, "Team %i Units: %i", i, teamUnits);
        //        swprintf_s(&bfScreen[m_nScreenWidth * (4 + i - 1)].Char.UnicodeChar, len + 1, L"Team %i Units: %i", i, teamUnits);
        //    }
        //}*/
        //
        //wchar_t s[256];
        //wstring sConsoleTitle2 = m_sConsoleTitle;
        //if(!pause) sConsoleTitle2.append(L" - Gold %i - Units %i - Ticks since start: %i");
        //else sConsoleTitle2.append(L" - Gold %i - Units %i - Ticks since start: %i - Paused");
        //const wchar_t* cConsoleTitle = sConsoleTitle2.c_str();
        //swprintf_s(s, 256, cConsoleTitle, currentPlayer->getGold(), currentPlayer->teamUnits.size(), waveTimer);
        //SetConsoleTitle(s);
    }

private:

    // Generate Base Map

    void createMap()
    {
        Fortress* Fortress1 = new Fortress();
        int fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(0, -24);
        entityList[fortressID]->setTeam(0);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(-24, 0);
        entityList[fortressID]->setTeam(1);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(0, 24);
        entityList[fortressID]->setTeam(2);
        Fortress1 = new Fortress();
        fortressID = createEntity(Fortress1);
        buildings[fortressID] = Fortress1;
        entityList[fortressID]->setCoords(24, 0);
        entityList[fortressID]->setTeam(3);
        
        // Team 0
        Barracks* Barracks1 = new Barracks();
        int barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(0, -21);
        entityList[barracksID]->setTeam(0);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-3, -24);
        entityList[barracksID]->setTeam(0);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(3, -24);
        entityList[barracksID]->setTeam(0);

        Tower* tower1 = new Tower();
        int towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-2, -22);
        entityList[towerID]->setTeam(0);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(2, -22);
        entityList[towerID]->setTeam(0);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-2, -26);
        entityList[towerID]->setTeam(0);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(2, -26);
        entityList[towerID]->setTeam(0);

        
        // Team 1
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-21, 0);
        entityList[barracksID]->setTeam(1);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-24, 3);
        entityList[barracksID]->setTeam(1);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-24, -3);
        entityList[barracksID]->setTeam(1);

        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-22, 2);
        entityList[towerID]->setTeam(1);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-22, -2);
        entityList[towerID]->setTeam(1);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-26, -2);
        entityList[towerID]->setTeam(1);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-26, 2);
        entityList[towerID]->setTeam(1);

        // Team 2
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(0, 21);
        entityList[barracksID]->setTeam(2);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(-3, 24);
        entityList[barracksID]->setTeam(2);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(3, 24);
        entityList[barracksID]->setTeam(2);

        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-2, 22);
        entityList[towerID]->setTeam(2);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(2, 22);
        entityList[towerID]->setTeam(2);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(-2, 26);
        entityList[towerID]->setTeam(2);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(2, 26);
        entityList[towerID]->setTeam(2);

        // Team 3
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(21, 0);
        entityList[barracksID]->setTeam(3);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(24, 3);
        entityList[barracksID]->setTeam(3);
        Barracks1 = new Barracks();
        barracksID = createEntity(Barracks1);
        buildings[barracksID] = Barracks1;
        entityList[barracksID]->setCoords(24, -3);
        entityList[barracksID]->setTeam(3);
        

        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(22, 2);
        entityList[towerID]->setTeam(3);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(22, -2);
        entityList[towerID]->setTeam(3);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(26, -2);
        entityList[towerID]->setTeam(3);
        tower1 = new Tower();
        towerID = createEntity(tower1);
        buildings[towerID] = tower1;
        entityList[towerID]->setCoords(26, 2);
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

            players[i]->setCamera(players[i]->teamBuildings[0]->fX, players[i]->teamBuildings[0]->fY);
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
        delete entityList[ID];
        entityList.erase(ID);
        if (units.find(ID) != units.end()) units.erase(ID);
        if (buildings.find(ID) != buildings.end()) buildings.erase(ID);
        if (projectiles.find(ID) != projectiles.end()) projectiles.erase(ID);
    }

    void shootProjectile(Entity* entity, string projectile)
    {
        if (projectile == "Bullet")
        {
            Bullet* bullet = new Bullet();
            bullet->fX = entity->fX;
            bullet->fY = entity->fY;
            bullet->setTeam(entity->getTeam());
            bullet->setTarget(entity->fTargetX, entity->fTargetY);
            projectiles[createEntity(bullet)] = bullet;
        }
        else if (projectile == "Fireball")
        {
            Fireball* fireball = new Fireball();
            fireball->fX = entity->fX;
            fireball->fY = entity->fY;
            fireball->setTeam(entity->getTeam());
            fireball->setTarget(entity->fTargetX, entity->fTargetY);
            projectiles[createEntity(fireball)] = fireball;
        }
        else if (projectile == "Cannonball")
        {
            Cannonball* cannonball = new Cannonball();
            cannonball->fX = entity->fX;
            cannonball->fY = entity->fY;
            cannonball->setTeam(entity->getTeam());
            cannonball->setTarget(entity->fTargetX, entity->fTargetY);
            projectiles[createEntity(cannonball)] = cannonball;
        }
        else if (projectile == "BulletMG")
        {
            BulletMG* bulletMG = new BulletMG();
            bulletMG ->fX = entity->fX;
            bulletMG->fY = entity->fY;
            bulletMG->setTeam(entity->getTeam());
            bulletMG->setTarget(entity->fTargetX, entity->fTargetY);
            projectiles[createEntity(bulletMG)] = bulletMG;
        }
        
    }

    void gameAction(int player, int id)
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
            if (players[player]->teamBuildings.size() >= 1)
            { 
                if (players[player]->selectedBuildingID < players[player]->teamBuildings.size() - 1)
                {
                    if (currentPlayer == players[player]) players[player]->selectedBuilding()->select();
                    players[player]->selectedBuildingID++;
                    int counter = 0;
                    while (players[player]->selectedBuilding()->sName == "Tower" && counter < 10)
                    {
                        if (players[player]->selectedBuildingID < players[player]->teamBuildings.size() - 1)
                            players[player]->selectedBuildingID++;
                        else
                            players[player]->selectedBuildingID = 0;
                        counter++;
                    }
                    if (currentPlayer == players[player]) players[player]->selectedBuilding()->select();
                }
                else
                {
                    if (currentPlayer == players[player]) players[player]->selectedBuilding()->select();
                    players[player]->selectedBuildingID = 0;
                    int counter = 0;
                    while (players[player]->selectedBuilding()->sName == "Tower" && counter < 10)
                    {
                        if (players[player]->selectedBuildingID < players[player]->teamBuildings.size() - 1)
                            players[player]->selectedBuildingID++;
                        else
                            players[player]->selectedBuildingID = 0;
                        counter++;
                    }
                    if (currentPlayer == players[player]) players[player]->selectedBuilding()->select();
                }
            }
            break;
        case 6:
            if (players[player]->teamBuildings.size() >= 1)
            {
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
        

protected:

};

int main(int argc, char* args[])
{
    Caelis_Chaos game;
    game.Start();

    bool client = false;
    bool server = false;
    char option;

    cout << "Start server(s) or client(c)?" << endl;
    cin >> option;

    if (option == 'c') client = true;
    else if (option == 's') server = true;

    /*if (client)
    {
        
    }*/

    return 0;
}