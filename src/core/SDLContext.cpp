#include "core/SDLContext.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>

SDLContext::SDLContext() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(SDL_GetError());

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
        throw std::runtime_error(IMG_GetError());

    if (TTF_Init() != 0)
        throw std::runtime_error(TTF_GetError());
}

SDLContext::~SDLContext() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
