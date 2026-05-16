#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

class Renderer;
class Registry;
class Text;
struct PlayerStats;

// Nakładka rozgrywki: pasek HP, pasek XP, poziom, czas, liczba zabić.
// Rysowana w przestrzeni ekranu (bez kamery), po RenderSystem.
class HUD {
public:
    HUD(Renderer& renderer, TTF_Font* font);
    ~HUD();

    void render(Renderer& renderer, Registry& reg,
                const PlayerStats& stats, int screenW, int screenH);

private:
    void drawBar(Renderer& r, SDL_Rect rect,
                 float ratio, SDL_Color fill, SDL_Color bg);

    std::unique_ptr<Text> m_levelText;
    std::unique_ptr<Text> m_timeText;
    std::unique_ptr<Text> m_killsText;
};
