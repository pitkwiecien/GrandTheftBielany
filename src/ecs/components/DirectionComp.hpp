#pragma once
#include <SDL.h>
#include <array>

enum class Direction8 : int {
    North = 0,
    NorthEast = 1,
    East = 2,
    SouthEast = 3,
    South = 4,
    SouthWest = 5,
    West = 6,
    NorthWest = 7
};

struct DirectionComp {
    Direction8 facing = Direction8::South;
    std::array<SDL_Texture*, 8> textures{};
};