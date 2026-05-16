#pragma once
#include <SDL.h>

struct SpriteComp {
    SDL_Texture* texture = nullptr;  // własność po stronie TextureManager
    SDL_Rect     srcRect{0, 0, 0, 0}; // wycinek atlasu (0 = całość)
    int          w = 0, h = 0;        // rozmiar docelowy w pikselach świata
    int          layer = 0;           // do sortowania przy rysowaniu
};