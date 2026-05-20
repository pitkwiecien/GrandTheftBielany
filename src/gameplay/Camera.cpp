#include "gameplay/Camera.hpp"
#include "math/MathUtils.hpp"

void Camera::setViewport(int w, int h) {
    vw = w;
    vh = h;
}

void Camera::follow(Vec2 target, float dt, float smoothing) {
    float t = smoothing * dt;

    m_center = MathUtils::lerp(m_center, target, t);
}

SDL_Rect Camera::worldToScreen(Vec2 worldPos, int w, int h) const{
    int sx = static_cast<int>(worldPos.x - m_center.x + vw * 0.5f);
    int sy = static_cast<int>(worldPos.y - m_center.y + vh * 0.5f);

    return SDL_Rect{
        sx - w / 2,
        sy - h / 2,
        w,
        h
    };
}

Vec2 Camera::screenToWorld(int sx, int sy) const {
    return {
        sx + m_center.x - vw * 0.5f,
        sy + m_center.y - vh * 0.5f
    };
}

bool Camera::isVisible(Vec2 worldPos, float radius) const{
    SDL_Rect r = worldToScreen(
        worldPos,
        static_cast<int>(radius * 2.f),
        static_cast<int>(radius * 2.f));

    return !(r.x + r.w < 0 ||
             r.y + r.h < 0 ||
             r.x > vw ||
             r.y > vh);
}