#pragma once
#include <SDL.h>
#include "math/Vec2.hpp"

class Camera {
public:
    void follow(Vec2 target, float dt);   // płynne podążanie za graczem
    SDL_Rect worldToScreen(Vec2 worldPos, int w, int h) const;
    Vec2 center() const { return m_center; }
    void setViewport(int w, int h) { m_vw = w; m_vh = h; }

private:
    Vec2 m_center{};
    int  m_vw = 0, m_vh = 0;
};