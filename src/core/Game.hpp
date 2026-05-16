#pragma once
#include "SDLContext.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "StateMachine.hpp"
#include "resources/TextureManager.hpp"
#include "resources/FontManager.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    SDLContext      m_sdl;          // musi być pierwsze (RAII init)
    Window          m_window;
    Renderer        m_renderer;
    InputManager    m_input;
    TextureManager  m_textures;
    FontManager     m_fonts;
    StateMachine    m_states;

    bool m_running = true;
    static constexpr float kFixedDt = 1.f / 60.f;
};