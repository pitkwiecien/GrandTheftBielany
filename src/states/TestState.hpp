#pragma once
#include "core/GameState.hpp"
#include "core/Renderer.hpp"
#include <SDL.h>

// Tymczasowy stan do weryfikacji petli gry.
// Rysuje kolorowe tlo i zamyka sie na ESC lub klikniecie X.
class TestState : public GameState {
public:
    explicit TestState(StateMachine& states) : m_states(states) {}

    void handleEvent(const SDL_Event& e) override {
        if (e.type == SDL_QUIT ||
            (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
            m_states.clear();
    }

    void update(float dt) override {
        m_hue += dt * 60.f;
        if (m_hue >= 360.f) m_hue -= 360.f;
    }

    void render(Renderer& renderer) override {
        // Prosty cykl kolorow: czerwony -> zielony -> niebieski -> ...
        SDL_Color bg = hueToRGB(m_hue);
        renderer.clear(bg);

        SDL_Rect box{540, 310, 200, 100};
        renderer.drawRect(box, {0, 0, 0, 180}, true);
        renderer.drawRect(box, {255, 255, 255, 255}, false);
    }

private:
    StateMachine& m_states;
    float m_hue = 0.f;

    static SDL_Color hueToRGB(float h) {
        float s = 0.7f, v = 0.6f;
        float c  = v * s;
        float x  = c * (1.f - std::abs(std::fmod(h / 60.f, 2.f) - 1.f));
        float m  = v - c;
        float r, g, b;
        if      (h < 60)  { r=c; g=x; b=0; }
        else if (h < 120) { r=x; g=c; b=0; }
        else if (h < 180) { r=0; g=c; b=x; }
        else if (h < 240) { r=0; g=x; b=c; }
        else if (h < 300) { r=x; g=0; b=c; }
        else              { r=c; g=0; b=x; }
        return {
            static_cast<Uint8>((r+m)*255),
            static_cast<Uint8>((g+m)*255),
            static_cast<Uint8>((b+m)*255),
            255
        };
    }
};
