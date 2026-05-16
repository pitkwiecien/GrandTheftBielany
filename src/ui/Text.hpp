#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Renderer;

// W SDL2 tekst nie "działa sam" — TTF renderuje do powierzchni,
// którą zamieniamy na teksturę. Tekstura jest przebudowywana
// tylko gdy zmieni się string/kolor (cache wewnętrzny).
class Text {
public:
    Text(Renderer& renderer, TTF_Font* font);
    ~Text();

    Text(const Text&)            = delete;
    Text& operator=(const Text&) = delete;

    void setString(const std::string& s, SDL_Color color);
    void draw(int x, int y);

    int width()  const { return m_w; }
    int height() const { return m_h; }

private:
    void rebuild();

    Renderer&    m_renderer;
    TTF_Font*    m_font    = nullptr;
    SDL_Texture* m_texture = nullptr;
    std::string  m_string;
    SDL_Color    m_color{255, 255, 255, 255};
    bool         m_dirty = true;
    int          m_w = 0;
    int          m_h = 0;
};
