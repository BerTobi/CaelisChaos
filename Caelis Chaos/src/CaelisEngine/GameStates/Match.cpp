#include "Match.h"
#include "../CaelisEngine.h"
#include <cstdio>
#include <sstream>


Match::Match()
{
    m_backgroundColor = SDLColor(0, 200, 0, 255);
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

}

std::uint64_t Match::update()
{
    // gameMap->getEntities()[0].m_coords = { gameMap->getEntities()[0].m_coords.x - 0.01f, gameMap->getEntities()[0].m_coords.y };
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
            if (m_keyboardState[SDL_SCANCODE_Z]) m_gameRenderer->scaleCameraTileSizeBy(1.5f);
            if (m_keyboardState[SDL_SCANCODE_X]) m_gameRenderer->scaleCameraTileSizeBy(0.75f);
            if (m_keyboardState[SDL_SCANCODE_C]) m_gameRenderer->changeCameraTileSizeBy(1);
            if (m_keyboardState[SDL_SCANCODE_V]) m_gameRenderer->changeCameraTileSizeBy(-1);
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
    debugStream << "Entities: " << m_gameMap->getEntities().size() << "\nFPS: " << nFPS << "\nFrametime: " << fFrametime;
    ((Textbox*)(m_GUIComponents["Debug info"]))->loadIconFromText(game->getRenderer(), game->getFont(), debugStream.str(), SDLColor(255, 255, 255, 255));
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
