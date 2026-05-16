#pragma once
#include <SDL.h>
#include "math/Vec2.hpp"

class Window;

class Renderer {
public:
    explicit Renderer(Window& window);
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear(Uint8 r, Uint8 g, Uint8 b);
    void present();

    void drawTexture(SDL_Texture* tex,
                      const SDL_Rect* src,
                      const SDL_Rect* dst,
                      double angleDeg = 0.0);
    void drawRect(const SDL_Rect& rect, SDL_Color color, bool filled);

    SDL_Renderer* handle() const { return m_renderer; }

private:
    SDL_Renderer* m_renderer = nullptr;
};