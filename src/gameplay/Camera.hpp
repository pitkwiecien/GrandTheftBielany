#pragma once
#include "math/Math.hpp"
#include <SDL.h>


class Camera {
public:
    void setViewport(int w, int h);
    SDL_Rect worldToScreen(Vec2 worldPos, int w, int h) const;

private:
    Vec2 m_center{};
    int  vw = 0;
    int  vh = 0;
};
