#include "Match.h"
#include "../CaelisEngine.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cmath>


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
	m_nTicksSinceStart = 0;
	m_nCurrentPlayer = 0;
	m_players[0] = Player(0);
	m_players[1] = Player(1);
	m_players[2] = Player(2);
	m_players[3] = Player(3);
	m_players[4] = Player(4);
	m_gameRenderer->setCamera(&m_players[m_nCurrentPlayer].m_Camera);
}

void Match::cleanup()
{
	delete m_gameMap;
	delete m_gameRenderer;
}

std::uint64_t Match::update()
{
    // gameMap->getEntities()[0].m_coords = { gameMap->getEntities()[0].m_coords.x - 0.01f, gameMap->getEntities()[0].m_coords.y };
    if (m_nTicksSinceStart % 900 == 0) // Spawn footman from barracks
    {
        std::vector<Entity*> barracks;
        for (size_t i = 0; i < m_gameMap->getEntities().size(); i++)
        {
            if (m_gameMap->getEntities()[i]->m_sType == "Barracks")
            {
                barracks.push_back(m_gameMap->getEntities()[i]);
            }
        }

        for (size_t i = 0; i < barracks.size(); i++)
        {
			//SDL_FPoint initialCoords = barracks[i]->m_coords;
			//m_gameMap->placeUnit("footman", initialCoords);
            //m_gameMap->placeUnit("footman", initialCoords);
            //m_gameMap->placeUnit("footman", initialCoords);
            //barracks[i]->executeAbility("TrainFootman");
			//barracks[i]->executeAbility("TrainFootman");
			//barracks[i]->executeAbility("TrainFootman");
        }
        
    }
    
    if (m_nTicksSinceStart % 2 == 0)        // Unit movement
    {
        for (size_t i = 0; i < m_gameMap->m_units.size(); ++i)
        {
			Entity* unit = m_gameMap->m_units[i];
            if (unit->m_movementTarget.x == 0.0f && unit->m_movementTarget.y == 0.0f)   // don't know how to specify "target not assigned"
            {
                SDL_FPoint randomPos = SDLFPoint((float)(rand() % 200 - 100), (float)(rand() % 200 - 100));
                unit->move(randomPos);
            }
            unit->move();
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
			if (m_keyboardState[SDL_SCANCODE_F4])
			{
					m_nCurrentPlayer = (m_nCurrentPlayer + 1) % 5;
					m_gameRenderer->setCamera(&m_players[m_nCurrentPlayer].m_Camera);
			}
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
	int nCurrentTeamPopulation = m_gameMap->getTeamPopulation(m_nCurrentPlayer);
    float fFrametime = game->getFrametime() / 1000000.0f;
    debugStream << "Entities: " << m_gameMap->getEntities().size() << "\nFPS: " << nFPS << "\nFrametime: " << fFrametime << "\nTicks: " << m_nTicksSinceStart << "\nCurrent Player: " << m_nCurrentPlayer << "\nPopulation: " << nCurrentTeamPopulation;
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