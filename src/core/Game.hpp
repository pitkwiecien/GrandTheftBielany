#pragma once
#include "SDLContext.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "Timer.hpp"
#include "StateMachine.hpp"
#include "resources/TextureManager.hpp"
#include "resources/FontManager.hpp"

// Punkt centralny. Kolejność pól = kolejność inicjalizacji:
// kontekst SDL musi powstać zanim powstanie okno/renderer.
class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    SDLContext     m_sdl;        // RAII init — MUSI być pierwsze
    Window         m_window;
    Renderer       m_renderer;
    InputManager   m_input;
    Timer          m_timer;

    TextureManager m_textures;
    FontManager    m_fonts;

    StateMachine   m_states;
    bool           m_running = true;

    // Stały krok logiki (akumulator), max klatka by uniknąć spirali śmierci.
    static constexpr float kFixedDt   = 1.f / 60.f;
    static constexpr float kMaxFrame  = 0.25f;
};
