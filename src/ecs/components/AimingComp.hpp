#pragma once
#include <SDL.h>

struct AimingComp {
    float timeLeft = 0.f;
    float aimX = 0.f;
    float aimY = 0.f;
    
    SDL_Texture* textures[8]{nullptr}; 
};