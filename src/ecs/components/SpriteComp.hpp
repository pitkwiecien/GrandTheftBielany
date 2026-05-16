#pragma once
#include <SDL.h>

// Sprite do rysowania. Tekstura jest własnością TextureManager.
// srcRect o zerowym w/h => rysuj całą teksturę.
struct SpriteComp {
    SDL_Texture* texture = nullptr;
    SDL_Rect     srcRect{0, 0, 0, 0}; // wycinek atlasu
    int          w = 0;               // rozmiar docelowy w świecie
    int          h = 0;
    int          layer = 0;           // sortowanie rysowania (niżej = wcześniej)
    SDL_Color    tint{255, 255, 255, 255};
    bool         visible = true;
};
