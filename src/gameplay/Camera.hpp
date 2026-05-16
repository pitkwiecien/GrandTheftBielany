#pragma once
#include <SDL.h>
#include "math/Vec2.hpp"

// SDL2 nie ma sf::View — kamerę liczymy ręcznie.
// Płynnie podąża za graczem, daje konwersję świat<->ekran i culling.
class Camera {
public:
    void setViewport(int w, int h);
    void follow(Vec2 target, float dt, float smoothing = 8.f);

    // Pozycja świata -> prostokąt na ekranie dla sprite'a w*h.
    SDL_Rect worldToScreen(Vec2 worldPos, int w, int h) const;
    Vec2     screenToWorld(int sx, int sy) const;

    // Czy obiekt o danym promieniu jest w widoku (culling).
    bool isVisible(Vec2 worldPos, float radius) const;

    Vec2 center() const { return m_center; }

private:
    Vec2 m_center{};
    int  m_vw = 0;
    int  m_vh = 0;
};
