#include <iostream>
#include "TobiGameEngine.h"

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
        bool bKey[7];
        bool bHoldKey[7] = { false };
        bool bShowGrid = true;

        float fCameraX = 0;
        float fCameraY = 0;

        float enemyX = 3;
        float enemyY = 3;

        float enemyXb = 2;
        float enemyYb = 2;

        int nMoveTimer = 0;

        float fScreenRatio = (float)nScreenWidth / (float)nScreenHeight;
        int nTileSize = 16;
        float fVerticalTilesInScreen = (float)nScreenHeight / (float)nTileSize;
        float fHorizontalTilesInScreen = (float)nScreenWidth / (float)nTileSize;
        float fScale = 1;
        

        // LOAD ASSETS =============

        sprites[0].append(L"  █  ██  ██  █  ");
        sprites[0].append(L"  ████████████  ");
        sprites[0].append(L"  ██  ████  ██  ");
        sprites[0].append(L"  ██  ████  ██  ");
        sprites[0].append(L"  ████████████  ");
        sprites[0].append(L"  ████████████  ");
        sprites[0].append(L"█ ████████████ █");
        sprites[0].append(L"█ ████████████ █");
        sprites[0].append(L"████████████████");
        sprites[0].append(L"████████████████");
        sprites[0].append(L"████████████████");
        sprites[0].append(L"███████  ███████");
        sprites[0].append(L"██████    ██████");
        sprites[0].append(L"██████    ██████");
        sprites[0].append(L"██████    ██████");
        sprites[0].append(L"██████    ██████");

        sprites[1].append(L"  █  ");
        sprites[1].append(L"█████");
        sprites[1].append(L" ███ ");
        sprites[1].append(L" █ █ ");
        sprites[1].append(L" █ █ ");

        // Game Loop
        while (!bGameOver)
        {
            // GAME TIMING  ============================================

            setGameTick(16);

            // INPUT ============================================

            for (int k = 0; k < 7; k++)
                bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x26ZXC"[k]))) != 0;

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

            // GAME LOGIC ============================================

            enemyYb -= 0.02f;

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

            int enemyScreenLocationX = (enemyX - fCameraX) * nTileSize + (fHorizontalTilesInScreen / 2) * nTileSize;
            int enemyScreenLocationY = (enemyY - fCameraY) * nTileSize + (fVerticalTilesInScreen / 2) * nTileSize;
            int enemyScreenLocationXb = (enemyXb - fCameraX) * nTileSize + (fHorizontalTilesInScreen / 2) * nTileSize;
            int enemyScreenLocationYb = (enemyYb - fCameraY) * nTileSize + (fVerticalTilesInScreen / 2) * nTileSize;

            fScale = (float)nTileSize / (float)16;

            // Draw sprites

            drawSprite(scaleSprite(sprites[0], 16, (int)(16 * fScale)), enemyScreenLocationX, enemyScreenLocationY, (int)(16 * fScale));
            drawSprite(scaleSprite(sprites[1], 5, (int)(5 * fScale)), enemyScreenLocationXb, enemyScreenLocationYb, (int)(5 * fScale));

            int len = snprintf(NULL, 0, "Camera X: %.1f", fCameraX);
            swprintf_s(&bfScreen[0], len+1, L"Camera X: %.1f", fCameraX);
            len = snprintf(NULL, 0, "Camera Y: %.1f", fCameraY);
            swprintf_s(&bfScreen[nScreenWidth], len+1, L"Camera Y: %.1f", fCameraY);
            len = snprintf(NULL, 0, "Tile Size: %i", nTileSize);
            swprintf_s(&bfScreen[nScreenWidth * 2], len + 1, L"Tile Size: %i", nTileSize);
            writeToScreen(bfScreen, nScreenWidth * nScreenHeight);
        }

        return 0;
    }

private:

    wstring sprites[2];

    // Generate Base Map
    void createMap()
    {
    

    
    }

protected:

    

};

int main()
{
    Caelis_Chaos game;
    game.start();

    return 0;
}