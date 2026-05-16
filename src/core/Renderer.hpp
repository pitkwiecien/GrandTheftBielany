#pragma once
#include <SDL.h>

class Window;

// Owija SDL_Renderer i udostępnia pomocnicze rysowanie.
// Jedyna klasa core, której powinien dotykać RenderSystem.
class Renderer {
public:
    explicit Renderer(Window& window);
    ~Renderer();

    Renderer(const Renderer&)            = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear(SDL_Color color);
    void present();

    // Rysuje teksturę. src == nullptr => cała tekstura.
    // angleDeg => obrót wokół środka dst (przydatne dla pocisków).
    void drawTexture(SDL_Texture*   texture,
                      const SDL_Rect* src,
                      const SDL_Rect* dst,
                      double          angleDeg = 0.0);

    void drawRect(const SDL_Rect& rect, SDL_Color color, bool filled);
    void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);

    SDL_Renderer* handle() const { return m_renderer; }

private:
    SDL_Renderer* m_renderer = nullptr;
};
