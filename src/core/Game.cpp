#include "core/Game.hpp"
#include "states/MenuState.hpp" 

Game::Game()
    : m_sdl(),
      m_window("Grand Theft Bielany", 1280, 720),
      m_renderer(m_window),
      m_input(),
      m_timer(),
      m_textures(m_renderer),
      m_fonts(),
      m_audio(),
      m_states(),
      m_running(true)
{
    // m_states.pushState(std::make_unique<MenuState>());
}

void Game::run() {
    float accumulator = 0.0f;

    m_timer.tick();

    while (m_running) {
        float dt = m_timer.tick();
        
        // Zapobiega spirali śmierci
        if (dt > kMaxFrame) {
            dt = kMaxFrame; 
        }

        accumulator += dt;

        processEvents();

        while (accumulator >= kFixedDt) {
            update(kFixedDt);
            accumulator -= kFixedDt;
        }

        render();
    }
}
