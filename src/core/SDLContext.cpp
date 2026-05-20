#include "core/SDLContext.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdexcept>

SDLContext::SDLContext() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(SDL_GetError());

    SDL_InitSubSystem(SDL_INIT_AUDIO);

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
        throw std::runtime_error(IMG_GetError());

    if (TTF_Init() != 0)
        throw std::runtime_error(TTF_GetError());

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0)
        m_audioOpen = true;
}

SDLContext::~SDLContext() {
    if (m_audioOpen) Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
