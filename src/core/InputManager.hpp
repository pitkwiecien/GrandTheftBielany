#pragma once
#include <SDL.h>
#include <array>
#include "math/Vec2.hpp"

// Trzyma snapshot stanu klawiatury/myszy.
// Pętla: beginFrame() -> handleEvent() dla każdego SDL_Event -> zapytania.
class InputManager {
public:
    InputManager();

    // Czyści flagi "naciśnięte/zwolnione w tej klatce".
    void beginFrame();

    // Przetwarza pojedyncze zdarzenie SDL.
    void handleEvent(const SDL_Event& e);

    // Klawisz jest aktualnie wciśnięty.
    bool isDown(SDL_Scancode key) const;

    // Klawisz został wciśnięty dokładnie w tej klatce.
    bool wasPressed(SDL_Scancode key) const;

    // Klawisz został zwolniony dokładnie w tej klatce.
    bool wasReleased(SDL_Scancode key) const;

    Vec2 mousePos()  const { return m_mousePos; }
    bool mouseDown(Uint8 button) const;
    bool mouseClicked(Uint8 button) const;

    bool quitRequested() const { return m_quit; }

private:
    static constexpr int kKeyCount = SDL_NUM_SCANCODES;

    const Uint8* m_keyState = nullptr;          // własność SDL
    std::array<bool, kKeyCount> m_pressed{};
    std::array<bool, kKeyCount> m_released{};

    Vec2  m_mousePos{};
    Uint32 m_mouseState   = 0;
    Uint32 m_mouseClicked = 0;
    bool   m_quit = false;
};
