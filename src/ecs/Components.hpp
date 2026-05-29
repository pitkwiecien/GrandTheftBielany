#pragma once
#include "math/Math.hpp"
#include <SDL.h>
#include <array>

struct Transform {
    Vec2  pos{};
    float rotation = 0.f;
    float scale    = 1.f;
};

struct Velocity {
    Vec2  value{};
    float maxSpeed = 0.f;
};

struct Health {
    float current     = 1.f;
    float max         = 1.f;
    float invulnTimer = 0.f;
    bool  dead        = false;

    void damage(float amount) {
        if (invulnTimer > 0.f || dead) return;
        current -= amount;
        if (current <= 0.f) { current = 0.f; dead = true; }
    }

    void heal(float amount) {
        if (dead) return;
        current = std::min(current + amount, max);
    }
};

struct Collider {
    float radius  = 8.f;
    bool  trigger = false;
};

struct PlayerTag {};

struct EnemyTag {
    int   typeId          = 0;
    float touchDamage     = 1.f;
    float xpReward        = 1.f;
    float contactCooldown = 0.f;
};

struct SpriteComp {
    SDL_Texture* texture = nullptr;
    SDL_Rect srcRect{0, 0, 0, 0};
    int w = 0;
    int h = 0;
    int layer = 0;
    SDL_Color tint{255, 255, 255, 255};
    bool visible         = true;
    bool flipHorizontal  = false;
};

enum Direction8 {
    North = 0, NorthEast, East, SouthEast,
    South, SouthWest, West, NorthWest
};

struct DirectionComp {
    Direction8 facing = Direction8::South;
    std::array<SDL_Texture*, 8> idleTextures{};
    std::array<SDL_Texture*, 8> runTextures{};
};

struct AnimationComp {
    int   numFrames    = 1;
    int   currentFrame = 0;
    float frameTime    = 0.1f;
    float accumulator  = 0.f;
    int   frameWidth   = 0;
    int   frameHeight  = 0;
    bool  isPlaying    = false;
};

struct ProjectileTag {
    float damage   = 10.f;
    float lifetime =  2.f;
};
