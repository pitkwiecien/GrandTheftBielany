#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Renderer;

class Text {
public:
    Text(Renderer& renderer, TTF_Font* font);
    ~Text();

    void setString(const std::string& s, SDL_Color color);
    void draw(int x, int y);

private:
    Renderer&    m_renderer;
    TTF_Font*    m_font = nullptr;
    SDL_Texture* m_texture = nullptr;   // przebudowywana przy zmianie tekstu
    int m_w = 0, m_h = 0;
};