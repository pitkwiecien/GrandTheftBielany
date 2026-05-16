#pragma once
#include <SDL.h>
#include "math/Vec2.hpp"

class InputManager {
public:
    void beginFrame();                 // zeruje "pressed/released" tej klatki
    void handleEvent(const SDL_Event& e);

    bool isDown(SDL_Scancode key) const;
    bool wasPressed(SDL_Scancode key) const;   // tylko ta klatka
    Vec2 mousePos() const;
    bool mouseDown(Uint8 button) const;
    bool quitRequested() const { return m_quit; }

private:
    const Uint8* m_keyState = nullptr; // SDL_GetKeyboardState
    bool m_quit = false;
    // tablice na "pressed this frame" itd.
};