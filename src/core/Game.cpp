#include "core/Game.hpp"
#include "states/PlayState.hpp"

Game::Game()
    : m_sdl(),
      m_window("Grand Theft Bielany", 1280, 720),
      m_renderer(m_window),
      m_input(),
      m_timer(),
      m_textures(m_renderer),
      m_fonts(),
      m_states(),
      m_running(true)
{
    StateContext ctx;
    ctx.states   = &m_states;
    ctx.renderer = &m_renderer;
    ctx.input    = &m_input;

    m_states.push(
        std::make_unique<PlayState>(
            ctx,
            m_textures,
            m_fonts));

    m_states.applyPending();
}

void Game::processEvents() {
    m_input.beginFrame();

    SDL_Event e;

    while (SDL_PollEvent(&e)) {

        if (e.type == SDL_QUIT)
            m_running = false;

        m_input.handleEvent(e);
        m_states.handleEvent(e);
    }

    if (m_input.quitRequested())
        m_running = false;

    m_states.applyPending();

    if (m_states.empty())
        m_running = false;
}

void Game::update(float dt) {

    m_states.update(dt);

    m_states.applyPending();

    if (m_states.empty())
        m_running = false;
}

void Game::render() {

    m_renderer.clear({20, 20, 20, 255});

    m_states.render(m_renderer);

    m_renderer.present();
}

void Game::run() {

    float accumulator = 0.0f;

    m_timer.tick();

    while (m_running) {

        float dt = m_timer.tick();

        if (dt > kMaxFrame)
            dt = kMaxFrame;

        accumulator += dt;

        processEvents();

        while (accumulator >= kFixedDt) {

            update(kFixedDt);

            accumulator -= kFixedDt;
        }

        render();
    }
}