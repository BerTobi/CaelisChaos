#include "Match.h"
#include "../CaelisEngine.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>


Match::Match()
{
    m_backgroundColor = SDLColor(0x55, 0xFF, 0x55, 255);
}

void Match::init(CaelisEngine* game)
{
    m_gameMap = new Map();
    m_gameRenderer = new Renderer(m_gameMap, game->getRenderer(), game->getFont(), game->getScreenResolution());
    m_keyboardState = game->keyboardState;
    m_GUIComponents["Debug info"] = new Textbox(SDLFPoint(0.0f, 0.0f), SDLFPoint(0.3f, 0.3f), game->getScreenResolution(), SDLColor( 100, 100, 100, 0 ));
}

void Match::cleanup()
{
	delete m_gameMap;
	delete m_gameRenderer;
}

std::uint64_t Match::update()
{
    // gameMap->getEntities()[0].m_coords = { gameMap->getEntities()[0].m_coords.x - 0.01f, gameMap->getEntities()[0].m_coords.y };
    if (m_nTicksSinceStart % 200 == 0) // Spawn footman from barracks
    {
        std::vector<Entity*> barracks;
        for (int i = 0; i < m_gameMap->getEntities().size(); i++)
        {
            if (m_gameMap->getEntities()[i]->m_sType == "Barracks")
            {
                barracks.push_back(m_gameMap->getEntities()[i]);
            }
        }

        for (int i = 0; i < barracks.size(); i++)
        {
            Unit* newFootman = new Unit(m_gameMap->getUnitPrototypeByID("footman"), SDLFPoint(((float)(rand()) / (float)(rand())) * 100 - 50, ((float)(rand()) / (float)(rand())) * 100 - 50));
            m_gameMap->getEntities().push_back(newFootman);
            m_units.push_back(newFootman);
        }


            
        
    }
    
    if (m_nTicksSinceStart % 2 == 0)        // Unit movement
    {
        for (Unit* unit : m_units)
        {
            SDL_FPoint randomPos = SDLFPoint(30.0f, 30.0f);
            SDL_FPoint currentPos = unit->m_coords;

            if (!(randomPos == currentPos))     // Equality defined for SDL_FPoint in Util.h (likely to be removed later)
            {
                
                SDL_FPoint fDistance = { randomPos.x - currentPos.x , randomPos.y - currentPos.y }; // All of this should be an entity method

                float fHypotenuse = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
                float fHorizontalAngle = acos(fDistance.x / fHypotenuse);
                float fVerticalAngle = asin(fDistance.y / fHypotenuse);

                //float fSpeedX = fMovementSpeed * cos(fHorizontalAngle);
                //float fSpeedY = fMovementSpeed * sin(fVerticalAngle);

                float fSpeedX = 0.2;
                float fSpeedY = 0.2;

                SDL_FPoint nextPosition = currentPos;

                if (randomPos.x != currentPos.x)
                    if (abs(randomPos.x - currentPos.x) < fSpeedX)
                        nextPosition.x = randomPos.x;
                    else
                        nextPosition.x = currentPos.x + fSpeedX;

                if (randomPos.y != currentPos.y)
                    if (abs(randomPos.y - currentPos.y) < fSpeedY)
                        nextPosition.y = randomPos.y;
                    else
                        nextPosition.y = currentPos.y + fSpeedY;

                //fMovementAngle = atan2f(mTargetPosition.y - mPosition.y, mTargetPosition.x - mPosition.x) * 180.0f / PI;

                unit->m_coords = nextPosition;
            }
        }
    }
    m_nTicksSinceStart++;
    return SDL_GetTicksNS();
}

void Match::handleEvents(SDL_Event* eventHandler, CaelisEngine* game)
{
    while (SDL_PollEvent(eventHandler) != 0)
    {
        switch (eventHandler->type)
        {
        case SDL_EVENT_QUIT:
            game->quit();
            break;

        case SDL_EVENT_KEY_DOWN:
            if (m_keyboardState[SDL_SCANCODE_UP]) m_gameRenderer->moveCamera(SDLFPoint(-0.5f, -0.5f));
            if (m_keyboardState[SDL_SCANCODE_DOWN]) m_gameRenderer->moveCamera(SDLFPoint( 0.5f, 0.5f ));
            if (m_keyboardState[SDL_SCANCODE_LEFT]) m_gameRenderer->moveCamera(SDLFPoint( -0.5f, 0.5f ));
            if (m_keyboardState[SDL_SCANCODE_RIGHT]) m_gameRenderer->moveCamera(SDLFPoint( 0.5f, -0.5f ));
            if (m_keyboardState[SDL_SCANCODE_Z]) m_gameRenderer->scaleCameraTileSizeBy(2.0f);
            if (m_keyboardState[SDL_SCANCODE_X]) m_gameRenderer->scaleCameraTileSizeBy(0.5f);
            //if (m_keyboardState[SDL_SCANCODE_C]) m_gameRenderer->changeCameraTileSizeBy(1);
            //if (m_keyboardState[SDL_SCANCODE_V]) m_gameRenderer->changeCameraTileSizeBy(-1);
            if (m_keyboardState[SDL_SCANCODE_KP_PLUS]) game->changeTickRateBy(25);
            if (m_keyboardState[SDL_SCANCODE_KP_MINUS]) game->changeTickRateBy(-25);
            if (m_keyboardState[SDL_SCANCODE_F3]) m_GUIComponents["Debug info"]->m_bVisible = !m_GUIComponents["Debug info"]->m_bVisible;
            break;
        }
        handleGUIEvents(eventHandler, game);
    }
}

void Match::handleGUI(CaelisEngine* game)
{
    updateDebugInfo(game);
}

void Match::updateDebugInfo(CaelisEngine* game)
{
    std::ostringstream debugStream;
    std::uint64_t nFPS = 1000000000 / game->getFrametime();
    float fFrametime = game->getFrametime() / 1000000.0f;
    debugStream << "Entities: " << m_gameMap->getEntities().size() << "\nFPS: " << nFPS << "\nFrametime: " << fFrametime << "\nTicks: " << m_nTicksSinceStart;
    ((Textbox*)(m_GUIComponents["Debug info"]))->loadIconFromText(game->getRenderer(), game->getFont(), debugStream.str(), SDLColor(0xFF, 0x55, 0x55, 255));
}

void Match::render(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, COLOR_CHANNELS(m_backgroundColor));
    SDL_RenderClear(renderer);
    m_gameRenderer->renderTiles();
    m_gameRenderer->renderEntities();
    renderGUI(renderer);
    SDL_RenderPresent(renderer);
}
