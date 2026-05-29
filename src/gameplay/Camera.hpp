#pragma once
#include "math/Math.hpp"
#include <SDL.h>


class Camera {
public:
    void setViewport(int w, int h);
    void follow(Vec2 target, float dt, float smoothing = 8.f);
    SDL_Rect worldToScreen(Vec2 worldPos, int w, int h) const;
    Vec2     screenToWorld(int sx, int sy) const;
    bool isVisible(Vec2 worldPos, float radius) const;
    Vec2 center() const { return m_center; }

private:
    Vec2 m_center{};
    int  vw = 0;
    int  vh = 0;
};
