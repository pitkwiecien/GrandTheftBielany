#include "core/Renderer.hpp"
#include "core/Window.hpp"
#include <stdexcept>

Renderer::Renderer(Window& window) {
    m_renderer = SDL_CreateRenderer(
        window.handle(), -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_renderer)
        throw std::runtime_error(SDL_GetError());
}

Renderer::~Renderer() {
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
}

void Renderer::clear(SDL_Color c) {
    SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(m_renderer);
}

void Renderer::present() {
    SDL_RenderPresent(m_renderer);
}

void Renderer::drawTexture(SDL_Texture* texture,
                            const SDL_Rect* src,
                            const SDL_Rect* dst,
                            double angleDeg) {
    SDL_RenderCopyEx(m_renderer, texture, src, dst,
                     angleDeg, nullptr, SDL_FLIP_NONE);
}

void Renderer::drawRect(const SDL_Rect& rect, SDL_Color c, bool filled) {
    SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
    if (filled)
        SDL_RenderFillRect(m_renderer, &rect);
    else
        SDL_RenderDrawRect(m_renderer, &rect);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, SDL_Color c) {
    SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
}
