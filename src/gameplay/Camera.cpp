#include "gameplay/Camera.hpp"

void Camera::setViewport(int w, int h) {
    vw = w;
    vh = h;
}

SDL_Rect Camera::worldToScreen(Vec2 worldPos, int w, int h) const {
    int sx = static_cast<int>(worldPos.x - m_center.x + vw * 0.5f);
    int sy = static_cast<int>(worldPos.y - m_center.y + vh * 0.5f);
    return SDL_Rect{ sx - w / 2, sy - h / 2, w, h };
}