#pragma once
#include <SDL.h>

struct SpriteComp {
    SDL_Texture* texture = nullptr;
    SDL_Rect srcRect{0, 0, 0, 0};
    int w = 0;
    int h = 0;
    int layer = 0;
    SDL_Color tint{255, 255, 255, 255};
    bool visible = true;
    bool flipHorizontal = false;
};